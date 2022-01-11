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

    m_r0 = 1.0;
    m_r1 = 2.0;

    m_pendulum0.reset();
    m_pendulum0.configure(m_r0 * 2, rodDensity);
    m_pendulum0.m_body.p_x = -2.0 + m_r0;
    m_pendulum0.m_body.theta = 0.5;
    m_pendulum0.m_body.v_theta = 0;

    m_pendulum1.reset();
    m_pendulum1.configure(m_r1 * 2, rodDensity);
    m_pendulum1.m_body.p_x = -2.0 + m_r0 * 2 + m_r1;
    m_pendulum1.m_body.theta = 0.1;

    m_pendulum2.reset();
    m_pendulum2.configure(m_r1 * 2, rodDensity);
    m_pendulum2.m_body.p_y = 2.0 + m_r1;
    m_pendulum2.m_body.theta = 0.2;

    m_spring.m_spring.m_body1 = &m_pendulum0.m_body;
    m_spring.m_spring.m_body2 = &m_pendulum2.m_body;
    m_spring.m_spring.m_ks = 0.0f;
    m_spring.m_spring.m_kd = 10.0f;
    m_spring.m_spring.m_restLength = 3.0f;
    m_spring.m_spring.m_p1_x = m_r0;
    m_spring.m_spring.m_p2_x = -m_r1;
    m_spring.m_coilCount = 7;

    m_c0.setBody(&m_pendulum0.m_body);
    m_c0.m_local_x = -m_r0;
    m_c0.m_world_x = -2.0;

    m_c1.setBody(&m_pendulum2.m_body);
    m_c1.m_local_x = m_r1;
    m_c1.m_world_x = 2.0;

    m_f.m_body = &m_pendulum0.m_body;
    m_f.m_f_x = 0;
    m_f.m_f_y = 10;
    m_f.m_p_x = -m_r0;
    m_f.m_p_y = 0;

    m_gravity.m_gravity.m_g = 10.0;
    // m_friction0.m_body0 = &m_pendulum0;
    // m_friction0.m_constraint = &m_c0;
    // m_friction0.m_frictionCoefficient = 0.025;
    
    m_link0.m_link.setBody1(&m_pendulum0.m_body);
    m_link0.m_link.setBody2(&m_pendulum1.m_body);
    m_link0.m_link.setLocalPosition1(m_r0, 0.0);
    m_link0.m_link.setLocalPosition2(-m_r1, 0.0);

    m_link1.m_link.setBody1(&m_pendulum1.m_body);
    m_link1.m_link.setBody2(&m_pendulum2.m_body);
    m_link1.m_link.setLocalPosition1(m_r1, 0.0);
    m_link1.m_link.setLocalPosition2(-m_r1, 0.0);

    //m_link2.m_link.setBody1(&m_pendulum2.m_body);
    //m_link2.m_link.setBody2(&m_pendulum0.m_body);
    //m_link2.m_link.setLocalPosition1(m_r1, 0.0);
    //m_link2.m_link.setLocalPosition2(-m_r0, 0.0);

    m_rigidBodySystem.reset();
    m_rigidBodySystem.addConstraint(&m_c0);
    m_rigidBodySystem.addConstraint(&m_c1);
    //m_rigidBodySystem.addForceGenerator(&m_f);

    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    addObject(&m_pendulum0, &m_rigidBodySystem);
    //addObject(&m_pendulum1, &m_rigidBodySystem);
    addObject(&m_pendulum2, &m_rigidBodySystem);
    addObject(&m_gravity, &m_rigidBodySystem);
    addObject(&m_spring, &m_rigidBodySystem);
    //addObject(&m_link0, &m_rigidBodySystem);
    //addObject(&m_link1, &m_rigidBodySystem);
    //addObject(&m_link2, &m_rigidBodySystem);
}

void DoublePendulumDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0, 1);
}

void DoublePendulumDemo::render() {
    m_app->drawGrid();

    m_app->drawFixedPositionConstraint(-2.0f, 0.0f, 0.0f);
    m_app->drawFixedPositionConstraint(2.0f, 0.0f, 0.0f);

    renderObjects();
}
