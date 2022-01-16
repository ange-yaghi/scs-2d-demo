#ifndef ATG_SCS_2D_DEMO_ROLLING_CONSTRAINT_H
#define ATG_SCS_2D_DEMO_ROLLING_CONSTRAINT_H

#include "demo_object.h"

class RollingConstraint : public DemoObject {
    public:
        RollingConstraint();
        virtual ~RollingConstraint();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::RollingConstraint m_constraint;
};

#endif /* ATG_SCS_2D_DEMO_ROLLING_CONSTRAINT_H */
