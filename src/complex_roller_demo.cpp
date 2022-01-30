#include "../include/complex_roller_demo.h"

#include "../include/demo_application.h"

#include <sstream>

ComplexRollerDemo::ComplexRollerDemo() {
    setName("Complex Roller Demo");

    m_steps = 1;
}

ComplexRollerDemo::~ComplexRollerDemo() {
    /* void */
}

void ComplexRollerDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    const double input_y = 2;
    const double floor_y = -5;
    const double width = 12;
    const double beamTop = input_y + 3;
    const double ramp_y = floor_y + 2;

    setCursor(0.0, input_y);
    EmptyObject *motorBase = createEmpty(EmptyObject::Style::Invisible);

    setActiveBody(nullptr);
    DiskObject *driveDisk = createLinkedDisk(1.5, 1.0);
    fixObject(0, input_y);

    ConstantSpeedMotor *motor = createMotor(&motorBase->m_body);
    motor->m_motor.m_speed = 1.0;
    motor->m_motor.m_ks = 600;
    motor->m_radius = 2.0;
    motor->m_motor.m_maxTorque = 200;
   
    setCursor(width / 2, floor_y);
    setActiveBody(nullptr);
    BarObject *rightBeam = createLinkedBar(width / 2, beamTop, 1);
    fixObject(width / 2, floor_y);

    setCursor(-width / 2, floor_y);
    setActiveBody(nullptr);
    BarObject *leftBeam = createLinkedBar(-width / 2, beamTop, 1);
    fixObject(-width / 2, floor_y);

    SpringObject *spring = connectSpring(&rightBeam->m_body, width / 2, beamTop);
    spring->m_spring.m_ks = 1;
    spring->m_spring.m_restLength = width / 2;
    spring->m_coilCount = 24;

    setCursor(0, input_y + 1.25);
    setActiveBody(&driveDisk->m_body);
    createLinkedBar(width / 2, input_y, 1.0);
    connectObjects(&rightBeam->m_body);

    setCursor(0, input_y - 1.25);
    setActiveBody(&driveDisk->m_body);
    BarObject *leftConnector = createLinkedBar(-width / 2, input_y, 1.0);
    connectObjects(&leftBeam->m_body);

    setCursor(-1.5, ramp_y);
    setActiveBody(nullptr);
    BarObject *ramp = createLinkedBar(width / 2, ramp_y, 1.0);
    connectObjects(&rightBeam->m_body);

    setCursor(width / 2 - 1.5, ramp_y);
    createLinkedBar(width / 2, ramp_y - 1.5, 1.0);
    connectObjects(&rightBeam->m_body);

    setActiveBody(&leftBeam->m_body);
    setCursor(-width / 2, ramp_y + 0.75 + 0.2);
    createLinkedBar(0, ramp_y + 0.75 + 0.2, 1.0);
    DiskObject *roller0 = createLinkedDisk(0.75, 1.0);

    moveBefore(roller0, driveDisk);

    RollingConstraint *rc0 = createObject<RollingConstraint>(&m_rigidBodySystem);
    rc0->m_constraint.m_dx = 1.0;
    rc0->m_constraint.m_dy = 0.0;
    rc0->m_constraint.setBaseBody(&ramp->m_body);
    rc0->m_constraint.setRollingBody(&roller0->m_body);
    rc0->m_constraint.m_radius = 0.75;
    rc0->m_constraint.m_local_y = 0.2;

    GravityObject *gravity = createObject<GravityObject>(&m_rigidBodySystem);
    gravity->m_gravity.m_g = 10.0;

    createMouseEmpty(EmptyObject::Style::Cursor);
    createControlSpring(200.0, 1.0);
}

void ComplexRollerDemo::process(float dt) {
    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    processObjects(dt);
}

void ComplexRollerDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
