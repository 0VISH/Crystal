#pragma once



typedef void (*materialInitType)(Material &m, u32 s);
typedef void (*materialUninitType)(Material &m);
typedef void (*materialRegisterEntityType)(Material &m, Entity e);

typedef void (*materialSystemInitType)(MaterialSystem &ms, u32 materialCount);
typedef void (*materialSystemUninitType)(MaterialSystem &ms);
typedef Material& (*newMaterialType)(MaterialSystem &ms, u32 shader);
