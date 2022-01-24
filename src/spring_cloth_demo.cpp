#include "../include/spring_cloth_demo.h"

#include "../include/demo_application.h"

#include <sstream>

SpringClothDemo::SpringClothDemo() {
    setName("Spring Cloth Demo");

    m_steps = 100;
}

SpringClothDemo::~SpringClothDemo() {
    /* void */
}

void SpringClothDemo::initialize() {
    clear();

    setTargetSystem(&m_rigidBodySystem);
    m_rigidBodySystem.reset();
    m_rigidBodySystem.initialize(
        new atg_scs::GaussianEliminationSleSolver, new atg_scs::Rk4OdeSolver);

    constexpr int ClothNodes = 6;
    constexpr double ClothWidth = 8.0;
    constexpr double UnitWidth = ClothWidth / (ClothNodes - 1);

    atg_scs::RigidBody **nodes = new atg_scs::RigidBody *[ClothNodes * ClothNodes];
    for (int i = 0; i < ClothNodes; ++i) {
        for (int j = 0; j < ClothNodes; ++j) {
            setActiveBody(nullptr);
            if (j != ClothNodes - 1) {
                setCursor(i * UnitWidth - ClothWidth / 2 + 0.1 * j, j * UnitWidth - ClothWidth / 2);
                nodes[i * ClothNodes + j] = &createLinkedDisk(0.5, 0.1)->m_body;
            }
            else {
                setCursor(i * UnitWidth - ClothWidth / 2, j * UnitWidth - ClothWidth / 2);
                EmptyObject *anchor = createEmpty(EmptyObject::Style::FixedPosition);
                anchor->m_body.theta = ysMath::Constants::PI;
                nodes[i * ClothNodes + j] = &anchor->m_body;
            }

            if (i > 0 && j != ClothNodes - 1) {
                SpringObject *spring = connectSpring(
                        nodes[(i - 1) * ClothNodes + j],
                        nodes[(i - 1) * ClothNodes + j]->p_x,
                        nodes[(i - 1) * ClothNodes + j]->p_y);
                spring->m_spring.m_ks = 20;
                spring->m_spring.m_kd = 1;
                spring->m_radius = 0.1;
                spring->m_coilCount = 3;
            }
            
            if (j > 0) {
                SpringObject *spring = connectSpring(
                        nodes[i * ClothNodes + j - 1],
                        nodes[i * ClothNodes + j - 1]->p_x,
                        nodes[i * ClothNodes + j - 1]->p_y);
                spring->m_spring.m_ks = 20;
                spring->m_spring.m_kd = 1;
                spring->m_radius = 0.1;
                spring->m_coilCount = 3;
            }
        }
    }

    GravityObject *g = createObject<GravityObject>(&m_rigidBodySystem);
    g->m_gravity.m_g = 10;

    createControlSpring(5.0, 1.0);
    createMouseEmpty(EmptyObject::Style::Invisible);
}

void SpringClothDemo::process(float dt) {
    Demo::process(dt);

    m_rigidBodySystem.process(1 / 60.0, m_steps);

    m_dt = 1 / 60.0f;
    m_odeSolveMicroseconds = m_rigidBodySystem.getOdeSolveMicroseconds();
    m_forceEvalMicroseconds = m_rigidBodySystem.getForceEvalMicroseconds();
    m_constraintEvalMicroseconds = m_rigidBodySystem.getConstraintEvalMicroseconds();
    m_constraintSolveMicroseconds = m_rigidBodySystem.getConstraintSolveMicroseconds();
}

void SpringClothDemo::render() {
    m_app->drawGrid();

    renderObjects();
}
