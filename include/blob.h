#ifndef ATG_SCS_2D_DEMO_BLOB_H
#define ATG_SCS_2D_DEMO_BLOB_H

#include "demo_object.h"

#include <random>

class Blob : public DemoObject {
    public:
        class BlobMotion : public atg_scs::ForceGenerator {
            public:
                BlobMotion();
                virtual ~BlobMotion();

                virtual void apply(atg_scs::SystemState *system);

                double m_tv_x;
                double m_tv_y;
                double m_maxForce;
                double m_ks;
                Blob *m_blob;
        };

    public:
        static std::mt19937 s_rng;
        static void seed(unsigned int seed) { s_rng.seed(seed); }

    public:
        Blob();
        virtual ~Blob();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        atg_scs::RigidBody m_body;
        BlobMotion m_motion;

        double m_radius;
        double m_destination_x;
        double m_destination_y;
        double m_speed;

        double m_boundWidth;
        double m_boundHeight;
};

#endif /* ATG_SCS_2D_DEMO_BLOB_H */
