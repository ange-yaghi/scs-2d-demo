#ifndef ATG_SCS_2D_DEMO_MOTOR_DEMO_H
#define ATG_SCS_2D_DEMO_MOTOR_DEMO_H

#include "demo.h"

#include "bar_object.h"
#include "disk_object.h"
#include "gravity_object.h"
#include "link_constraint.h"
#include "spring_object.h"
#include "line_constraint.h"
#include "constant_speed_motor.h"
#include "scs.h"

class MotorDemo : public Demo {
    public:
        MotorDemo();
        virtual ~MotorDemo();
    
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();
    
    protected:
        atg_scs::GenericRigidBodySystem m_rigidBodySystem;

        BarObject m_bar0;
        BarObject m_bar1;
        DiskObject m_disk;
        ConstantSpeedMotor m_motor;
        GravityObject m_gravity;
        LinkConstraint m_link0;
        LinkConstraint m_link1;

        atg_scs::RigidBody m_motorMount;

        atg_scs::FixedPositionConstraint m_c0;
};

#endif /* ATG_SCS_2D_DEMO_MOTOR_DEMO_H */
