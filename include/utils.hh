#pragma once

typedef void  (*setGameCodeType)(char *path);
typedef void  (*setSceneType)(char *path);
typedef void  (*setMaterialSystemType)(char *path);
typedef void  (*logType)(char *fmt, ...);
typedef void* (*allocType)(u64 size);
typedef void  (*freeType)(void *ptr);
//only for editor
typedef void (*editorSignalType)();
