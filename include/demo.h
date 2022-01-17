#ifndef ATG_SCS_2D_DEMO_DEMO_H
#define ATG_SCS_2D_DEMO_DEMO_H

#include "demo_object.h"

#include "bar_object.h"
#include "disk_object.h"
#include "spring_object.h"
#include "fixed_position_constraint.h"
#include "constant_speed_motor.h"
#include "empty_object.h"

#include <string>
#include <vector>

class DemoApplication;

class Demo {
    public:
        Demo();
        virtual ~Demo();

        void reset();
        void setName(const std::string &name);
        void setApplication(DemoApplication *application);

        virtual void initialize();
        virtual void render();
        virtual void process(float dt);
        double energy(atg_scs::RigidBodySystem *system = nullptr);

        std::string getName() const { return m_name; }

        int getSteps() const { return m_steps; }
        float getTimestep() const { return m_dt; }
        float getOdeSolveMicroseconds() const { return m_odeSolveMicroseconds; }
        float getForceEvalMicroseconds() const { return m_forceEvalMicroseconds; }
        float getConstraintEvalMicroseconds() const { return m_constraintEvalMicroseconds; }
        float getConstraintSolveMicroseconds() const { return m_constraintSolveMicroseconds; }

        template <typename T>
        T *createObject(atg_scs::RigidBodySystem *system) {
            T *newObject = new T;
            addObject(newObject, system);
            return newObject;
        }
        void clear();

    protected:
        void addObject(DemoObject *object, atg_scs::RigidBodySystem *system);

        void renderObjects();
        void processObjects(float dt);

        DemoApplication *m_app;
        std::string m_name;

        std::vector<DemoObject *> m_objects;

        int m_steps;
        float m_dt;
        float m_odeSolveMicroseconds;
        float m_forceEvalMicroseconds;
        float m_constraintEvalMicroseconds;
        float m_constraintSolveMicroseconds;

    protected:
        double m_cursor_x;
        double m_cursor_y;
        atg_scs::RigidBody *m_activeBody;

        void setCursor(double x, double y);
        void moveCursor(double dx, double dy);
        void setTargetSystem(atg_scs::RigidBodySystem *system);
        void setActiveBody(atg_scs::RigidBody *body);
        void moveToLocal(double lx, double ly);
        FixedPositionConstraint *fixObject(double x, double y);
        BarObject *createLinkedBar(double x, double y, double density);
        DiskObject *createLinkedDisk(double r, double density);
        EmptyObject *createEmpty(EmptyObject::Style style);
        SpringObject *connectSpring(atg_scs::RigidBody *target, double x, double y);
        ConstantSpeedMotor *createMotor(atg_scs::RigidBody *base);
        void moveBefore(DemoObject *a, DemoObject *b);

        atg_scs::RigidBodySystem *m_targetSystem;
};

#endif /* ATG_SCS_2D_DEMO_DEMO_H */
