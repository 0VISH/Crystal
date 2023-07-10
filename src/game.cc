namespace Game{
    extern Scene **engineScenePointer;
};

namespace Cry{
    ShaderSystem &getShaderSystemRef(){
	return engine->ss;
    };
    MaterialSystem &getMaterialSystemRef(){
	return engine->ms;
    };

    void setupGamePointers(){
	Game::engineScenePointer = &engine->curScene;
    };
};
