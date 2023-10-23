#define SETUP_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l,				\
				     setGameCodeType sgct, setSceneType sct, \
				     setMaterialSystemType smst,	\
				     allocType at, freeType ft,		\
				     editorSignalType est))dlsym(HANDLE, "setupUtilPointers"); \
    setupUtilPointer(print, nullptr, setScene, setMaterialSystem, mem::alloc, mem::free, nullptr); \
									\
    auto setupPointers = (void(*)(materialRegisterEntityType mret, newMaterialType nmt, \
				  serializeMaterialSystemType smst, deserializeMaterialSystemType dmst,	\
				  componentPoolInitType cpit, componentPoolAddComponentType cpact, \
				  allocAndSetCurrentSceneType ascst, uninitAndFreeCurrentSceneType ufcst, \
				  initCurrentSceneType icst, setActiveCameraToCurrentSceneType sacct, \
				  serializeCurrentSceneType secst,	\
				  sceneNewEntityType snet, getEntityType get, \
				  removeComponentType rct, getComponentType gct, \
				  createRigidBodyType crbt, createBoxColliderFixtureType cbcft, \
				  getEngineType gent,			\
				  isKeyDownType ikdt))dlsym(HANDLE, "setupPointers"); \
    setupPointers(materialRegisterEntity,  newMaterial,			\
		  serializeMaterialSystem, deserializeMaterialSystem,	\
		  componentPoolInit, componentPoolAddComponent,		\
		  allocAndSetCurrentScene, uninitAndFreeCurrentScene,	\
		  initCurrentScene, setActiveCameraToCurrentScene,	\
		  serializeCurrentScene,				\
		  sceneNewEntity, getEntity,				\
		  removeComponent, getComponent,			\
		  createRigidBody, createBoxColliderFixture,		\
		  getEngine,						\
		  nullptr);						\
