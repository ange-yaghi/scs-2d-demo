#ifndef ATG_SCS_2D_DEMO_DEMO_APPLICATION_H
#define ATG_SCS_2D_DEMO_DEMO_APPLICATION_H

#include "geometry_generator.h"

#include "demo.h"
#include "bar_object.h"

#include "delta.h"

class DemoApplication {
public:
    static constexpr int BackgroundLayer = 0;
    static constexpr int ForegroundLayer = 1;

public:
    DemoApplication();
    virtual ~DemoApplication();

    void initialize(void *instance, ysContextObject::DeviceAPI api);
    void run();
    void destroy();

    void setCameraPosition(const ysVector &position) { m_cameraPosition = position; }
    void setCameraTarget(const ysVector &target) { m_cameraTarget = target; }
    void setCameraUp(const ysVector &up) { m_cameraUp = up; }

    void drawGenerated(
        const GeometryGenerator::GeometryIndices &indices,
        int layer= ForegroundLayer);

    void drawBar(float x, float y, float theta, float length, float width_px = 20.0f);
    void drawRoundedFrame(
            float x,
            float y,
            float width,
            float height,
            float thickness,
            float cornerRadius);
    void drawGrid();
    void drawFixedPositionConstraint(float x, float y, float angle);
    void drawCursor(float x, float y);
    void drawSpring(
            float x0,
            float y0,
            float x1,
            float y1,
            int coils,
            float radius = 0.5f);
    void drawDisk(float x, float y, float theta, float radius);
    void drawLineConstraint(
            float x,
            float y,
            float dx,
            float dy,
            float roller_x,
            float roller_y,
            float length,
            float sliderLength,
            bool drawTrack = true);
    void drawMotor(float x, float y, float theta, float radius, bool positive);
    void renderTitle();
    void drawLines(ysVector2 *p0, ysVector2 *p1, int n0, int n1);
    void drawBlob(float x, float y);

    float pixelsToUnits(float pixels) const;
    float unitsToPixels(float units) const;
    void getGridFrameSize(float *w, float *h) const;

    int getScreenWidth() const { return m_engine.GetScreenWidth(); }
    int getScreenHeight() const { return m_engine.GetScreenHeight(); }

    void addDemo(Demo *demo);

    dbasic::DeltaEngine *getEngine() { return &m_engine;  }
    GeometryGenerator *getGenerator() { return &m_geometryGenerator; }

protected:
    void renderScene();

    dbasic::ShaderSet m_shaderSet;
    dbasic::DefaultShaders m_shaders;

    float m_displayHeight;
    float m_uiScale;

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
    bool m_showingStats;

    ysVector m_background;
    ysVector m_foreground;
    ysVector m_shadow;
    ysVector m_highlight1;
    ysVector m_highlight2;

    dbasic::ModelAsset *m_logo;
    dbasic::ModelAsset *m_logoBackground;
    dbasic::ModelAsset *m_blobForeground;
    dbasic::ModelAsset *m_blobBackground;
    dbasic::ModelAsset *m_blobFace;

    dbasic::TextRenderer m_textRenderer;
};

#endif /* ATG_SCS_2D_DEMO_DEMO_APPLICATION_H */
