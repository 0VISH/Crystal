namespace GameLayer{
    bool onUpdate(Event e, f64 dt){
	Scene *s = engine->curScene;
	if(s == nullptr || s->state != SceneState::PLAYING){return false;};
	bool res;
	if(s->onUpdate != nullptr){res=s->onUpdate(e, dt);};
        const u32 hertz = 60;
	const f32 timeStamp = 1/hertz;
	s32 velocityIterations = 6;
	s32 positionIterations = 2;
	for(u32 x=0; x<hertz; x+=1){
	    s->physicsWorld->Step(timeStamp, velocityIterations, positionIterations);
	};
	if(s->components.count <= (u32)ComponentID::RIGIDBODY){
	    return res;
	};
	ComponentPool &cp = s->components[(u32)ComponentID::RIGIDBODY];
	for(u32 x=0; x<cp.entityWatermark; x+=1){
	    if(cp.entityToComponentOff[x] == -1){
		continue;
	    };
	    auto *trans = (Component::Transform*)getComponent(x, (u32)ComponentID::TRANSFORM);
	    if(trans == nullptr){continue;};
	    auto *rb = (Component::RigidBody*)getComponent(x, (u32)ComponentID::RIGIDBODY);
	    if(rb == nullptr){continue;};
	    auto *body = rb->runtimeBody;
	    auto pos = body->GetPosition();
	    trans->position.x = pos.x;
	    trans->position.y = pos.y;
	    print("%f %f", pos.x, pos.y);
	    auto angle = body->GetAngle();
	    print("%f", angle);
	    trans->rotation.x = angle;
	};
	return res;
    };
    void onRender(){
	Scene *s = engine->curScene;
	if(s == nullptr){return;};
	if(s->onRender != nullptr && s->state == SceneState::PLAYING){s->onRender();};
	Entity e = s->activeCam;
	if(e < 0){return;};
	auto *cam = (Component::PCamera*)getComponent(e, (u32)ComponentID::PCAMERA);
	cam->calculateViewMat();

	fillRenderBufferHeader(engine->r, cam->projection * cam->view);
	fillRenderBufferWithGivenMS(engine->r, engine->ms);
    };
    void onUninit(){
	Scene *s = engine->curScene;
	if(s == nullptr){return;};
	if(s->onUninit){
	    s->onUninit();
	};
	uninitAndFreeCurrentScene();
    };
};
