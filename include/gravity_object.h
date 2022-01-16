#ifndef ATG_SCS_2D_DEMO_GRAVITY_OBJECT_H
#define ATG_SCS_2D_DEMO_GRAVITY_OBJECT_H

#include "demo_object.h"

class GravityObject : public DemoObject {
    public:
        GravityObject();
        virtual ~GravityObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        atg_scs::GravityForceGenerator m_gravity;
};

#endif /* ATG_SCS_2D_DEMO_GRAVITY_OBJECT_H */
