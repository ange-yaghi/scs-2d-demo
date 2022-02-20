#ifndef ATG_SCS_2D_DEMO_COMPLEX_ROLLER_DEMO_H
#define ATG_SCS_2D_DEMO_COMPLEX_ROLLER_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "disk_object.h"
#include "gravity_object.h"
#include "link_constraint.h"
#include "spring_object.h"
#include "line_constraint.h"
#include "plotter.h"
#include "scs.h"

class ComplexRollerDemo : public Demo {
    public:
        ComplexRollerDemo();
        virtual ~ComplexRollerDemo();

        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

    protected:
        atg_scs::GenericRigidBodySystem m_rigidBodySystem;
};

#endif /* ATG_SCS_2D_DEMO_COMPLEX_ROLLER_DEMO_H */
