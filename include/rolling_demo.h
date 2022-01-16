#ifndef ATG_SCS_2D_DEMO_ROLLING_DEMO_H
#define ATG_SCS_2D_DEMO_ROLLING_DEMO_H

#include "demo.h"

#include "demo_objects.h"

class RollingDemo : public Demo {
    public:
        RollingDemo();
        virtual ~RollingDemo();
    
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();
    
    protected:
        atg_scs::RigidBodySystem m_rigidBodySystem;
};

#endif /* ATG_SCS_2D_DEMO_ROLLING_DEMO_H */
