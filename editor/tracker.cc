namespace Tracker{
    enum class Command{
	UNDO,
	REDO,
	TRANSLATE,
    };
    struct CommandBase{
	CommandBase *prevCmd;
	Command cmd;
	Entity  e;
    };
    struct Translate : CommandBase{
	glm::vec3 oldPos;
	glm::vec3 newPos;
    };

    const u64 cmdBufferSize = 100000;
    char *cmds;
    char *watermark;
    CommandBase *prevCommand;
    //to save old data;
    static union{
	glm::vec3 vec3;
    };

    void init(){
	cmds = (char*)mem::alloc(cmdBufferSize);
	watermark = cmds;
	prevCommand = nullptr;
    };
    void uninit(){
	mem::free(cmds);
    };
    char *allocCmd(Command cmd, Entity e, u64 size){
	if(watermark+size >= cmds+cmdBufferSize){
	    watermark = cmds;
	};
	char *mem = watermark;
	watermark += size;
	CommandBase *base = (CommandBase*)mem;
	base->cmd = cmd;
	base->e   = e;
	base->prevCmd = prevCommand;
	prevCommand = base;
	return mem;
    };
    void translate(Entity e, glm::vec3 &newPos){
	Translate *trans = (Translate*)allocCmd(Command::TRANSLATE, e, sizeof(Translate));
	trans->oldPos = vec3;
	trans->newPos = newPos;
    };
    void undoredo(Command ur){
	if(prevCommand == nullptr && ur == Command::UNDO){
	    watermark = cmds;
	    print("Nothing left to undo");
	    return;
	};
	CommandBase *base = prevCommand;
	prevCommand = base->prevCmd;
	watermark = (char*)base;
	switch(base->cmd){
	case Command::TRANSLATE:{
	    Component::Transform *trans = (Component::Transform*)getComponent(base->e, ComponentID::TRANSFORM);
	    Translate *tr = (Translate*)base;
	    if(ur == Command::UNDO){
		trans->translation = tr->oldPos;
	    }else{
		trans->translation = tr->newPos;
	    };
	    glm::vec3 t = trans->translation;
	    print("Changed entity %d translation to (%f, %f, %f)", base->e, t.x, t.y, t.z);
	}break;
	default:{
	    print("[error] unkown command to undo: %d", base->cmd);
	}break;
	};
    };
};
