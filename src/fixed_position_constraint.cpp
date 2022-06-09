#include "../include/fixed_position_constraint.h"

#include "../include/demo_application.h"

FixedPositionConstraint::FixedPositionConstraint() {
    m_angle = 0;
}

FixedPositionConstraint::~FixedPositionConstraint() {
    /* void */
}

void FixedPositionConstraint::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addConstraint(&m_link);
}

void FixedPositionConstraint::reset() {
    DemoObject::reset();
}

void FixedPositionConstraint::render(DemoApplication *app) {
    DemoObject::render(app);

    app->drawFixedPositionConstraint(
            (float)m_link.m_world_x,
            (float)m_link.m_world_y,
            m_angle);
}

void FixedPositionConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
