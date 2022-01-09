#ifndef ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_APPLICATION_H
#define ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_APPLICATION_H

#include "demo_application.h"

#include "scs.h"

class DoublePendulumApplication : public DemoApplication {
public:
    DoublePendulumApplication();
    virtual ~DoublePendulumApplication();

protected:
    virtual void initialize();
    virtual void process(float dt);
    virtual void render();
    
    void drawPendulum(
        double hinge_x,
        double hinge_y,
        double x,
        double y,
        double angle,
        double r);

    dbasic::TextRenderer m_textRenderer;

    atg_scs::RigidBodySystem m_rigidBodySystem;
    atg_scs::RigidBody m_pendulum0;
    atg_scs::RigidBody m_pendulum1;

    atg_scs::StaticForceGenerator m_fg0;
    atg_scs::StaticForceGenerator m_fg1;

    atg_scs::FixedPositionConstraint m_c0;
    atg_scs::FixedPositionConstraint m_c1;

    double m_r0;
    double m_r1;
};

#endif /* ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_APPLICATION_H */
