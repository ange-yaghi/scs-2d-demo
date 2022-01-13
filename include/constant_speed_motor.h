#ifndef ATG_SCS_2D_DEMO_CONSTANT_SPEED_MOTOR_H
#define ATG_SCS_2D_DEMO_CONSTANT_SPEED_MOTOR_H

#include "demo_object.h"

class ConstantSpeedMotor : public DemoObject {
    public:
        ConstantSpeedMotor();
        virtual ~ConstantSpeedMotor();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);

        atg_scs::ConstantSpeedMotor m_motor;
        float m_local_x;
        float m_local_y;

    public:
        float m_theta;
};

#endif /* ATG_SCS_2D_DEMO_CONSTANT_SPEED_MOTOR_H */
