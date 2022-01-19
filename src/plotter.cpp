#include "../include/plotter.h"

#include "../include/demo_application.h"

Plotter::Plotter() {
    m_points = nullptr;
    m_pointCount = 0;
    m_bufferSize = 0;
    m_writeIndex = 0;
}

Plotter::~Plotter() {
    /* void */
}

void Plotter::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);
}

void Plotter::reset() {
    DemoObject::reset();
}

void Plotter::render(DemoApplication *app) {
    DemoObject::render(app);

    const int start = (m_writeIndex - m_pointCount + m_bufferSize) % m_bufferSize;
    const int n0 = (start + m_pointCount) > m_bufferSize
        ? m_bufferSize - start
        : m_pointCount;
    const int n1 = m_pointCount - n0;
    app->drawLines(m_points + start, m_points, n0, n1);
}

void Plotter::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

double Plotter::energy() const {
    return 0;
}

void Plotter::addPoint(const ysVector2 &p) {
    m_points[m_writeIndex] = p;
    m_writeIndex = (m_writeIndex + 1) % m_bufferSize;
    m_pointCount = (m_pointCount >= m_bufferSize)
        ? m_bufferSize
        : m_pointCount + 1;
}

void Plotter::setSize(int bufferSize) {
    destroy();

    m_writeIndex = 0;
    m_bufferSize = bufferSize;
    m_pointCount = 0;

    m_points = new ysVector2[bufferSize];
}

void Plotter::destroy() {
    if (m_points != 0) {
        delete[] m_points;
    }

    m_bufferSize = 0;
}
