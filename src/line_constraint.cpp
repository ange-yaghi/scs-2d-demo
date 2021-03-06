#include "../include/line_constraint.h"

#include "../include/demo_application.h"

LineConstraint::LineConstraint() {
    m_trackLength = 10.0f;
    m_drawTrack = true;
    m_sliderLength = 1.5f;
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
            (float)m_constraint.m_local_x,
            (float)m_constraint.m_local_y,
            &roller_x,
            &roller_y);

    app->drawLineConstraint(
            (float)m_constraint.m_p0_x,
            (float)m_constraint.m_p0_y,
            (float)m_constraint.m_dx,
            (float)m_constraint.m_dy,
            (float)roller_x,
            (float)roller_y,
            m_trackLength,
            m_sliderLength,
            m_drawTrack);
}

void LineConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
