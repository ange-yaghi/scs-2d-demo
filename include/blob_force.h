#ifndef ATG_SCS_2D_DEMO_BLOB_FORCE_H
#define ATG_SCS_2D_DEMO_BLOB_FORCE_H

#include "blob.h"

class BlobForceObject : public DemoObject {
    public:
        class BlobForce : public atg_scs::ForceGenerator {
            public:
                BlobForce();
                virtual ~BlobForce();

                virtual void apply(atg_scs::SystemState *system);

                Blob **m_blobs;
                int m_blobCount;
                double m_width;
                double m_height;

            protected:
                void f(Blob *blob0, Blob *blob1, double *f_x, double *f_y) const; 
        };

    public:
        BlobForceObject();
        virtual ~BlobForceObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        BlobForce m_force;
};

#endif /* ATG_SCS_2D_DEMO_BLOB_FORCE_H */
