#ifndef ATG_SCS_2D_DEMO_SPRING_DOUBLE_PENDULUM_DEMO_H
#define ATG_SCS_2D_DEMO_SPRING_DOUBLE_PENDULUM_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "disk_object.h"
#include "gravity_object.h"
#include "link_constraint.h"
#include "spring_object.h"
#include "line_constraint.h"
#include "plotter.h"
#include "scs.h"

class SpringDoublePendulumDemo : public Demo {
    public:
        SpringDoublePendulumDemo();
        virtual ~SpringDoublePendulumDemo();

        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

    protected:
        atg_scs::RigidBodySystem m_rigidBodySystem;

        DiskObject *m_end;
        Plotter *m_plotter;
};

#endif /* ATG_SCS_2D_DEMO_SPRING_DOUBLE_PENDULUM_DEMO_H */
