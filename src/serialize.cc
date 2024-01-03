void serializeString(char *mem, FILE *f){
    u32 len = strlen(mem);
    fwrite(&len, sizeof(len), 1, f);
    fwrite(mem, len, 1, f);
};
void serializeHashmapStr(HashmapStr &map, FILE *f){
    fwrite(&map.count, sizeof(map.count), 1, f);
    for(u32 x=0; x<map.len; x+=1){
	if(map.status[x]){
	    serializeString(map.keys[x].mem, f);
	    fwrite(&map.values[x], sizeof(u32), 1, f);
	};
    };
};
inline void serializeu32(u32 num, FILE *f){
    fwrite(&num, sizeof(num), 1, f);
};
template<typename T>
void serializeDynamicArray(DynamicArray<T> &arr, FILE *f){
    fwrite(&arr.count, sizeof(arr.count), 1, f);
    fwrite(arr.mem, sizeof(T)*arr.count, 1, f);
};

inline u32 deserializeu32(char *mem, u32 &x){
    u32 u = *(u32*)(&mem[x]);
    x += sizeof(u32);
    return u;
};
char* deserializeString(u32 &length, char *mem, u32 &x){
    u32 len = deserializeu32(mem, x);
    char *str = (char*)mem::alloc(len+1);
    memcpy(str, &mem[x], len);
    str[len] = '\0';
    x += len;
    length = len;
    return str;
};
void deserializeHashmapStr(HashmapStr &map, char *mem, u32 &x){
    u32 count = deserializeu32(mem, x);
    map.init(count);
    for(u32 j=0; j<count; j+=1){
	u32 len;
	char *str = deserializeString(len, mem, x);
	u32 value = deserializeu32(mem, x);
	map.insertValue({str, len}, value);
    };
};
template<typename T>
void deserializeDynamicArray(DynamicArray<T> &arr, char *mem, u32 &x){
    u32 count = deserializeu32(mem, x);
    arr.init(count);
    for(u32 j=0; j<count; j+=1){
	T *t = (T*)(&mem[x]);
	arr.push(*t);
	x += sizeof(T);
    };
};
