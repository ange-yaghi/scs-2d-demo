#include "../include/spring_double_pendulum_demo.h"

#include "../include/demo_application.h"

#include <sstream>

SpringDoublePendulumDemo::SpringDoublePendulumDemo() {
    setName("Double Pendulum Demo");

    m_steps = 5;
    m_end = nullptr;
    m_plotter = nullptr;
}

SpringDoublePendulumDemo::~SpringDoublePendulumDemo() {
    /* void */
}

void SpringDoublePendulumDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    setCursor(0.0, 2.0);

    EmptyObject *base = createEmpty(EmptyObject::Style::FixedPosition);
    base->m_body.theta = ysMath::Constants::PI;

    setActiveBody(nullptr);
    setCursor(2.0, 2.0);
    DiskObject *link = createLinkedDisk(0.5, 1.0);

    SpringObject *s0 = connectSpring(&base->m_body, 0.0, 2.0);
    s0->m_spring.m_ks = 10000;
    s0->m_spring.m_kd = 0.0;

    setActiveBody(nullptr);
    setCursor(4.0, 2.0);
    m_end = createLinkedDisk(0.5, 1.0);

    SpringObject *s1 = connectSpring(&link->m_body, 2.0, 2.0);
    s1->m_spring.m_ks = 10000;
    s1->m_spring.m_kd = 0.0;

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    m_plotter = createObject<Plotter>(nullptr);
    m_plotter->setSize(256);

    createMouseEmpty(EmptyObject::Style::Cursor);
    createControlSpring(1000.0, 100.0);
}

void SpringDoublePendulumDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    m_plotter->addPoint({ (float)m_end->m_body.p_x, (float)m_end->m_body.p_y });
}

void SpringDoublePendulumDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
