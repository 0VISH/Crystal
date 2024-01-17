namespace GameLayer{
    f64 physicsDelta = 0;
    
    bool onUpdate(Event e, f64 dt){
	Scene *s = engine->curScene;
	if(s == nullptr || s->state != SceneState::PLAYING){return false;};
	bool res;
	if(s->onUpdate != nullptr){res=s->onUpdate(e, dt);};
	if(s->components.count <= (u32)ComponentID::RIGIDBODY){
	    return res;
	};
	physicsDelta += dt;
	const u32 hertz = 60;
	const f32 timeStamp = (f32)1/(f32)hertz;
	if(physicsDelta >= timeStamp){
	    const s32 velocityIterations = 6;
	    const s32 positionIterations = 2;
	    s->physicsWorld->Step(1.0f/60.0f, velocityIterations, positionIterations);
	    ComponentPool &cp = s->components[(u32)ComponentID::RIGIDBODY];
	    for(u32 x=0; x<cp.entityWatermark; x+=1){
		if(cp.entityToComponentOff[x] == -1){
		    continue;
		};
		auto *trans = (Component::Transform*)getComponent(x, ComponentID::TRANSFORM);
		if(trans == nullptr){continue;};
		auto *rb = (Component::RigidBody*)getComponent(x, ComponentID::RIGIDBODY);
		if(rb == nullptr){continue;};
		auto *body = rb->runtimeBody;
		auto pos = body->GetPosition();
		trans->translation.x = pos.x;
		trans->translation.y = pos.y;
		auto angle = body->GetAngle();
		trans->rotation.z = angle;
	    };
	    physicsDelta = 0;
	};
	return res;
    };
    void onRender(){
	Scene *s = engine->curScene;
	if(s == nullptr){return;};
	if(s->onRender != nullptr && s->state == SceneState::PLAYING){s->onRender();};
	Entity e = s->activeCam;
	if(e < 0){return;};
	auto *cam = (Component::PCamera*)getComponent(e, ComponentID::PCAMERA);
	ASSERT(cam != nullptr);
	cam->calculateProjectionMat();
	cam->calculateViewMat();;
		
	fillRenderBufferHeader(engine->r, cam->projection * cam->calculateViewMat());
	fillRenderBufferWithGivenMS(engine->r, engine->ms);
    };
    void onUninit(){
	Scene *s = engine->curScene;
	if(s == nullptr){return;};
	uninitAndFreeCurrentScene();
    };
};
