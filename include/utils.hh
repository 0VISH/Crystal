#pragma once

typedef void (*LayerFunc)();

typedef void  (*setGameCodeType)(char *path);
typedef LayerFunc (*setSceneType)(char *path);
typedef void  (*setMaterialSystemType)(char *path);
typedef void  (*logType)(char *fmt, ...);
//only for editor
typedef void (*editorSignalType)();
