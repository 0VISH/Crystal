FILE *logOutputFile = nullptr;

void initLogOutputFile(char *fileName){
    logOutputFile = fopen(fileName, "w");
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(logOutputFile, "(+) [%02d:%02d:%02d %02d/%02d/%02d]\n", time.wHour, time.wMinute, time.wSecond, time.wDay, time.wMonth, time.wYear);
};
void uninitLogOutputFile(){
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(logOutputFile, "(-) [%02d:%02d:%02d %02d/%02d/%02d]\n", time.wHour, time.wMinute, time.wSecond, time.wDay, time.wMonth, time.wYear);
    fclose(logOutputFile);
};

void _log(char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    FILE *out = (logOutputFile==nullptr)?stdout:logOutputFile;
    vfprintf(out, fmt, args);
    va_end(args);
};
void _dlog(char *file, u32 line, const char *fmt, ...){
    printf("%s(%d): ", file, line);
#if(DBG)
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
#endif
};
