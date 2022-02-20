#include "../include/constant_rotation_constraint.h"

#include "../include/demo_application.h"

ConstantRotationConstraint::ConstantRotationConstraint() {
    /* void */
}

ConstantRotationConstraint::~ConstantRotationConstraint() {
    /* void */
}

void ConstantRotationConstraint::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addConstraint(&m_constraint);
}

void ConstantRotationConstraint::reset() {
    DemoObject::reset();
}

void ConstantRotationConstraint::render(DemoApplication *app) {
    DemoObject::render(app);
}

void ConstantRotationConstraint::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
