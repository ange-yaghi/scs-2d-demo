#include "../include/spring_object.h"

#include "../include/demo_application.h"

SpringObject::SpringObject() {
    m_coilCount = 5;
}

SpringObject::~SpringObject() {
    /* void */
}

void SpringObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addForceGenerator(&m_spring);
}

void SpringObject::reset() {
    DemoObject::reset();
}

void SpringObject::render(DemoApplication *app) {
    DemoObject::render(app);

    double x1, y1, x2, y2;
    m_spring.getEnds(&x1, &y1, &x2, &y2);
    app->drawSpring((float)x1, (float)y1, (float)x2, (float)y2, m_coilCount, 30.0f);
}

void SpringObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

double SpringObject::energy() const {
    return m_spring.energy();
}
