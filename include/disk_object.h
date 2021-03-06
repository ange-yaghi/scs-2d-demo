#ifndef ATG_SCS_2D_DEMO_DISK_OBJECT_H
#define ATG_SCS_2D_DEMO_DISK_OBJECT_H

#include "demo_object.h"

class DiskObject : public DemoObject {
    public:
        DiskObject();
        virtual ~DiskObject();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;
        virtual void onClick(double x, double y, ClickEvent *clickEvent);

        void configure(double radius, double density);

        atg_scs::RigidBody m_body;

    protected:
        float m_radius;
};

#endif /* ATG_SCS_2D_DEMO_DISK_OBJECT_H */
