#include "../include/link_constraint.h"

#include "../include/demo_application.h"

LinkConstraint::LinkConstraint() {
    /* void */
}

LinkConstraint::~LinkConstraint() {
    /* void */
}

void LinkConstraint::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addConstraint(&m_link);
}

void LinkConstraint::reset() {
    DemoObject::reset();
}

void LinkConstraint::render(DemoApplication *app) {
    DemoObject::render(app);
}

void LinkConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
