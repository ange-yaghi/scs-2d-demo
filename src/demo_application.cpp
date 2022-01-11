#include "../include/demo_application.h"

#include "../include/double_pendulum_demo.h"

#include <cmath>

DemoApplication::DemoApplication() {
    m_cameraTarget = ysMath::Constants::Zero;
    m_cameraPosition = ysMath::LoadVector(0.0f, 0.0f, 5.0f);
    m_cameraUp = ysMath::Constants::YAxis;

    m_assetPath = "";

    m_geometryVertexBuffer = nullptr;
    m_geometryIndexBuffer = nullptr;

    m_displayHeight = 10.0f;
    m_paused = true;
    m_activeDemo = 0;

    m_background = ysColor::srgbiToLinear(0xFFFFFF);
    m_foreground = ysColor::srgbiToLinear(0xFFFFFF);
    m_shadow = ysColor::srgbiToLinear(0x101213);
    m_highlight1 = ysColor::srgbiToLinear(0xFFFFFF);
    m_highlight2 = ysColor::srgbiToLinear(0xFFFFFF);
}

DemoApplication::~DemoApplication() {
    /* void */
}

void DemoApplication::initialize(void *instance, ysContextObject::DeviceAPI api) {
    dbasic::Path modulePath = dbasic::GetModulePath();
    dbasic::Path confPath = modulePath.Append("delta.conf");

    std::string enginePath = "../dependencies/submodules/delta-studio/engines/basic";
    m_assetPath = "../assets";
    if (confPath.Exists()) {
        std::fstream confFile(confPath.ToString(), std::ios::in);
        
        std::getline(confFile, enginePath);
        std::getline(confFile, m_assetPath);
        enginePath = modulePath.Append(enginePath).ToString();
        m_assetPath = modulePath.Append(m_assetPath).ToString();

        confFile.close();
    }

    m_engine.GetConsole()->SetDefaultFontDirectory(enginePath + "/fonts/");

    const std::string shaderPath = enginePath + "/shaders/";

    dbasic::DeltaEngine::GameEngineSettings settings;
    settings.API = api;
    settings.DepthBuffer = false;
    settings.Instance = instance;
    settings.ShaderDirectory = shaderPath.c_str();
    settings.WindowTitle = "Engine Sim | AngeTheGreat";
    settings.WindowPositionX = 0;
    settings.WindowPositionY = 0;
    settings.WindowStyle = ysWindow::WindowStyle::Windowed;

    m_engine.CreateGameWindow(settings);

    m_engine.InitializeShaderSet(&m_shaderSet);
    m_engine.InitializeDefaultShaders(&m_shaders, &m_shaderSet);
    m_engine.InitializeConsoleShaders(&m_shaderSet);
    m_engine.SetShaderSet(&m_shaderSet);

    m_assetManager.SetEngine(&m_engine);

    m_shaders.SetCameraMode(dbasic::DefaultShaders::CameraMode::Target);

    m_engine.GetDevice()->CreateIndexBuffer(
        &m_geometryIndexBuffer, sizeof(unsigned short) * 100000, nullptr);
    m_engine.GetDevice()->CreateVertexBuffer(
        &m_geometryVertexBuffer, sizeof(dbasic::Vertex) * 50000, nullptr);

    m_geometryGenerator.initialize(50000, 100000);

    addDemo(new DoublePendulumDemo);
}

void DemoApplication::run() {
    while (m_engine.IsOpen()) {
        m_engine.StartFrame();

        if (m_engine.ProcessKeyDown(ysKey::Code::Space)) {
            m_paused = !m_paused;
        }

        if (m_engine.ProcessKeyDown(ysKey::Code::R)) {
            m_demos[m_activeDemo]->initialize();
        }

        if (!m_paused || m_engine.ProcessKeyDown(ysKey::Code::Right)) {
            m_demos[m_activeDemo]->process(m_engine.GetFrameLength());
        }

        renderScene();

        m_engine.EndFrame();
    }
}

void DemoApplication::destroy() {
    m_shaderSet.Destroy();

    m_engine.GetDevice()->DestroyGPUBuffer(m_geometryVertexBuffer);
    m_engine.GetDevice()->DestroyGPUBuffer(m_geometryIndexBuffer);

    m_assetManager.Destroy();
    m_engine.Destroy();
}

void DemoApplication::drawGenerated(const GeometryGenerator::GeometryIndices &indices) {
    m_engine.DrawGeneric(
        m_shaders.GetRegularFlags(),
        m_geometryIndexBuffer,
        m_geometryVertexBuffer,
        sizeof(dbasic::Vertex),
        indices.BaseIndex,
        indices.BaseVertex,
        indices.FaceCount);
}

void DemoApplication::drawBar(
        float x,
        float y,
        float theta,
        float length)
{
    GeometryGenerator::GeometryIndices
        bar, barShadow, end, endShadows;

    GeometryGenerator::Line2dParameters lineParams;
    lineParams.x0 = -length / 2;
    lineParams.y0 = 0.0;
    lineParams.x1 = length / 2;
    lineParams.y1 = 0.0;

    m_geometryGenerator.startShape();
    lineParams.lineWidth = pixelsToUnits(10);
    m_geometryGenerator.generateLine2d(lineParams);
    m_geometryGenerator.endShape(&bar);

    m_geometryGenerator.startShape();
    lineParams.lineWidth = pixelsToUnits(16);
    m_geometryGenerator.generateLine2d(lineParams);
    m_geometryGenerator.endShape(&barShadow);

    GeometryGenerator::Circle2dParameters circleParams;
    circleParams.center_y = 0.0;
    circleParams.maxEdgeLength = pixelsToUnits(2.0f);

    // Bar ends
    m_geometryGenerator.startShape();
    circleParams.radius = pixelsToUnits(10);
    
    circleParams.center_x = -length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    circleParams.center_x = length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    m_geometryGenerator.endShape(&end);

    // Bar end shadows
    m_geometryGenerator.startShape();
    circleParams.radius = pixelsToUnits(13);

    circleParams.center_x = -length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    circleParams.center_x = length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    m_geometryGenerator.endShape(&endShadows);

    // Draw shapes
    ysMatrix mat = ysMath::RotationTransform(
        ysMath::LoadVector(0.0f, 0.0f, 1.0f),
        (float)theta);
    mat = ysMath::MatMult(
        ysMath::TranslationTransform(
            ysMath::LoadVector(
                (float)x,
                (float)y,
                0.0f,
                0.0f)),
        mat);

    m_shaders.ResetBrdfParameters();
    m_shaders.SetMetallic(0.8f);
    m_shaders.SetIncidentSpecular(0.8f);
    m_shaders.SetSpecularRoughness(0.7f);
    m_shaders.SetSpecularMix(1.0f);
    m_shaders.SetDiffuseMix(1.0f);
    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    m_shaders.SetColorReplace(true);
    m_shaders.SetLit(false);
    m_shaders.SetDiffuseTexture(nullptr);
    m_shaders.SetFogFar(2001);
    m_shaders.SetFogNear(2000.0);
    m_shaders.SetObjectTransform(mat);

    m_shaders.SetBaseColor(ysColor::srgbiToLinear(0x101213));
    drawGenerated(barShadow);
    
    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    drawGenerated(bar);

    m_shaders.SetBaseColor(ysColor::srgbiToLinear(0x101213));
    drawGenerated(endShadows);

    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    drawGenerated(end);
}

void DemoApplication::drawRoundedFrame(
    float x,
    float y,
    float width,
    float height,
    float thickness,
    float cornerRadius)
{
    const float maxCornerRadius = std::fminf(width / 2, height / 2);
    if (cornerRadius > maxCornerRadius) {
        cornerRadius = maxCornerRadius;
    }

    GeometryGenerator::Line2dParameters params;
    params.lineWidth = thickness;

    m_geometryGenerator.startShape();

    params.x0 = x - width / 2 + cornerRadius;
    params.y0 = y + height / 2;
    params.x1 = x + width / 2 - cornerRadius;
    params.y1 = y + height / 2;
    m_geometryGenerator.generateLine2d(params);

    params.x0 = x - width / 2 + cornerRadius;
    params.y0 = y - height / 2;
    params.x1 = x + width / 2 - cornerRadius;
    params.y1 = y - height / 2;
    m_geometryGenerator.generateLine2d(params);
    
    params.x0 = x - width / 2;
    params.y0 = y - height / 2 + cornerRadius;
    params.x1 = x - width / 2;
    params.y1 = y + height / 2 - cornerRadius;
    m_geometryGenerator.generateLine2d(params);

    params.x0 = x + width / 2;
    params.y0 = y - height / 2 + cornerRadius;
    params.x1 = x + width / 2;
    params.y1 = y + height / 2 - cornerRadius;
    m_geometryGenerator.generateLine2d(params);

    GeometryGenerator::Ring2dParameters ringParams;
    ringParams.innerRadius = cornerRadius - thickness / 2;
    ringParams.outerRadius = cornerRadius + thickness / 2;
    ringParams.maxEdgeLength = 1.0f;

    const float a0 = 0;
    const float a90 = ysMath::Constants::PI / 2;
    const float a180 = ysMath::Constants::PI;
    const float a270 = 3 * ysMath::Constants::PI / 2;
    const float a360 = ysMath::Constants::TWO_PI;
    
    ringParams.center_x = x - width / 2 + cornerRadius;
    ringParams.center_y = y - height / 2 + cornerRadius;
    ringParams.startAngle = a180;
    ringParams.endAngle = a270;
    m_geometryGenerator.generateRing2d(ringParams);

    ringParams.center_x = x + width / 2 - cornerRadius;
    ringParams.center_y = y - height / 2 + cornerRadius;
    ringParams.startAngle = a270;
    ringParams.endAngle = a360;
    m_geometryGenerator.generateRing2d(ringParams);

    ringParams.center_x = x - width / 2 + cornerRadius;
    ringParams.center_y = y + height / 2 - cornerRadius;
    ringParams.startAngle = a90;
    ringParams.endAngle = a180;
    m_geometryGenerator.generateRing2d(ringParams);

    ringParams.center_x = x + width / 2 - cornerRadius;
    ringParams.center_y = y + height / 2 - cornerRadius;
    ringParams.startAngle = a0;
    ringParams.endAngle = a90;
    m_geometryGenerator.generateRing2d(ringParams);

    GeometryGenerator::GeometryIndices indices;
    m_geometryGenerator.endShape(&indices);

    drawGenerated(indices);
}

void DemoApplication::drawGrid() {
    const float frameWidth = pixelsToUnits(m_engine.GetScreenWidth() - 100);
    const float frameHeight = pixelsToUnits(m_engine.GetScreenHeight() - 100);

    GeometryGenerator::GridParameters gridParams;
    gridParams.x = 0.0f;
    gridParams.y = 0.0f;
    gridParams.width = frameWidth;
    gridParams.height = frameHeight;

    GeometryGenerator::FrameParameters frameParams;
    frameParams.frameHeight = frameHeight;
    frameParams.frameWidth = frameWidth;
    frameParams.lineWidth = pixelsToUnits(2.0f); 
    frameParams.x = frameParams.y = 0.0f;

    GeometryGenerator::GeometryIndices main, second, third;

    m_geometryGenerator.startShape();
    gridParams.div_x = gridParams.div_y = 1.0f;
    gridParams.lineWidth = pixelsToUnits(1.0f);
    m_geometryGenerator.generateGrid(gridParams);
    m_geometryGenerator.generateFrame(frameParams);
    m_geometryGenerator.endShape(&main);

    m_geometryGenerator.startShape();
    gridParams.div_x = gridParams.div_y = 0.5f;
    gridParams.lineWidth = pixelsToUnits(1.0f);
    m_geometryGenerator.generateGrid(gridParams);
    m_geometryGenerator.endShape(&second);

    m_geometryGenerator.startShape();
    gridParams.lineWidth = pixelsToUnits(1.0f);
    gridParams.div_x = gridParams.div_y = 0.25f;
    m_geometryGenerator.generateGrid(gridParams);
    m_geometryGenerator.endShape(&third);

    // Draw geometry
    m_shaders.ResetBrdfParameters();
    m_shaders.SetColorReplace(true);
    m_shaders.SetLit(false);
    m_shaders.SetFogFar(2001);
    m_shaders.SetFogNear(2000.0);
    m_shaders.SetObjectTransform(ysMath::LoadIdentity());
    
    const float c0 = 0.2f, c1 = 0.05f, c2 = 0.01f;

    m_shaders.SetBaseColor(ysMath::LoadVector(c2, c2, c2, 1.0f));
    drawGenerated(third);

    m_shaders.SetBaseColor(ysMath::LoadVector(c1, c1, c1, 1.0f));
    drawGenerated(second);

    m_shaders.SetBaseColor(ysMath::LoadVector(c0, c0, c0, 1.0f));
    drawGenerated(main);
}

void DemoApplication::drawFixedPositionConstraint(float x, float y, float angle) {
    GeometryGenerator::GeometryIndices indices;

    const float triangleHeight = pixelsToUnits(25);
    const float baseHeight = pixelsToUnits(5);

    GeometryGenerator::Line2dParameters lineParams;
    lineParams.x0 = -pixelsToUnits(20);
    lineParams.y0 = -triangleHeight - baseHeight / 2; 
    lineParams.x1 = pixelsToUnits(20);
    lineParams.y1 = -triangleHeight - baseHeight / 2;
    lineParams.lineWidth = baseHeight;

    m_geometryGenerator.startShape();
    m_geometryGenerator.generateIsoscelesTriangle(
            0,
            -triangleHeight,
            pixelsToUnits(30),
            triangleHeight);
    m_geometryGenerator.generateLine2d(lineParams);
    m_geometryGenerator.endShape(&indices);

    // Draw geometry
    ysMatrix mat = ysMath::RotationTransform(
        ysMath::LoadVector(0.0f, 0.0f, 1.0f),
        (float)angle);
    mat = ysMath::MatMult(
        ysMath::TranslationTransform(
            ysMath::LoadVector(
                x,
                y,
                0.0f,
                0.0f)),
        mat);

    m_shaders.ResetBrdfParameters();
    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    m_shaders.SetColorReplace(true);
    m_shaders.SetLit(false);
    m_shaders.SetFogFar(2001);
    m_shaders.SetFogNear(2000.0);
    m_shaders.SetObjectTransform(mat);

    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(indices);
}

void DemoApplication::drawSpring(float x0, float y0, float x1, float y1, int coils) {
    const float dx = x1 - x0;
    const float dy = y1 - y0;
    const float length = std::sqrt(dx * dx + dy * dy);
    float theta = (dy < 0)
        ? ysMath::Constants::TWO_PI - std::acos(dx / length)
        : std::acos(dx / length);

    GeometryGenerator::Line2dParameters lineParams;
    GeometryGenerator::Rhombus2dParameters rhombParams;
    GeometryGenerator::Circle2dParameters circleParams;

    GeometryGenerator::GeometryIndices
        rods,
        rodShadows,
        retainers,
        retainerShadows,
        coilBack,
        coilBackShadow,
        coilFront,
        coilFrontShadow,
        ends,
        endShadows;

    const float rodThickness = pixelsToUnits(10);
    const float coilThickness = pixelsToUnits(15);
    const float rodShadowThickness = pixelsToUnits(16);
    const float rodLength = pixelsToUnits(40);
    const float retainerRadius = pixelsToUnits(75 / 2.0);
    const float coilLength = length + rodThickness - rodLength * 2;
    
    // Rods
    m_geometryGenerator.startShape();
    lineParams.y0 = 0;
    lineParams.y1 = 0;
    lineParams.lineWidth = rodThickness;

    lineParams.x0 = -length / 2;
    lineParams.x1 = lineParams.x0 + rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    lineParams.x0 = length / 2;
    lineParams.x1 = lineParams.x0 - rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    m_geometryGenerator.endShape(&rods);

    // Rod Shadows
    m_geometryGenerator.startShape();
    lineParams.y0 = 0;
    lineParams.y1 = 0;
    lineParams.lineWidth = rodShadowThickness;

    lineParams.x0 = -length / 2;
    lineParams.x1 = lineParams.x0 + rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    lineParams.x0 = length / 2;
    lineParams.x1 = lineParams.x0 - rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    m_geometryGenerator.endShape(&rodShadows);

    // Retainers
    m_geometryGenerator.startShape();
    lineParams.lineWidth = coilThickness;
    lineParams.y0 = -retainerRadius;
    lineParams.y1 = retainerRadius;

    lineParams.x0 = lineParams.x1 = -length / 2 + rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    lineParams.x0 = lineParams.x1 = length / 2 - rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    m_geometryGenerator.endShape(&retainers);

    // Retainer Shadows
    m_geometryGenerator.startShape();
    lineParams.lineWidth = coilThickness + pixelsToUnits(6);
    lineParams.y0 = -retainerRadius - pixelsToUnits(0);
    lineParams.y1 = retainerRadius + pixelsToUnits(0);

    lineParams.x0 = lineParams.x1 = -length / 2 + rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    lineParams.x0 = lineParams.x1 = length / 2 - rodLength;
    m_geometryGenerator.generateLine2d(lineParams);

    m_geometryGenerator.endShape(&retainerShadows);

    // Coil
    rhombParams.height = 2 * retainerRadius;
    rhombParams.width = coilThickness;
    rhombParams.center_y = 0;

    // Coil back
    m_geometryGenerator.startShape();

    const float rhombSegment = (coilLength - coilThickness) / (2 * coils + 1);
    const float fullRhombusWidth = rhombSegment + coilThickness;

    // full_rhombus_width = width + 2 * shear
    rhombParams.shear = (fullRhombusWidth - rhombParams.width) / 2;
    
    for (int i = 0; i < coils + 1; ++i) {
        rhombParams.center_x = -coilLength / 2.0f + fullRhombusWidth / 2 + rhombSegment * (2 * i);
        m_geometryGenerator.generateRhombus(rhombParams);
    }

    m_geometryGenerator.endShape(&coilBack);

    // Coil front
    m_geometryGenerator.startShape();
    rhombParams.shear = -rhombParams.shear;

    for (int i = 0; i < coils; ++i) {
        rhombParams.center_x = -coilLength / 2.0f + fullRhombusWidth / 2 + rhombSegment * (2 * i + 1);
        m_geometryGenerator.generateRhombus(rhombParams);
    }

    m_geometryGenerator.endShape(&coilFront);

    // Coil front shadow
    m_geometryGenerator.startShape();
    rhombParams.width = coilThickness + pixelsToUnits(6);

    for (int i = 0; i < coils; ++i) {
        rhombParams.center_x = -coilLength / 2.0f + fullRhombusWidth / 2 + rhombSegment * (2 * i + 1);
        m_geometryGenerator.generateRhombus(rhombParams);
    }

    m_geometryGenerator.endShape(&coilFrontShadow);

    // Coil back shadow
    m_geometryGenerator.startShape();
    rhombParams.shear = -rhombParams.shear;

    for (int i = 0; i < coils; ++i) {
        rhombParams.center_x = -coilLength / 2.0f + fullRhombusWidth / 2 + rhombSegment * (2 * i);
        m_geometryGenerator.generateRhombus(rhombParams);
    }

    m_geometryGenerator.endShape(&coilBackShadow);

    // Ends
    circleParams.center_y = 0.0;
    circleParams.maxEdgeLength = pixelsToUnits(2.0f);

    m_geometryGenerator.startShape();
    circleParams.radius = pixelsToUnits(10);

    circleParams.center_x = -length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    circleParams.center_x = length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    m_geometryGenerator.endShape(&ends);

    // End shadows
    m_geometryGenerator.startShape();
    circleParams.radius = pixelsToUnits(13);

    circleParams.center_x = -length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    circleParams.center_x = length / 2;
    m_geometryGenerator.generateCircle2d(circleParams);

    m_geometryGenerator.endShape(&endShadows);

    // Draw geometry
    ysMatrix mat = ysMath::RotationTransform(
        ysMath::LoadVector(0.0f, 0.0f, 1.0f),
        (float)theta);
    mat = ysMath::MatMult(
        ysMath::TranslationTransform(
            ysMath::LoadVector(
                (float)(x0 + x1) / 2,
                (float)(y0 + y1) / 2,
                0.0f,
                0.0f)),
        mat);

    m_shaders.ResetBrdfParameters();
    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    m_shaders.SetColorReplace(true);
    m_shaders.SetLit(false);
    m_shaders.SetFogFar(2001);
    m_shaders.SetFogNear(2000.0);
    m_shaders.SetObjectTransform(mat);

    m_shaders.SetBaseColor(m_shadow);
    drawGenerated(coilBackShadow);

    m_shaders.SetBaseColor(m_shadow);
    drawGenerated(rodShadows);
    
    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(rods);

    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(coilBack);

    m_shaders.SetBaseColor(m_shadow);
    drawGenerated(coilFrontShadow);

    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(coilFront);

    m_shaders.SetBaseColor(m_shadow);
    drawGenerated(retainerShadows);

    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(retainers);

    m_shaders.SetBaseColor(m_shadow);
    drawGenerated(endShadows);

    m_shaders.SetBaseColor(m_foreground);
    drawGenerated(ends);
}

float DemoApplication::pixelsToUnits(float pixels) const {
    const float f = m_displayHeight / m_engine.GetGameWindow()->GetGameHeight();
    return pixels * f;
}

float DemoApplication::unitsToPixels(float units) const {
    const float f = m_engine.GetGameWindow()->GetGameHeight() / m_displayHeight;
    return units * f;
}

void DemoApplication::renderScene() {
    m_shaders.SetClearColor(ysColor::linearToSrgb(ysColor::srgbiToLinear(0x101213)));

    const int screenWidth = m_engine.GetGameWindow()->GetGameWidth();
    const int screenHeight = m_engine.GetGameWindow()->GetGameHeight();

    m_shaders.SetScreenDimensions((float)screenWidth, (float)screenHeight);

    m_shaders.SetCameraPosition(m_cameraPosition);
    m_shaders.SetCameraTarget(m_cameraTarget);
    m_shaders.SetCameraUp(m_cameraUp);
    m_shaders.CalculateUiCamera();
    
    if (screenWidth > 0 && screenHeight > 0) {
        const float aspectRatio = screenWidth / (float)screenHeight;
        m_shaders.SetProjection(ysMath::Transpose(
            ysMath::OrthographicProjection(
                aspectRatio * m_displayHeight,
                m_displayHeight,
                0.001f,
                500.0f)));
    }

    m_geometryGenerator.reset();

    m_demos[m_activeDemo]->render();

    m_engine.GetDevice()->EditBufferDataRange(
        m_geometryVertexBuffer,
        (char *)m_geometryGenerator.getVertexData(),
        sizeof(dbasic::Vertex) * m_geometryGenerator.getCurrentVertexCount(),
        0);

    m_engine.GetDevice()->EditBufferDataRange(
        m_geometryIndexBuffer,
        (char *)m_geometryGenerator.getIndexData(),
        sizeof(unsigned short) * m_geometryGenerator.getCurrentIndexCount(),
        0);
}

void DemoApplication::addDemo(Demo *demo) {
    m_demos.push_back(demo);
    demo->initialize();
    demo->setApplication(this);
}