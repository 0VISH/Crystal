#if(DBG)

void unreachable(char *file, u32 line) {
    print("\n[ERROR] unreachable area reached: %s:%d", file, line);
};
#define UNREACHABLE unreachable(__FILE__, __LINE__)
void ass(bool x, char *file, u32 line){
    if(x){return;};
    print("\n%s:%d assertion failed\n", file, line);
};
#define ASSERT(expr)   ass(expr, __FILE__, __LINE__)
#else
#define UNREACHABLE
#define ASSERT(expr)
#endif
