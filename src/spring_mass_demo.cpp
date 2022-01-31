#include "../include/spring_mass_demo.h"

#include "../include/demo_application.h"

#include <sstream>

SpringMassDemo::SpringMassDemo() {
    setName("Mass Spring System");

    m_steps = 10;
}

SpringMassDemo::~SpringMassDemo() {
    /* void */
}

void SpringMassDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    setCursor(0.0, 2.0);
    EmptyObject *anchor = createEmpty(EmptyObject::Style::FixedPosition);
    anchor->m_body.theta = ysMath::Constants::PI;

    setCursor(1.0, -2.0);
    setActiveBody(nullptr);
    createLinkedDisk(1.0, 1.0);

    SpringObject *s = connectSpring(&anchor->m_body, 0.0, 2.0);
    s->m_spring.m_ks = 50;
    s->m_spring.m_kd = 0;

    GravityObject *g = createObject<GravityObject>(&m_rigidBodySystem);
    g->m_gravity.m_g = 10;

    createMouseEmpty(EmptyObject::Style::Cursor);
    createControlSpring(100.0, 10.0);
}

void SpringMassDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process((double)dt, m_steps);

    m_dt = dt;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();
}

void SpringMassDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
