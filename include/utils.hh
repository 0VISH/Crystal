#pragma once

typedef void  (*setGameFolderType)(char *path);
typedef u32   (*getComponentUIDType)();
typedef void  (*logType)(char *fmt, ...);
//only for editor
typedef void (*editorSignalType)();
