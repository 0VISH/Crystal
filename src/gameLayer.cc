namespace GameLayer{
    bool onUpdate(Event e, f64 dt){
	Scene *s = engine->curScene;
	if(s == nullptr || s->state != SceneState::PLAYING){return false;};
	bool res;
	if(s->onUpdate != nullptr){res=s->onUpdate(e, dt);};
	//TODO: update physics
	return res;
    };
    void onRender(){
	Scene *s = engine->curScene;
	if(s == nullptr){return;};
	if(s->onRender != nullptr && s->state == SceneState::PLAYING){s->onRender();};
	Entity e = s->activeCam;
	if(e < 0){return;};
	auto *cam = (Component::PCamera*)getComponent(e, (u32)ComponentID::CAMERA);
	cam->calculateViewMat();

	fillRenderBufferHeader(engine->r, cam->projection * cam->view);
	fillRenderBufferWithGivenMS(engine->r, engine->ms);
    };
    void onUninit(){
	Scene *s = engine->curScene;
	if(s->onUninit){
	    s->onUninit();
	};
    };
};
