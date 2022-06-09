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
                (float)m_body.p_x,
                (float)m_body.p_y,
                (float)m_body.theta);
    }
    else if (m_style == Style::Cursor) {
        app->drawCursor(
            (float)m_body.p_x,
            (float)m_body.p_y);
    }
}

void EmptyObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

double EmptyObject::energy() const {
    return 0;
}
