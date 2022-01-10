#ifndef ATG_SCS_2D_DEMO_DEMO_APPLICATION_H
#define ATG_SCS_2D_DEMO_DEMO_APPLICATION_H

#include "geometry_generator.h"

#include "demo.h"

#include "delta.h"

class DemoApplication {
public:
    enum class Application {
        SimplePendulum,
        DoublePendulum,
        ArticulatedPendulum,
        LineConstraintPendulum
    };

public:
    DemoApplication();
    virtual ~DemoApplication();

    void initialize(void *instance, ysContextObject::DeviceAPI api);
    void run();
    void destroy();

    void setCameraPosition(const ysVector &position) { m_cameraPosition = position; }
    void setCameraTarget(const ysVector &target) { m_cameraTarget = target; }
    void setCameraUp(const ysVector &up) { m_cameraUp = up; }

    void drawGenerated(const GeometryGenerator::GeometryIndices &indices);

    void drawBar(float x, float y, float theta, float length);
    void drawRoundedFrame(
            float x,
            float y,
            float width,
            float height,
            float thickness,
            float cornerRadius);
    void drawGrid();
    void drawFixedPositionConstraint(float x, float y);

    float pixelsToUnits(float pixels) const;
    float unitsToPixels(float units) const;

    int getScreenWidth() const { return m_engine.GetScreenWidth(); }
    int getScreenHeight() const { return m_engine.GetScreenHeight(); }

    void addDemo(Demo *demo);

protected:
    void renderScene();

    dbasic::ShaderSet m_shaderSet;
    dbasic::DefaultShaders m_shaders;

    float m_displayHeight;

    dbasic::DeltaEngine m_engine;
    dbasic::AssetManager m_assetManager;

    ysVector m_cameraPosition;
    ysVector m_cameraTarget;
    ysVector m_cameraUp;

    std::string m_assetPath;

    ysGPUBuffer *m_geometryVertexBuffer;
    ysGPUBuffer *m_geometryIndexBuffer;

    GeometryGenerator m_geometryGenerator;

    int m_activeDemo;
    std::vector<Demo *> m_demos;
    bool m_paused;
};

#endif /* ATG_SCS_2D_DEMO_DEMO_APPLICATION_H */
