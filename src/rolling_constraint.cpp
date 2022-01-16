#include "../include/rolling_constraint.h"

#include "../include/demo_application.h"

RollingConstraint::RollingConstraint() {
    /* void */
}

RollingConstraint::~RollingConstraint() {
    /* void */
}

void RollingConstraint::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addConstraint(&m_constraint);
}

void RollingConstraint::reset() {
    DemoObject::reset();
}

void RollingConstraint::render(DemoApplication *app) {
    DemoObject::render(app);
}

void RollingConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
