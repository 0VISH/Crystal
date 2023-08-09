#include "box2d/box2d.h"

b2Body *createPhysicsBody(b2BodyDef *def, b2World *world){
    return world->CreateBody(def);
};
