#ifndef ATG_SCS_2D_DEMO_EMPTY_OBJECT_H
#define ATG_SCS_2D_DEMO_EMPTY_OBJECT_H

#include "demo_object.h"

class EmptyObject : public DemoObject {
    public:
        enum class Style {
            FixedPosition,
            Invisible
        };

    public:
        EmptyObject();
        virtual ~EmptyObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        atg_scs::RigidBody m_body;
        Style m_style;
};

#endif /* ATG_SCS_2D_DEMO_EMPTY_OBJECT_H */
