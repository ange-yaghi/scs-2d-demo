#include "../include/line_constraint.h"

#include "../include/demo_application.h"

LineConstraint::LineConstraint() {
    m_trackLength = 10.0f;
}

LineConstraint::~LineConstraint() {
    /* void */
}

void LineConstraint::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addConstraint(&m_constraint);
}

void LineConstraint::reset() {
    DemoObject::reset();
}

void LineConstraint::render(DemoApplication *app) {
    DemoObject::render(app);

    double roller_x, roller_y;
    m_constraint.m_bodies[0]->localToWorld(
            m_constraint.m_local_x,
            m_constraint.m_local_y,
            &roller_x,
            &roller_y);

    app->drawLineConstraint(
            m_constraint.m_p0_x,
            m_constraint.m_p0_y,
            m_constraint.m_dx,
            m_constraint.m_dy,
            (float)roller_x,
            (float)roller_y,
            m_trackLength);
}

void LineConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
