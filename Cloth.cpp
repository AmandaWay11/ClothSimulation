#include <iostream>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>

const int ROWS = 10;
const int COLS = 10;
const double MASS = 0.1;
const double REST_LENGTH = 0.1;
const double K = 100;
const double DAMPING = 0.5;

class Cloth {
public:
    Cloth(btDynamicsWorld* world) : world_(world) {
        createParticles();
        createConstraints();
    }

    void update() {
        // apply forces to the cloth
        // ...
        for (int i = 0; i < particles_.size(); i++) {
            particles_[i]->applyCentralForce(btVector3(0, -9.8, 0));
        }
        // solve constraints
        for (int i = 0; i < constraints_.size(); i++) {
            constraints_[i]->solve();
        }
        world_->stepSimulation(1.0 / 60.0);
    }

    void draw() {
        // draw the cloth
        // ...
    }

private:
    void createParticles() {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                btVector3 pos(r * REST_LENGTH, c * REST_LENGTH, 0);
                btCollisionShape* shape = new btSphereShape(0.02);
                btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), pos));
                btRigidBody::btRigidBodyConstructionInfo info(MASS, state, shape);
                btRigidBody* body = new btRigidBody(info);
