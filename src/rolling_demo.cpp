#include "../include/rolling_demo.h"

#include "../include/demo_application.h"

#include <sstream>

RollingDemo::RollingDemo() {
    setName("Rolling Demo");

    m_steps = 10;
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

    setCursor(4.0, -1.0);
    createLinkedDisk(0.25, 5.5);
    BarObject *bar0 = createLinkedBar(4.0, 1.25, 1.0);
    FixedPositionConstraint *constraint = fixObject(4.0, 0.0);
    constraint->m_angle = ysMath::Constants::PI;
    constraint->m_link.m_ks = 500;
    constraint->m_link.m_kd = 10;

    BarObject *bar1 = createLinkedBar(0.0, 0.16, 1.0);
    m_roller = createLinkedDisk(1.0, 1.0);
    moveBefore(m_roller, bar1);

    setActiveBody(nullptr);
    setCursor(-2.0, -1.0);
    BarObject *base = createLinkedBar(2.0, -1.0, 1.0);
    fixObject(2.0, -1.0);

    RollingConstraint *r = createObject<RollingConstraint>(&m_rigidBodySystem);
    r->m_constraint.setBaseBody(&base->m_body);
    r->m_constraint.setRollingBody(&m_roller->m_body);
    r->m_constraint.m_dx = 1.0;
    r->m_constraint.m_dy = 0.0;
    r->m_constraint.m_radius = 1.0;
    r->m_constraint.m_local_x = 0.0;
    r->m_constraint.m_local_y = 0.16;

    setCursor(-2.0, -3.0);
    createEmpty(EmptyObject::Style::FixedPosition);
    SpringObject *spring = connectSpring(&base->m_body, -2.0, -1.0);
    spring->m_spring.m_ks = 50.0f;
    spring->m_spring.m_kd = 1.0f;
    spring->m_spring.m_restLength += 0.75f;
    spring->m_coilCount = 3;

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    setCursor(4.0, 0.0);
    EmptyObject *motorBase = createEmpty(EmptyObject::Style::Invisible);
    ConstantSpeedMotor *motor = createMotor(&motorBase->m_body);
    motor->m_motor.m_body1 = &bar0->m_body;
    motor->m_motor.m_speed = 2.0;
    motor->m_motor.m_maxTorque = 1000;
    motor->m_motor.m_ks = 100;
    motor->m_radius = 1.0f;
    setActiveBody(nullptr);

    moveBefore(motor, constraint);
    moveBefore(base, bar1);

    m_plotter = createObject<Plotter>(nullptr);
    m_plotter->setSize(1024);
}

void RollingDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    if (m_app->getEngine()->ProcessKeyDown(ysKey::Code::P)) {
        m_plotter->setVisible(!m_plotter->isVisible());
    }

    m_plotter->addPoint({ (float)m_roller->m_body.p_x, (float)m_roller->m_body.p_y });
}

void RollingDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
