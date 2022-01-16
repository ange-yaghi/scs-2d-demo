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

double GravityObject::energy() const {
    double totalPotential = 0;

    const int n = m_system->getRigidBodyCount();
    for (int i = 0; i < n; ++i) {
        atg_scs::RigidBody *body = m_system->getRigidBody(i);
        const double p_y = body->p_y;
        totalPotential += m_gravity.m_g * body->m * p_y;
    }

    return totalPotential;
}
