#include "../include/gravity_object.h"

#include "../include/demo_application.h"

GravityObject::GravityObject() {
    /* void */
}

GravityObject::~GravityObject() {
    /* void */
}

void GravityObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addForceGenerator(&m_gravity);
}

void GravityObject::reset() {
    DemoObject::reset();
}

void GravityObject::render(DemoApplication *app) {
    DemoObject::render(app);
}

void GravityObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}
