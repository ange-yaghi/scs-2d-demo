#ifndef ATG_SCS_2D_DEMO_SPRING_MASS_DEMO_H
#define ATG_SCS_2D_DEMO_SPRING_MASS_DEMO_H

#include "demo.h"

#include "demo_objects.h"

class SpringMassDemo : public Demo {
    public:
        SpringMassDemo();
        virtual ~SpringMassDemo();

        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

    protected:
        atg_scs::GenericRigidBodySystem m_rigidBodySystem;
};

#endif /* ATG_SCS_2D_DEMO_SPRING_MASS_DEMO_H */
