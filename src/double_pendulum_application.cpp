#include "../include/double_pendulum_application.h"

#include <sstream>

DoublePendulumApplication::DoublePendulumApplication() {
    /* void */
}

DoublePendulumApplication::~DoublePendulumApplication() {
    /* void */
}

void DoublePendulumApplication::initialize() {
    m_shaders.SetClearColor(ysColor::linearToSrgb(ysColor::srgbiToLinear(0x101213)));
    m_assetManager.CompileInterchangeFile((m_assetPath + "/icosphere").c_str(), 1.0f, true);
    m_assetManager.LoadSceneFile((m_assetPath + "/icosphere").c_str(), true);
    m_assetManager.LoadTexture((m_assetPath + "/chicken.png").c_str(), "Chicken");
    m_assetManager.LoadTexture((m_assetPath + "/dashed_line_pencil_2.png").c_str(), "Dashed Line");

    setCameraPosition(ysMath::LoadVector(0.0f, 0.0f, 10.0f));
    setCameraTarget(ysMath::LoadVector(0.0f, 0.0f, 0.0f));
    setCameraUp(ysMath::Constants::YAxis);

    m_textRenderer.SetEngine(&m_engine);
    m_textRenderer.SetRenderer(m_engine.GetUiRenderer());
    m_textRenderer.SetFont(m_engine.GetConsole()->GetFont());

    const double rodDensity = 1.0;

    m_r0 = 1.5;
    m_r1 = 2.0;

    m_pendulum0.m = rodDensity * m_r0 * 2;
    m_pendulum0.I = m_pendulum0.m * m_r0 * m_r0;
    m_pendulum0.p_x = -2.0 + m_r0;

    m_pendulum1.m = rodDensity * m_r1 * 2;
    m_pendulum1.I = m_pendulum1.m * m_r1 * m_r1;
    m_pendulum1.p_x = 2.0 + m_r1;

    m_c0.setBody(&m_pendulum0);
    m_c0.m_local_x = -m_r0;
    m_c0.m_world_x = -2.0;

    m_c1.setBody(&m_pendulum1);
    m_c1.m_local_x = -m_r1;
    m_c1.m_world_x = 2.0;

    m_fg0.m_body = &m_pendulum0;
    m_fg0.m_f_y = -10.0 * m_pendulum0.m;
    
    m_fg1.m_body = &m_pendulum1;
    m_fg1.m_f_y = -10.0 * m_pendulum1.m;

    // m_friction0.m_body0 = &m_pendulum0;
    // m_friction0.m_constraint = &m_c0;
    // m_friction0.m_frictionCoefficient = 0.025;

    m_rigidBodySystem.addConstraint(&m_c0);
    m_rigidBodySystem.addConstraint(&m_c1);

    m_rigidBodySystem.addForceGenerator(&m_fg0);
    m_rigidBodySystem.addForceGenerator(&m_fg1);
    // m_rigidBodySystem.addForceGenerator(&m_friction0);

    m_rigidBodySystem.addRigidBody(&m_pendulum0);
    m_rigidBodySystem.addRigidBody(&m_pendulum1);

    m_rigidBodySystem.initialize(new atg_scs::GaussSeidelSleSolver, new atg_scs::Rk4OdeSolver);
}

void DoublePendulumApplication::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0);
}

void DoublePendulumApplication::render() {
    drawGrid();

    drawBar(
            m_pendulum0.p_x,
            m_pendulum0.p_y,
            m_pendulum0.theta,
            m_r0 * 2);

    drawBar(
            m_pendulum1.p_x,
            m_pendulum1.p_y,
            m_pendulum1.theta,
            m_r1 * 2);

    std::stringstream ss;
    ss << (m_pendulum0.v_theta / (ysMath::Constants::TWO_PI)) * 60 << " RPM";

    const float screenWidth = (float)m_engine.GetScreenWidth();
    const float screenHeight = (float)m_engine.GetScreenHeight();
    m_textRenderer.RenderText(
            ss.str(), -screenWidth / 2.0f, screenHeight / 2.0f - 32.0f, 32.0f);

    ss = std::stringstream();
    ss << m_engine.GetAverageFramerate() << " FPS";
    m_textRenderer.RenderText(
            ss.str(), -screenWidth / 2.0f, screenHeight / 2.0f - 64.0f, 32.0f);
}

void DoublePendulumApplication::drawPendulum(
    double hinge_x,
    double hinge_y,
    double x,
    double y,
    double angle,
    double r)
{
    ysMatrix mat = ysMath::RotationTransform(
        ysMath::LoadVector(0.0f, 0.0f, 1.0f),
        (float)angle);
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
    m_shaders.SetEmission(
        ysMath::Mul(ysColor::srgbiToLinear(0xff, 0x0, 0x0), ysMath::LoadScalar(0)));
    m_shaders.SetBaseColor(ysMath::LoadVector(1.0f, 1.0f, 1.0f, 1.0f));
    m_shaders.SetColorReplace(true);
    m_shaders.SetLit(false);
    m_shaders.SetDiffuseTexture(nullptr);
    m_shaders.SetFogFar(2001);
    m_shaders.SetFogNear(2000.0);

    GeometryGenerator::GeometryIndices indices;

    m_shaders.SetObjectTransform(ysMath::TranslationTransform(
        ysMath::LoadVector(
            (float)hinge_x,
            (float)hinge_y,
            0.0f,
            0.0f)));

    GeometryGenerator::LineRingParameters params{};
    params.center = ysMath::LoadVector(0.0f, 0.0f, 0.0f);
    params.normal = ysMath::Constants::ZAxis;
    params.radius = 100.3f;
    params.maxEdgeLength = 1.0f;
    params.startAngle = 0.0f;
    params.endAngle = ysMath::Constants::TWO_PI;
    params.patternHeight = 1.0f;
    params.textureWidthHeightRatio = 5.0;
    params.taperTail = ysMath::Constants::TWO_PI * 0.1f;

    m_geometryGenerator.startShape();
    m_geometryGenerator.generateLineRingBalanced(
        params);
    m_geometryGenerator.endShape(&indices);
    drawGenerated(indices);

    m_shaders.SetObjectTransform(mat);

    GeometryGenerator::LineParameters lineParams{};
    lineParams.start = ysMath::LoadVector((float)-r, 0.0f, 0.0f);
    lineParams.end = ysMath::LoadVector((float)r, 0.0f, 0.0f);
    lineParams.patternHeight = 10.0f;
    lineParams.textureOffset = 0.0f;
    lineParams.textureWidthHeightRatio = 5.0f;
    lineParams.taperTail = 0.0f;

    m_geometryGenerator.startShape();
    m_geometryGenerator.generateLine(
        lineParams);
    m_geometryGenerator.endShape(&indices);
    drawGenerated(indices);

    GeometryGenerator::LineRingParameters lineEndParams{};
    lineEndParams.center = ysMath::LoadVector(-r, 0.0f, 0.0f);
    lineEndParams.normal = ysMath::Constants::ZAxis;
    lineEndParams.radius = 50.0f;
    lineEndParams.maxEdgeLength = 1.0f;
    lineEndParams.startAngle = 0.0f;
    lineEndParams.endAngle = ysMath::Constants::TWO_PI;
    lineEndParams.patternHeight = 1.0f;
    lineEndParams.textureWidthHeightRatio = 5.0;
    lineEndParams.taperTail = ysMath::Constants::TWO_PI * 0.1f;

    m_geometryGenerator.startShape();
    m_geometryGenerator.generateLineRingBalanced(
        lineEndParams);
    m_geometryGenerator.endShape(&indices);
    drawGenerated(indices);

    lineEndParams.center = ysMath::LoadVector(r, 0.0f, 0.0f);
    lineEndParams.normal = ysMath::Constants::ZAxis;
    lineEndParams.radius = 0.01f;
    lineEndParams.maxEdgeLength = 0.1f;
    lineEndParams.startAngle = 0.0f;
    lineEndParams.endAngle = ysMath::Constants::TWO_PI;
    lineEndParams.patternHeight = 100.0f;
    lineEndParams.textureWidthHeightRatio = 5.0;
    lineEndParams.taperTail = ysMath::Constants::TWO_PI * 0.1f;

    m_geometryGenerator.startShape();
    m_geometryGenerator.generateLineRingBalanced(
        lineEndParams);
    m_geometryGenerator.endShape(&indices);
    drawGenerated(indices);

    //drawRoundedFrame(0, 0, 500, 120 - 15 / 2.0, 15, 60);
}
