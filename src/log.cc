FILE *logOutputFile = nullptr;

void initLogOutputFile(char *fileName){
    logOutputFile = fopen(fileName, "w");
#if(PLAT_WINDOWS)
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(logOutputFile, "(+) [%02d:%02d:%02d %02d/%02d/%02d]\n", time.wHour, time.wMinute, time.wSecond, time.wDay, time.wMonth, time.wYear);
#endif
};
void uninitLogOutputFile(){
#if(PLAT_WINDOWS)
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(logOutputFile, "(-) [%02d:%02d:%02d %02d/%02d/%02d]\n", time.wHour, time.wMinute, time.wSecond, time.wDay, time.wMonth, time.wYear);
#endif
    fclose(logOutputFile);
};

void log(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    FILE *out = (logOutputFile==nullptr)?stdout:logOutputFile;
    vfprintf(out, fmt, args);
    va_end(args);
};
void dlog(const char *fmt, ...){
#if(DBG)
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
#endif
};
