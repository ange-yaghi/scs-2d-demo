#include "../include/triple_pendulum_demo.h"

#include "../include/demo_application.h"

#include <sstream>

TriplePendulumDemo::TriplePendulumDemo() {
    setName("Triple Pendulum Demo");

    m_steps = 60;
    m_end = nullptr;
    m_plotter = nullptr;
}

TriplePendulumDemo::~TriplePendulumDemo() {
    /* void */
}

void TriplePendulumDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    setCursor(0.0, 1.0);

    BarObject *bar0 = createLinkedBar(4.0 / 3, 1.0, 1.0);
    FixedPositionConstraint *constraint = fixObject(0, 1);
    constraint->m_angle = ysMath::Constants::PI;

    for (int i = 2; i <= 3; ++i) {
        createLinkedBar(i * (4.0 / 3), 1.0, 1.0);
    }

    m_end = createLinkedDisk(0.5, 1.0);
    moveBefore(m_end, bar0);

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    m_plotter = createObject<Plotter>(nullptr);
    m_plotter->setSize(1024);

    createMouseEmpty(EmptyObject::Style::Cursor);
    createControlSpring(1000.0, 100.0);
}

void TriplePendulumDemo::process(float dt) {
    m_rigidBodySystem.process((double)dt, m_steps);

    m_dt = dt;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    m_plotter->addPoint({ (float)m_end->m_body.p_x, (float)m_end->m_body.p_y });
}

void TriplePendulumDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
