#ifndef ATG_SCS_2D_DEMO_DEMO_H
#define ATG_SCS_2D_DEMO_DEMO_H

#include "demo_object.h"

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

        std::string getName() const { return m_name; }

        int getSteps() const { return m_steps; }
        float getTimestep() const { return m_dt; }
        float getOdeSolveMicroseconds() const { return m_odeSolveMicroseconds; }
        float getForceEvalMicroseconds() const { return m_forceEvalMicroseconds; }
        float getConstraintEvalMicroseconds() const { return m_constraintEvalMicroseconds; }
        float getConstraintSolveMicroseconds() const { return m_constraintSolveMicroseconds; }

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
};

#endif /* ATG_SCS_2D_DEMO_DEMO_H */
