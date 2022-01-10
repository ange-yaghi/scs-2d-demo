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

        void setName(const std::string &name);
        void setApplication(DemoApplication *application);

        virtual void initialize();
        virtual void render();
        virtual void process(float dt);

    protected:
        void addObject(DemoObject *object, atg_scs::RigidBodySystem *system);
        
        void renderObjects();
        void processObjects(float dt);

        DemoApplication *m_app;
        std::string m_name;

        std::vector<DemoObject *> m_objects;
};

#endif /* ATG_SCS_2D_DEMO_DEMO_H */
