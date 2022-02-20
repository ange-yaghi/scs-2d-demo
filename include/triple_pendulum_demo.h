#ifndef ATG_SCS_2D_DEMO_TRIPLE_PENDULUM_DEMO_H
#define ATG_SCS_2D_DEMO_TRIPLE_PENDULUM_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "disk_object.h"
#include "gravity_object.h"
#include "link_constraint.h"
#include "spring_object.h"
#include "line_constraint.h"
#include "plotter.h"
#include "scs.h"

class TriplePendulumDemo : public Demo {
    public:
        TriplePendulumDemo();
        virtual ~TriplePendulumDemo();
    
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();
    
    protected:
        atg_scs::GenericRigidBodySystem m_rigidBodySystem;

        DiskObject *m_end;
        Plotter *m_plotter;
};

#endif /* ATG_SCS_2D_DEMO_TRIPLE_PENDULUM_DEMO_H */
