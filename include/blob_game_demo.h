#ifndef ATG_SCS_2D_DEMO_BLOB_GAME_DEMO_H
#define ATG_SCS_2D_DEMO_BLOB_GAME_DEMO_H

#include "demo.h"

#include "demo_objects.h"

class BlobGameDemo : public Demo {
    public:
        static constexpr int BlobCount = 50;

    public:
        BlobGameDemo();
        virtual ~BlobGameDemo();

        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

    protected:
        Blob **m_blobs;
        BlobForceObject *m_blobForce;
        atg_scs::RigidBodySystem m_rigidBodySystem;
};

#endif /* ATG_SCS_2D_DEMO_BLOB_GAME_DEMO_H */
