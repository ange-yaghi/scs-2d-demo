#include "../include/blob.h"

#include "../include/demo_application.h"

#include <cmath>

std::mt19937 Blob::s_rng;

Blob::BlobMotion::BlobMotion() {
    m_tv_x = m_tv_y = 0;
    m_maxForce = 10;
    m_ks = 10;
    m_blob = nullptr;
}

Blob::BlobMotion::~BlobMotion() {
    /* void */
}

void Blob::BlobMotion::apply(atg_scs::SystemState *system) {
    const double v_x = m_blob->m_body.v_x;
    const double v_y = m_blob->m_body.v_y;

    const double dx = m_tv_x - v_x;
    const double dy = m_tv_y - v_y;

    const double f_x = std::fmax(std::fmin(dx * m_ks, m_maxForce), -m_maxForce);
    const double f_y = std::fmax(std::fmin(dy * m_ks, m_maxForce), -m_maxForce);

    system->applyForce(
            0, 0,
            f_x, f_y,
            m_blob->m_body.index);
}

Blob::Blob() {
    m_radius = 0.5;
    m_destination_x = 0;
    m_destination_y = 0;
    m_speed = 0;
    m_boundWidth = m_boundHeight = 10.0;
}

Blob::~Blob() {
    /* void */
}

void Blob::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addRigidBody(&m_body);
    system->addForceGenerator(&m_motion);

    m_motion.m_blob = this;
    m_body.m = 10.0;
    m_body.I = 10.0;
}

void Blob::reset() {
    DemoObject::reset();
}

void Blob::render(DemoApplication *app) {
    DemoObject::render(app);

    app->drawBlob((float)m_body.p_x, (float)m_body.p_y);
}

void Blob::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);

    // Simple blob AI
    constexpr double DirectionChangesPerSecond = 0.1;
    std::uniform_real_distribution<double> dist;
    if (dist(s_rng) < DirectionChangesPerSecond * dt) {
        m_destination_x = dist(s_rng) * m_boundWidth - m_boundWidth / 2;
        m_destination_y = dist(s_rng) * m_boundHeight - m_boundHeight / 2;
        m_speed = dist(s_rng) * 2.0 + 1.0;
    }

    const double heading_x = m_destination_x - m_body.p_x;
    const double heading_y = m_destination_y - m_body.p_y;

    const double length = std::sqrt(
            heading_x * heading_x + heading_y * heading_y);

    if (length == 0) {
        m_motion.m_tv_x = m_motion.m_tv_y = 0;
    }
    else {
        m_motion.m_tv_x = m_speed * heading_x / length;
        m_motion.m_tv_y = m_speed * heading_y / length;
    }
}

double Blob::energy() const {
    return m_body.energy();
}
