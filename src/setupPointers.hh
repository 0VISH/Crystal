#pragma once

#define GET_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l,				\
				     setGameCodeType sgct, setSceneType sct, \
				     setMaterialSystemType smst,	\
				     editorSignalType est))GET_PROC(HANDLE, "setupUtilPointers"); \
									\
    auto setupPointers = (void(*)(loadTextureType ltt, materialRegisterEntityType mret, newMaterialType nmt, \
				  serializeMaterialSystemType smst, deserializeMaterialSystemType dmst,	\
				  componentPoolInitType cpit, componentPoolAddComponentType cpact, \
				  allocAndSetCurrentSceneType ascst, uninitAndFreeCurrentSceneType ufcst, \
				  initCurrentSceneType icst, setActiveCameraToCurrentSceneType sacct, \
				  serializeCurrentSceneType secst,	\
				  newEntityType snet, getEntityType get, \
				  removeComponentType rct, getComponentType gct, \
				  createRigidBodyType crbt, createBoxColliderFixtureType cbcft, \
				  getEngineType gent,			\
				  isKeyDownType ikdt))GET_PROC(HANDLE, "setupPointers"); \

#if(AND)
#define SET_POINTERS							\
    setupUtilPointer(print, nullptr, setScene, setMaterialSystem, nullptr); \
    setupPointers(loadTexture, materialRegisterEntity,  newMaterial,	\
		  serializeMaterialSystem, deserializeMaterialSystem,	\
		  componentPoolInit, componentPoolAddComponent,		\
		  allocAndSetCurrentScene, uninitAndFreeCurrentScene,	\
		  initCurrentScene, setActiveCameraToCurrentScene,	\
		  serializeCurrentScene,				\
		  newEntity, getEntity,					\
		  removeComponent, getComponent,			\
		  createRigidBody, createBoxColliderFixture,		\
		  getEngine,						\
		  nullptr);						\
    
#elif(WIN)
#define SET_POINTERS							\
    setupUtilPointer(print, Code::setGameCode, setScene, setMaterialSystem, editorSignal); \
    setupPointers(loadTexture, materialRegisterEntity,  newMaterial,	\
		  serializeMaterialSystem, deserializeMaterialSystem,	\
		  componentPoolInit, componentPoolAddComponent,		\
		  allocAndSetCurrentScene, uninitAndFreeCurrentScene,	\
		  initCurrentScene, setActiveCameraToCurrentScene,	\
		  serializeCurrentScene,				\
		  newEntity, getEntity,					\
		  removeComponent, getComponent,			\
		  createRigidBody, createBoxColliderFixture,		\
		  getEngine,						\
		  isKeyDown);						\

#endif
