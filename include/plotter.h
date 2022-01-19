#ifndef ATG_SCS_2D_DEMO_PLOTTER_H
#define ATG_SCS_2D_DEMO_PLOTTER_H

#include "demo_object.h"

#include "delta.h"

class Plotter : public DemoObject {
    public:
        Plotter();
        virtual ~Plotter();

        virtual void initialize(atg_scs::RigidBodySystem *system);
        virtual void reset();
        virtual void render(DemoApplication *app);
        virtual void process(float dt, DemoApplication *app);
        virtual double energy() const;

        void addPoint(const ysVector2 &p);
        void setSize(int bufferSize);
        void destroy();

    protected:
        int m_writeIndex;
        int m_bufferSize;
        int m_pointCount;
        ysVector2 *m_points;
};

#endif /* ATG_SCS_2D_DEMO_PLOTTER_H */
