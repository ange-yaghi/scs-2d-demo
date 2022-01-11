#ifndef ATG_SCS_2D_DEMO_SPRING_OBJECT_H
#define ATG_SCS_2D_DEMO_SPRING_OBJECT_H

#include "demo_object.h"

class SpringObject : public DemoObject {
    public:
        SpringObject();
        virtual ~SpringObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::Spring m_spring;

        int m_coilCount;
};

#endif /* ATG_SCS_2D_DEMO_SPRING_OBJECT_H */
