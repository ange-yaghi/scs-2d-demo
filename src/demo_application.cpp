#include "../include/demo_application.h"

#include "../include/double_pendulum_application.h"

DemoApplication::DemoApplication() {
    m_cameraTarget = ysMath::Constants::Zero;
    m_cameraPosition = ysMath::LoadVector(0.0f, 0.0f, 5.0f);
    m_cameraUp = ysMath::Constants::YAxis;

    m_assetPath = "";

    m_geometryVertexBuffer = nullptr;
    m_geometryIndexBuffer = nullptr;
}

DemoApplication::~DemoApplication() {
    /* void */
}

DemoApplication *DemoApplication::createApplication(Application application) {
    switch (application) {
    case Application::DoublePendulum:
        return new DoublePendulumApplication;
    default:
        return nullptr;
    }
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

    initialize();
}

void DemoApplication::initialize() {
    m_shaders.SetClearColor(ysColor::srgbiToLinear(0x101213));
    m_assetManager.CompileInterchangeFile((m_assetPath + "/icosphere").c_str(), 1.0f, true);
    m_assetManager.LoadSceneFile((m_assetPath + "/icosphere").c_str(), true);
}

void DemoApplication::process(float dt) {
    /* void */
}

void DemoApplication::render() {
    /* void */
}

void DemoApplication::run() {
    while (m_engine.IsOpen()) {
        m_engine.StartFrame();

        process(m_engine.GetFrameLength());
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
    if (indices.Failed) return;

    m_engine.DrawGeneric(
        m_shaders.GetRegularFlags(),
        m_geometryIndexBuffer,
        m_geometryVertexBuffer,
        sizeof(dbasic::Vertex),
        indices.BaseIndex,
        indices.BaseVertex,
        indices.FaceCount);
}

void DemoApplication::renderScene() {
    const int screenWidth = m_engine.GetGameWindow()->GetGameWidth();
    const int screenHeight = m_engine.GetGameWindow()->GetGameHeight();

    m_shaders.SetScreenDimensions((float)screenWidth, (float)screenHeight);

    m_shaders.SetCameraPosition(m_cameraPosition);
    m_shaders.SetCameraTarget(m_cameraTarget);
    m_shaders.SetCameraUp(m_cameraUp);
    m_shaders.CalculateUiCamera();

    m_geometryGenerator.reset();

    render();

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
