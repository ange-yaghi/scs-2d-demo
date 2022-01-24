#include "../include/energy_transfer_demo.h"

#include "../include/demo_application.h"

#include <sstream>

EnergyTransferDemo::EnergyTransferDemo() {
    setName("Natural Frequency Demo");

    m_steps = 10;
}

EnergyTransferDemo::~EnergyTransferDemo() {
    /* void */
}

void EnergyTransferDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    for (int i = 0; i < 2; ++i) {
        const double y = (i == 0)
            ? 2.0
            : -3.0;

        setCursor(-4.0, y);
        setActiveBody(nullptr);
        DiskObject *drive0 = createLinkedDisk(1.5, 1.0);
        fixObject(-4, y);
        setCursor(-4.0, y + 1.0);
        BarObject *linkBar0 = createLinkedBar(0, y, 1);
        LineConstraint *c0 = createObject<LineConstraint>(&m_rigidBodySystem);
        c0->m_trackLength = 15.0;
        c0->m_constraint.m_dx = 1;
        c0->m_constraint.m_dy = 0;
        c0->m_constraint.m_local_x = linkBar0->getLength() / 2;
        c0->m_constraint.m_local_y = 0;
        c0->m_constraint.m_p0_x = 0;
        c0->m_constraint.m_p0_y = y;
        c0->m_constraint.setBody(&linkBar0->m_body);

        setCursor(4.0, y);
        setActiveBody(nullptr);
        DiskObject *r0 = createLinkedDisk(1.0, 1.0);
        SpringObject *s0 = connectSpring(&linkBar0->m_body, 0, y);
        s0->m_spring.m_ks = 70;
        s0->m_spring.m_kd = 0.0; //3
        s0->m_radius = 0.4;
        s0->m_coilCount = 6;

        LineConstraint *cr0 = createObject<LineConstraint>(&m_rigidBodySystem);
        cr0->m_trackLength = 2.0;
        cr0->m_constraint.m_dx = 1;
        cr0->m_constraint.m_dy = 0;
        cr0->m_constraint.m_local_x = 0;
        cr0->m_constraint.m_local_y = 0;
        cr0->m_constraint.m_p0_x = 4;
        cr0->m_constraint.m_p0_y = y;
        cr0->m_constraint.setBody(&r0->m_body);
        cr0->m_drawTrack = false;

        GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
        gravity->m_gravity.m_g = 10.0;

        setCursor(-4.0, y);
        EmptyObject *motorBase0 = createEmpty(EmptyObject::Style::Invisible);
        setActiveBody(&drive0->m_body);
        ConstantSpeedMotor *motor0 = createMotor(&motorBase0->m_body);
        motor0->m_radius = 2.0;
        motor0->m_motor.m_ks = 200;
        motor0->m_motor.m_kd = 1;
        motor0->m_motor.m_maxTorque = 1000;
        motor0->m_motor.m_speed = (i == 0) ? 3.0 : 20.0;
    }

    createControlSpring(5.0, 1.0);
    createMouseEmpty(EmptyObject::Style::Invisible);
}

void EnergyTransferDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();
}

void EnergyTransferDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
