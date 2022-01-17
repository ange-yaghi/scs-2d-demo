#include "../include/empty_object.h"

#include "../include/demo_application.h"

EmptyObject::EmptyObject() {
    m_style = Style::Invisible;
}

EmptyObject::~EmptyObject() {
    /* void */
}

void EmptyObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);
}

void EmptyObject::reset() {
    DemoObject::reset();

    m_body.reset();
}

void EmptyObject::render(DemoApplication *app) {
    DemoObject::render(app);

    if (m_style == Style::FixedPosition) {
        app->drawFixedPositionConstraint(
                m_body.p_x,
                m_body.p_y,
                m_body.theta);
    }
}

void EmptyObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

double EmptyObject::energy() const {
    return 0;
}
