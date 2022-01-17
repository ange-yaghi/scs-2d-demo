#ifndef ATG_SCS_2D_DEMO_BAR_OBJECT_H
#define ATG_SCS_2D_DEMO_BAR_OBJECT_H

#include "demo_object.h"

class BarObject : public DemoObject {
    public:
        BarObject();
        virtual ~BarObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        void configure(float length, float density);
        float getLength() const { return m_length; }

        atg_scs::RigidBody m_body;

    protected:
        float m_length;
};

#endif /* ATG_SCS_2D_DEMO_BAR_OBJECT_H */
