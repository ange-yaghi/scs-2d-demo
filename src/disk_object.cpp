#include "../include/disk_object.h"

#include "../include/demo_application.h"

DiskObject::DiskObject() {
    m_radius = 0.0f;
}

DiskObject::~DiskObject() {
    /* void */
}

void DiskObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addRigidBody(&m_body);
}

void DiskObject::reset() {
    DemoObject::reset();

    m_body.reset();
}

void DiskObject::render(DemoApplication *app) {
    DemoObject::render(app);

    app->drawDisk(
        (float)m_body.p_x,
        (float)m_body.p_y,
        (float)m_body.theta,
        m_radius);
}

void DiskObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

void DiskObject::configure(double radius, double density) {
    m_radius = (float)radius;

    m_body.m = density * (double)ysMath::Constants::PI * radius * radius;
    m_body.I = 0.5 * m_body.m * radius * radius;
}

double DiskObject::energy() const {
    return m_body.energy();
}

void DiskObject::onClick(double x, double y, ClickEvent *clickEvent) {
    double lx, ly;
    m_body.worldToLocal(x, y, &lx, &ly);

    clickEvent->clicked = false;
    if (lx * lx + ly * ly > (double)m_radius * m_radius) return;
    
    clickEvent->body = &m_body;
    clickEvent->clicked = true;
    m_body.localToWorld(lx, ly, &clickEvent->x, &clickEvent->y);
}
