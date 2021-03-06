#include "../include/demo_object.h"

DemoObject::DemoObject() {
    m_visible = true;
    m_system = nullptr;
}

DemoObject::~DemoObject() {
    /* void */
}

void DemoObject::initialize(atg_scs::RigidBodySystem *system) {
    m_system = system;
}

void DemoObject::reset() {
    /* void */
}

void DemoObject::render(DemoApplication *app) {
    /* void */
}

void DemoObject::process(float dt, DemoApplication *app) {
    /* void */
}

double DemoObject::energy() const {
    return 0;
}

void DemoObject::onClick(double x, double y, ClickEvent *clickEvent) {
    /* void */
}
