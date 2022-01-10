#include "../include/double_pendulum_demo.h"

#include "../include/demo_application.h"

#include <sstream>

DoublePendulumDemo::DoublePendulumDemo() {
    /* void */
}

DoublePendulumDemo::~DoublePendulumDemo() {
    /* void */
}

void DoublePendulumDemo::initialize() {
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

void DoublePendulumDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0);
}

void DoublePendulumDemo::render() {
    m_app->drawGrid();

    m_app->drawFixedPositionConstraint(-2.0f, 0.0f);
    m_app->drawFixedPositionConstraint(2.0f, 0.0f);

    m_app->drawBar(
            m_pendulum0.p_x,
            m_pendulum0.p_y,
            m_pendulum0.theta,
            m_r0 * 2);

    m_app->drawBar(
            m_pendulum1.p_x,
            m_pendulum1.p_y,
            m_pendulum1.theta,
            m_r1 * 2);
}
