#include "../include/demo.h"

Demo::Demo() {
    m_app = nullptr;
    m_name = "";
}

Demo::~Demo() {
    /* void */
}

void Demo::reset() {
    m_objects.clear();
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
