#include "../include/double_pendulum_demo.h"

#include "../include/demo_application.h"

#include <sstream>

DoublePendulumDemo::DoublePendulumDemo() {
    setName("Double Pendulum Demo");

    m_steps = 100;
    m_end = nullptr;
    m_plotter = nullptr;
}

DoublePendulumDemo::~DoublePendulumDemo() {
    /* void */
}

void DoublePendulumDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    setCursor(0.0, 1.0);

    BarObject *bar0 = createLinkedBar(2.0, 1.0, 1.0);
    FixedPositionConstraint *constraint = fixObject(0, 1);
    constraint->m_angle = ysMath::Constants::PI;

    BarObject *bar1 = createLinkedBar(4.0, 1.0, 1.0);
    m_end = createLinkedDisk(0.5, 1.0);
    moveBefore(m_end, bar1);

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    m_plotter = createObject<Plotter>(nullptr);
    m_plotter->setSize(256);
}

void DoublePendulumDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    m_plotter->addPoint({ (float)m_end->m_body.p_x, (float)m_end->m_body.p_y });
}

void DoublePendulumDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
