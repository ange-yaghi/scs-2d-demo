#include "../include/blob_force.h"

#include <cmath>

BlobForceObject::BlobForce::BlobForce() {
    m_blobs = nullptr;
    m_blobCount = 0;
    m_width = 10.0;
    m_height = 10.0;
}

BlobForceObject::BlobForce::~BlobForce() {
    /* void */
}

void BlobForceObject::BlobForce::apply(atg_scs::SystemState *system) {
    const int n = m_blobCount;
    for (int i = 0; i < n; ++i) {
        Blob *blob0 = m_blobs[i];
        for (int j = i + 1; j < n; ++j) {
            Blob *blob1 = m_blobs[j]; 

            double f_x, f_y;
            f(blob0, blob1, &f_x, &f_y);
            
            system->applyForce(
                    0, 0,
                    f_x, f_y,
                    blob0->m_body.index);

            system->applyForce(
                    0, 0,
                    -f_x, -f_y,
                    blob1->m_body.index);
        }
    }

    for (int i = 0; i < n; ++i) {
        Blob *blob = m_blobs[i];

        if (blob->m_body.p_x + blob->m_radius > m_width / 2) {
            system->applyForce(
                0, 0,
                -100 * (blob->m_radius + blob->m_body.p_x - m_width / 2), 0,
                blob->m_body.index);
        }

        if (blob->m_body.p_x - blob->m_radius < -m_width / 2) {
            system->applyForce(
                0, 0,
                100 * (-m_width / 2 - blob->m_body.p_x + blob->m_radius), 0,
                blob->m_body.index);
        }

        if (blob->m_body.p_y + blob->m_radius > m_height / 2) {
            system->applyForce(
                0, 0,
                0, -100 * (blob->m_radius + blob->m_body.p_y - m_height / 2),
                blob->m_body.index);
        }

        if (blob->m_body.p_y - blob->m_radius < -m_height / 2) {
            system->applyForce(
                0, 0,
                0, 100 * (-m_height / 2 - blob->m_body.p_y + blob->m_radius),
                blob->m_body.index);
        }
    }
}

void BlobForceObject::BlobForce::f(
        Blob *blob0,
        Blob *blob1,
        double *f_x,
        double *f_y) const
{
    atg_scs::RigidBody &a = blob0->m_body;
    atg_scs::RigidBody &b = blob1->m_body;

    const double dx = a.p_x - b.p_x;
    const double dy = a.p_y - b.p_y;
    const double distance_2 = dx * dx + dy * dy;
    double distance = 0.0;

    const double closingDistance = blob0->m_radius + blob1->m_radius;

    double dir_x, dir_y;
    if (distance_2 == 0) {
        distance = 0.0;
        dir_x = 1.0;
        dir_y = 0.0;
    }
    else {
        distance = std::sqrt(distance_2);
        dir_x = dx / distance;
        dir_y = dy / distance;
    }

    if (closingDistance * closingDistance <= distance_2) {
        *f_x = *f_y = 0;
    }
    else {
        const double displacement = closingDistance - distance;

        *f_x = dir_x * displacement * 1000;
        *f_y = dir_y * displacement * 1000;
    }
}

BlobForceObject::BlobForceObject() {
    /* void */
}

BlobForceObject::~BlobForceObject() {
    /* void */
}

void BlobForceObject::initialize(atg_scs::RigidBodySystem *system) {
    DemoObject::initialize(system);

    system->addForceGenerator(&m_force);
}

void BlobForceObject::reset() {
    DemoObject::reset();
}

void BlobForceObject::render(DemoApplication *app) {
    DemoObject::render(app);
}

void BlobForceObject::process(float dt, DemoApplication *app) {
    DemoObject::process(dt, app);
}

double BlobForceObject::energy() const {
    return 0;
}
