#include "../include/demo.h"

#include "../include/link_constraint.h"

#include "../include/delta.h"

#include <cmath>

Demo::Demo() {
    m_app = nullptr;
    m_name = "";

    m_steps = 1;
    m_odeSolveMicroseconds = 0;
    m_forceEvalMicroseconds = 0;
    m_constraintEvalMicroseconds = 0;
    m_constraintSolveMicroseconds = 0;

    m_cursor_x = m_cursor_y = 0;
    m_activeBody = nullptr;
    m_targetSystem = nullptr;
}

Demo::~Demo() {
    /* void */
}

void Demo::reset() {
    m_objects.clear();

    m_activeBody = nullptr;
}

void Demo::setName(const std::string &name) {
    m_name = name;
}

void Demo::setApplication(DemoApplication *application) {
    m_app = application;
}

void Demo::initialize() {
    /* void */
}

void Demo::render() {
    /* void */
}

void Demo::process(float dt) {
    processObjects(dt);
}

double Demo::energy(atg_scs::RigidBodySystem *system) {
    double energy = 0;
    for (DemoObject *object : m_objects) {
        if (object->getSystem() == system || system == nullptr) {
            energy += object->energy();
        }
    }

    return energy;
}

void Demo::clear() {
    for (DemoObject *obj : m_objects) {
        delete obj;
    }

    m_objects.clear();

    m_activeBody = nullptr;
    m_targetSystem = nullptr;
    m_cursor_x = m_cursor_y = 0;
}

void Demo::addObject(DemoObject *object, atg_scs::RigidBodySystem *system) {
    m_objects.push_back(object); 
    object->initialize(system);
}

void Demo::processObjects(float dt) {
    for (DemoObject *object : m_objects) {
        object->process(dt, m_app);
    }
}

void Demo::renderObjects() {
    for (DemoObject *object : m_objects) {
        object->render(m_app);
    }
}

void Demo::setCursor(double x, double y) {
    m_cursor_x = x;
    m_cursor_y = y;
}

void Demo::moveCursor(double x, double y) {
    m_cursor_x += x;
    m_cursor_y += y;
}

void Demo::setTargetSystem(atg_scs::RigidBodySystem *system) {
    m_targetSystem = system;
}

void Demo::setActiveBody(atg_scs::RigidBody *body) {
    m_activeBody = body;
}

void Demo::moveToLocal(double lx, double ly) {
    double x, y;
    m_activeBody->localToWorld(lx, ly, &x, &y);

    m_cursor_x = x;
    m_cursor_y = y;
}

FixedPositionConstraint *Demo::fixObject(double x, double y) {
    double l_x, l_y;
    m_activeBody->worldToLocal(x, y, &l_x, &l_y);

    FixedPositionConstraint *newConstraint =
        createObject<FixedPositionConstraint>(m_targetSystem);

    newConstraint->m_link.setBody(m_activeBody);
    newConstraint->m_link.setLocalPosition(l_x, l_y);
    newConstraint->m_link.setWorldPosition(x, y);
    
    return newConstraint;
}

BarObject *Demo::createLinkedBar(double x, double y, double density) {
    const double dx = x - m_cursor_x;
    const double dy = y - m_cursor_y;
    const double length = std::sqrt(dx * dx + dy * dy);

    const double theta = (dy > 0)
        ? std::acos(dx / length)
        : ysMath::Constants::TWO_PI - std::acos(dx / length);

    BarObject *newBar = createObject<BarObject>(m_targetSystem);
    newBar->m_body.theta = theta;
    
    double ex, ey;
    newBar->m_body.localToWorld(-length / 2, 0, &ex, &ey);

    newBar->m_body.p_x = m_cursor_x - ex;
    newBar->m_body.p_y = m_cursor_y - ey;

    newBar->configure(length, density);    

    if (m_activeBody != nullptr) {
        double x0, y0;
        m_activeBody->worldToLocal(m_cursor_x, m_cursor_y, &x0, &y0); 

        LinkConstraint *link = createObject<LinkConstraint>(m_targetSystem);
        link->m_link.setBody2(m_activeBody);
        link->m_link.setBody1(&newBar->m_body);
        link->m_link.setLocalPosition2(x0, y0);
        link->m_link.setLocalPosition1(-length / 2, 0);
    }

    double new_x, new_y;
    newBar->m_body.localToWorld(length / 2, 0, &new_x, &new_y);
    m_cursor_x = new_x;
    m_cursor_y = new_y;

    m_activeBody = &newBar->m_body;

    return newBar;
}

EmptyObject *Demo::createEmpty(EmptyObject::Style style) {
    EmptyObject *newEmpty =
        createObject<EmptyObject>(m_targetSystem);
    newEmpty->m_body.p_x = m_cursor_x;
    newEmpty->m_body.p_y = m_cursor_y;
    newEmpty->m_style = style;

    m_activeBody = &newEmpty->m_body;

    return newEmpty;
}

DiskObject *Demo::createLinkedDisk(double r, double density) {
    DiskObject *newDisk =
        createObject<DiskObject>(m_targetSystem);
    newDisk->configure(r, density);
    newDisk->m_body.p_x = m_cursor_x;
    newDisk->m_body.p_y = m_cursor_y;
    newDisk->m_body.theta = 0;

    if (m_activeBody != nullptr) {
        double x0, y0;
        m_activeBody->worldToLocal(m_cursor_x, m_cursor_y, &x0, &y0);

        LinkConstraint *link = createObject<LinkConstraint>(m_targetSystem);
        link->m_link.setBody1(m_activeBody);
        link->m_link.setBody2(&newDisk->m_body);
        link->m_link.setLocalPosition1(x0, y0);
        link->m_link.setLocalPosition2(0, 0);
    }

    m_activeBody = &newDisk->m_body;

    return newDisk;
}

SpringObject *Demo::connectSpring(atg_scs::RigidBody *target, double x, double y) {
    SpringObject *newSpring = createObject<SpringObject>(m_targetSystem);
    newSpring->m_spring.m_body1 = m_activeBody;
    newSpring->m_spring.m_body2 = target;

    double lx0, ly0, lx1, ly1;
    newSpring->m_spring.m_body1->worldToLocal(m_cursor_x, m_cursor_y, &lx0, &ly0);
    newSpring->m_spring.m_body2->worldToLocal(x, y, &lx1, &ly1);

    const double dx = x - m_cursor_x;
    const double dy = y - m_cursor_y;

    newSpring->m_spring.m_p1_x = lx0;
    newSpring->m_spring.m_p1_y = ly0;
    newSpring->m_spring.m_p2_x = lx1;
    newSpring->m_spring.m_p2_y = ly1;
    newSpring->m_spring.m_restLength = std::sqrt(dx * dx + dy * dy);

    return newSpring;
}

ConstantSpeedMotor *Demo::createMotor(atg_scs::RigidBody *base) {
    ConstantSpeedMotor *newMotor = createObject<ConstantSpeedMotor>(m_targetSystem);
    newMotor->m_motor.m_body0 = base;
    newMotor->m_motor.m_body1 = m_activeBody;

    double lx, ly;
    base->worldToLocal(m_cursor_x, m_cursor_y, &lx, &ly);

    newMotor->m_local_x = lx;
    newMotor->m_local_y = ly;

    return newMotor;
}

void Demo::moveBefore(DemoObject *a, DemoObject *b) {
    const size_t n = m_objects.size();
    size_t i_a = -1, i_b = -1;
    for (size_t i = 0; i < n; ++i) {
        if (m_objects[i] == a) {
            i_a = i;
        }
        else if (m_objects[i] == b) {
            i_b = i;
        }
    }

    if (i_a <= i_b) return;

    int r = i_b;
    m_objects[i_b] = a;
    
    DemoObject *prev = m_objects[i_b + 1];
    m_objects[i_b + 1] = b;

    for (int i = i_b + 2; i <= i_a; ++i) {
        DemoObject *newPrev = m_objects[i];
        m_objects[i] = prev;
        prev = newPrev;
    }
}
