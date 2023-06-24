namespace Game{
    void init(){
	engine->r.drawWireframe();
    };
    void render(){
	engine->r.drawQuad();
    };
    void uninit(){
    };
    bool update(Event e){
	return false;
    };

    char* gameName  = "Sandbox";
};
