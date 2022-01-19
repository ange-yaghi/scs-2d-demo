#include "../include/blob_game_demo.h"

#include "../include/demo_application.h"

#include <sstream>

BlobGameDemo::BlobGameDemo() {
    setName("Blob Game Demo");

    m_steps = 10;
    m_blobs = nullptr;
}

BlobGameDemo::~BlobGameDemo() {
    /* void */
}

void BlobGameDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    m_blobs = new Blob *[BlobCount];

    float w, h;
    m_app->getGridFrameSize(&w, &h);

    std::mt19937 rng;
    std::uniform_real_distribution<double> realDist;
    for (int i = 0; i < BlobCount; ++i) {
        Blob *blob = createObject<Blob>(&m_rigidBodySystem);
        blob->m_body.p_x = realDist(rng) * w - w / 2;
        blob->m_body.p_y = realDist(rng) * h - h / 2;
        m_blobs[i] = blob;
    }

    m_blobForce = createObject<BlobForceObject>(&m_rigidBodySystem);
    m_blobForce->m_force.m_blobs = m_blobs;
    m_blobForce->m_force.m_blobCount = BlobCount;
}

void BlobGameDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();

    float w, h;
    m_app->getGridFrameSize(&w, &h);
    m_blobForce->m_force.m_width = w;
    m_blobForce->m_force.m_height = h;

    for (int i = 0; i < BlobCount; ++i) {
        m_blobs[i]->m_boundWidth = w;
        m_blobs[i]->m_boundHeight = h;
    }
}

void BlobGameDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
