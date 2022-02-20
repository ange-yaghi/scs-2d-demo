#ifndef ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H
#define ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "disk_object.h"
#include "plotter.h"
#include "constant_rotation_constraint.h"
#include "scs.h"

class DoublePendulumDemo : public Demo {
    public:
        DoublePendulumDemo();
        virtual ~DoublePendulumDemo();
    
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();
    
    protected:
        atg_scs::OptimizedNsvRigidBodySystem m_rigidBodySystem;

        DiskObject *m_end;
        Plotter *m_plotter;
        ConstantRotationConstraint *m_motor;

        bool m_motorOn;
};

#endif /* ATG_SCS_2D_DEMO_DOUBLE_PENDULUM_DEMO_H */
