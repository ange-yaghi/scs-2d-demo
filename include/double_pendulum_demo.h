#ifndef ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H
#define ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "gravity_object.h"
#include "link_constraint.h"
#include "scs.h"

class DoublePendulumDemo : public Demo {
    public:
        DoublePendulumDemo();
        virtual ~DoublePendulumDemo();
    
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();
    
    protected:
        atg_scs::RigidBodySystem m_rigidBodySystem;
        BarObject m_pendulum0;
        BarObject m_pendulum1;
        BarObject m_pendulum2;
    
        GravityObject m_gravity;
        LinkConstraint m_link0;
        LinkConstraint m_link1;
        LinkConstraint m_link2;

        atg_scs::FixedPositionConstraint m_c0;
        atg_scs::FixedPositionConstraint m_c1;
    
        double m_r0;
        double m_r1;
};

#endif /* ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H */
