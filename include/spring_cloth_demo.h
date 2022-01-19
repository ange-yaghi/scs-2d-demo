#ifndef ATG_SCS_2D_SPRING_CLOCK_DEMO_H
#define ATG_SCS_2D_SPRING_CLOCK_DEMO_H

#include "demo.h"

#include "demo_objects.h"

class SpringClothDemo : public Demo {
    public:
        SpringClothDemo();
        virtual ~SpringClothDemo();

        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

    protected:
        atg_scs::RigidBodySystem m_rigidBodySystem;
};

#endif /* ATG_SCS_2D_DEMO_SPRING_CLOCK_DEMO_H */
