#include "../include/bar_object.h"

#include "../include/demo_application.h"

#include <algorithm>

BarObject::BarObject() {
    /* void */
}

BarObject::~BarObject() {
    /* void */
}

void BarObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addRigidBody(&m_body);
}

void BarObject::reset() {
    DemoObject::reset();

    m_body.reset();
}

void BarObject::render(DemoApplication *app) {
    DemoObject::render(app);

    app->drawBar(
            m_body.p_x,
            m_body.p_y,
            m_body.theta,
            m_length);
}

void BarObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

void BarObject::configure(float length, float density) {
    m_length = length;

    m_body.m = (double)length * density;
    m_body.I = (1 / 12.0) * m_body.m * ((double)length * length);
}

double BarObject::energy() const {
    return m_body.energy();
}

void BarObject::onClick(double x, double y, ClickEvent *clickEvent) {
    double lx, ly;
    m_body.worldToLocal(x, y, &lx, &ly);

    clickEvent->clicked = false;
    if (lx >= -m_length / 2 && lx <= m_length / 2) {
        if (std::abs(ly) <= 0.2) {
            clickEvent->body = &m_body;
            clickEvent->clicked = true;
            m_body.localToWorld(lx, 0, &clickEvent->x, &clickEvent->y);
        }
    }
}
