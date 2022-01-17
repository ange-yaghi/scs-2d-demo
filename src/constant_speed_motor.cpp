#include "../include/constant_speed_motor.h"

#include "../include/demo_application.h"

ConstantSpeedMotor::ConstantSpeedMotor() {
    m_local_x = m_local_y = 0;
    m_theta = 0;
    m_radius = 1.0f;
}

ConstantSpeedMotor::~ConstantSpeedMotor() {
    /* void */
}

void ConstantSpeedMotor::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addForceGenerator(&m_motor);
}

void ConstantSpeedMotor::reset() {
    DemoObject::reset();
}

void ConstantSpeedMotor::render(DemoApplication *app) {
    DemoObject::render(app);

    double x, y;
    m_motor.m_body0->localToWorld(m_local_x, m_local_y, &x, &y);

    app->drawMotor((float)x, (float)y, m_theta, m_radius, m_motor.m_speed > 0);
}

void ConstantSpeedMotor::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);

    m_theta += m_motor.m_speed * dt;
}
