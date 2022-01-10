#ifndef ATG_SCS_2D_DEMO_OBJECT_H
#define ATG_SCS_2D_DEMO_OBJECT_H

#include "scs.h"

class DemoApplication;

class DemoObject {
    public:
        DemoObject();
        virtual ~DemoObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        void setVisible(bool visible) { m_visible = visible; }
        bool isVisible() const { return m_visible; }

    protected:
        bool m_visible;
};

#endif /* ATG_SCS_2D_DEMO_OBJECT_H */
