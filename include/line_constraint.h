#ifndef ATG_SCS_2D_DEMO_LINE_CONSTRAINT_H
#define ATG_SCS_2D_DEMO_LINE_CONSTRAINT_H

#include "demo_object.h"

class LineConstraint : public DemoObject {
    public:
        LineConstraint();
        virtual ~LineConstraint();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::LineConstraint m_constraint;
        float m_trackLength;
};

#endif /* ATG_SCS_2D_DEMO_LINE_CONSTRAINT_H */
