#ifndef ATG_SCS_2D_DEMO_FIXED_POSITION_CONSTRAINT_H
#define ATG_SCS_2D_DEMO_FIXED_POSITION_CONSTRAINT_H

#include "demo_object.h"

class FixedPositionConstraint : public DemoObject {
    public:
        FixedPositionConstraint();
        virtual ~FixedPositionConstraint();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::FixedPositionConstraint m_link;
        float m_angle;
};

#endif /* ATG_SCS_2D_DEMO_FIXED_POSITION_CONSTRAINT_H */
