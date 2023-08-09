#include "box2d/box2d.h"

b2Body *createRigidBody(b2BodyDef *def, b2World *world){
    return world->CreateBody(def);
};

b2Fixture *createBoxColliderFixture(f32 x, f32 y, f32 density, f32 friction, b2Body *body){
    b2PolygonShape box;
    box.SetAsBox(x, y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = density;
    fixtureDef.friction = friction;

    return body->CreateFixture(&fixtureDef);
};
