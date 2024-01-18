namespace Tracker{
    enum class Command{
	TRANSLATE,
    };
    struct CommandBase{
	CommandBase *prevCmd;
	CommandBase *nextCmd;
	Command cmd;
	Entity  e;
    };
    struct Translate : CommandBase{
	glm::vec3 oldPos;
	glm::vec3 curPos;
    };

    const u64 cmdBufferSize = 100000;
    char *cmds;
    char *watermark;
    CommandBase *curCommand;
    //to save old data;
    static union{
	glm::vec3 vec3;
    };

    void init(){
	cmds = (char*)mem::alloc(cmdBufferSize);
	watermark = cmds;
	curCommand = nullptr;
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
	base->prevCmd = curCommand;
	base->nextCmd = nullptr;
	if(curCommand){
	    curCommand->nextCmd = base;
	};
	curCommand = base;
	return mem;
    };
    void translate(Entity e, glm::vec3 &curPos){
	Translate *trans = (Translate*)allocCmd(Command::TRANSLATE, e, sizeof(Translate));
	trans->oldPos = vec3;
	trans->curPos = curPos;
    };
    void undo(){
	if(curCommand == nullptr){
	    watermark = cmds;
	    print("Nothing left to undo");
	    return;
	};
	CommandBase *base = curCommand;
	if(curCommand->prevCmd){
	    curCommand = curCommand->prevCmd;
	};
	watermark = (char*)base;
	switch(base->cmd){
	case Command::TRANSLATE:{
	    Component::Transform *trans = (Component::Transform*)getComponent(base->e, ComponentID::TRANSFORM);
	    Translate *tr = (Translate*)base;
	    trans->translation = tr->oldPos;
	    glm::vec3 t = trans->translation;
	    print("Changed entity %d translation to (%f, %f, %f)", base->e, t.x, t.y, t.z);
	}break;
	default:{
	    print("[error] unkown command to undo: %d", base->cmd);
	}break;
	};
    };
    void redo(){
	if(curCommand == nullptr){
	    watermark = cmds;
	    print("Nothing left to redo");
	    return;
	};
	CommandBase *base = curCommand->nextCmd;
	if(base == nullptr){return;};
	curCommand = curCommand->nextCmd;
	watermark = (char*)curCommand;
	switch(base->cmd){
	case Command::TRANSLATE:{
	    Component::Transform *trans = (Component::Transform*)getComponent(base->e, ComponentID::TRANSFORM);
	    Translate *tr = (Translate*)base;
	    trans->translation = tr->curPos;
	    glm::vec3 t = trans->translation;
	    print("Changed entity %d translation to (%f, %f, %f)", base->e, t.x, t.y, t.z);
	    watermark += sizeof(Translate);
	}break;
	default:{
	    print("[error] unkown command to redo: %d", base->cmd);
	}break;
	};
    };
};
