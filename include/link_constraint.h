#ifndef ATG_SCS_2D_DEMO_LINK_CONSTRAINT_H
#define ATG_SCS_2D_DEMO_LINK_CONSTRAINT_H

#include "demo_object.h"

class LinkConstraint : public DemoObject {
    public:
        LinkConstraint();
        virtual ~LinkConstraint();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::LinkConstraint m_link;
};

#endif /* ATG_SCS_2D_DEMO_LINK_CONSTRAINT_H */
