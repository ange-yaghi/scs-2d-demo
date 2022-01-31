#include "../include/motor_demo.h"

#include "../include/demo_application.h"

#include <sstream>

MotorDemo::MotorDemo() {
    setName("Constant Speed Motor");
}

MotorDemo::~MotorDemo() {
    /* void */
}

void MotorDemo::initialize() {
    m_bar0.reset();
    m_bar0.configure(2.0f, 2.0f);
    m_bar0.m_body.p_x = 1.0f;

    m_bar1.reset();
    m_bar1.configure(1.0f, 2.0f);
    m_bar1.m_body.p_x = 2.5f;

    m_disk.reset();
    m_disk.configure(0.25f, 2.0f);
    m_disk.m_body.p_x = 3.0f;

    m_link0.m_link.setLocalPosition1(1.0f, 0.0f);
    m_link0.m_link.setLocalPosition2(-0.5f, 0.0f);
    m_link0.m_link.setBody1(&m_bar0.m_body);
    m_link0.m_link.setBody2(&m_bar1.m_body);

    m_link1.m_link.setLocalPosition1(0.5f, 0.0f);
    m_link1.m_link.setLocalPosition2(0.0f, 0.0f);
    m_link1.m_link.setBody1(&m_bar1.m_body);
    m_link1.m_link.setBody2(&m_disk.m_body);

    m_c0.setBody(&m_bar0.m_body);
    m_c0.m_local_y = 0;
    m_c0.m_local_x = -1.0f;
    m_c0.m_world_x = m_c0.m_world_y = 0;
    m_gravity.m_gravity.m_g = 10.0;

    m_motor.m_local_x = m_motor.m_local_y = 0;
    m_motor.m_motor.m_body0 = &m_motorMount;
    m_motor.m_motor.m_body1 = &m_bar0.m_body;
    m_motor.m_motor.m_ks = 75.0;
    m_motor.m_motor.m_kd = 0.5;
    m_motor.m_motor.m_maxTorque = 100;
    m_motor.m_motor.m_speed = 2.0;
    
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussSeidelSleSolver, new atg_scs::Rk4OdeSolver);

    m_rigidBodySystem.addConstraint(&m_c0);

    addObject(&m_bar0, &m_rigidBodySystem);
    addObject(&m_disk, &m_rigidBodySystem);
    addObject(&m_bar1, &m_rigidBodySystem);
    addObject(&m_gravity, &m_rigidBodySystem);
    addObject(&m_motor, &m_rigidBodySystem);
    addObject(&m_link0, &m_rigidBodySystem);
    addObject(&m_link1, &m_rigidBodySystem);   
}

void MotorDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process((double)dt, 1);

    if (m_app->getEngine()->IsKeyDown(ysKey::Code::A)) {
        m_motor.m_motor.m_speed = 4.0;
    }
    else {
        m_motor.m_motor.m_speed = 2.0;
    }

    m_steps = 1;
    m_dt = dt;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();
}

void MotorDemo::render() {
    m_app->drawGrid();

    renderObjects();

    m_app->drawFixedPositionConstraint(0.0f, 0.0f, 0.0f);
}
