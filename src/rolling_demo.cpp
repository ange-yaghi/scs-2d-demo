#include "../include/rolling_demo.h"

#include "../include/demo_application.h"

#include <sstream>

RollingDemo::RollingDemo() {
    setName("Rolling Demo");

    m_steps = 1;
}

RollingDemo::~RollingDemo() {
    /* void */
}

void RollingDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    setCursor(4.0, 0.0);

    BarObject *bar0 = createLinkedBar(4.0, 1.0, 0.0001);
    FixedPositionConstraint *constraint = fixObject(4.0, 0.0);
    constraint->m_angle = ysMath::Constants::PI;
    constraint->m_link.m_ks = 500;
    constraint->m_link.m_kd = 10;

    BarObject *bar1 = createLinkedBar(0.0, -2.0, 1.0);
    DiskObject *disk = createLinkedDisk(1.0, 1.0);
    moveBefore(disk, bar1);

    setActiveBody(nullptr);
    setCursor(0.0, -3.0);
    BarObject *base = createLinkedBar(0.0, 0.0, 0.00001);
    fixObject(0.0, -1.0);

    RollingConstraint *r = createObject<RollingConstraint>(&m_rigidBodySystem);
    r->m_constraint.setBaseBody(&base->m_body);
    r->m_constraint.setRollingBody(&disk->m_body);
    r->m_constraint.m_dx = -1.0;
    r->m_constraint.m_dy = 0.0;
    r->m_constraint.m_radius = 0.0;
    r->m_constraint.m_local_x = 0.0;
    r->m_constraint.m_local_y = 0.0;

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;
}

void RollingDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();
}

void RollingDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
