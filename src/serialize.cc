void serializeString(char *mem, u32 len, FILE *f){
    fwrite(&len, sizeof(len), 1, f);
    fwrite(mem, len, 1, f);
};
void serializeHashmapStr(HashmapStr &map, FILE *f){
    fwrite(&map.count, sizeof(map.count), 1, f);
    for(u32 x=0; x<map.len; x+=1){
	if(map.status[x]){
	    serializeString(map.keys[x].mem, map.keys[x].len, f);
	    fwrite(&map.values[x], sizeof(u32), 1, f);
	};
    };
};
template<typename T>
void serializeDynamicArray(DynamicArray<T> &arr, FILE *f){
    fwrite(&arr.count, sizeof(arr.count), 1, f);
    for(u32 x=0; x<arr.count; x+=1){
	fwrite(&arr.mem[x], sizeof(T), 1, f);
    };
};

char* deserializeString(u32 &length, char *mem, u32 &x){
    u32 len = *(u32*)(&mem[x]);
    x += sizeof(len);
    char *str = (char*)mem::alloc(len);
    memcpy(str, &mem[x], len);
    x += len;
    length = len;
    return str;
};
void deserializeHashmapStr(HashmapStr &map, char *mem, u32 &x){
    u32 count = *(u32*)(&mem[x]);
    x += sizeof(count);
    map.init(count);
    for(u32 j=0; x<count; x+=1){
	u32 len;
	char *str = deserializeString(len, mem, x);
	u32 value = *(u32*)(&mem[x]);
	x += sizeof(count);
	map.insertValue({str, len}, value);
    };
};
template<typename T>
void deserializeDynamicArray(DynamicArray<T> &arr, char *mem, u32 &x){
    u32 count = *(u32*)(&mem[x]);
    x += sizeof(count);
    arr.init(count);
    for(u32 x=0; x<count; x+=1){
	T *t = (T*)mem;
	arr.insertValue(*T);
    };
};
