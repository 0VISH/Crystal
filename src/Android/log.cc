#include <stdarg.h>

void dlog(char *fmt, ...){
#if(DBG)
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_DEBUG, "LOG", fmt, args);
    va_end(args);
#endif
};

//TODO: file writter
