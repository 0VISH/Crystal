#pragma once

typedef void  (*setGameFolderType)(char *path);
typedef void  (*logType)(char *fmt, ...);
//only for editor
typedef void (*editorSignalType)();
