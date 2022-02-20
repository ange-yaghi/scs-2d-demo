#include "../include/double_pendulum_demo.h"

#include "../include/demo_application.h"

#include <sstream>

DoublePendulumDemo::DoublePendulumDemo() {
    setName("Double Pendulum Demo");

    m_steps = 100;
    m_end = nullptr;
    m_plotter = nullptr;
    m_motorOn = true;
}

DoublePendulumDemo::~DoublePendulumDemo() {
    /* void */
}

void DoublePendulumDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver);

    setCursor(0.0, 1.0);

    BarObject *bar0 = createLinkedBar(2.0, 1.0, 1.0);
    FixedPositionConstraint *constraint = fixObject(0, 1);
    constraint->m_angle = ysMath::Constants::PI;

    BarObject *bar1 = createLinkedBar(4.0, 1.0, 1.0);
    m_end = createLinkedDisk(0.5, 1.0);
    moveBefore(m_end, bar1);

    m_motor = createObject<ConstantRotationConstraint>(m_targetSystem);
    m_motor->m_constraint.setBody(&bar0->m_body);
    m_motor->m_constraint.m_rotationSpeed = 1.0;

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    m_plotter = createObject<Plotter>(nullptr);
    m_plotter->setSize(1024);

    createMouseEmpty(EmptyObject::Style::Cursor);
    createControlSpring(1000.0, 100.0);
}

void DoublePendulumDemo::process(float dt) {
    m_rigidBodySystem.process((double)dt, m_steps);

    if (m_app->getEngine()->ProcessKeyDown(ysKey::Code::M)) {
        if (m_motorOn) {
            m_rigidBodySystem.removeConstraint(&m_motor->m_constraint);
        }
        else {
            m_rigidBodySystem.addConstraint(&m_motor->m_constraint);
        }

        m_motorOn = !m_motorOn;
    }

    m_dt = dt;
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
