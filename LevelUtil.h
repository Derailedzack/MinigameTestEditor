#pragma once
#include <lua.h>
int Script_AddPropsToCurrent(lua_State* L);
int Script_AddWallToEntites(lua_State* L);
int Script_ConvertToEntityDat(lua_State* L);
void WriteLevelToScript(const char* level_path);
void LoadLevelFromScript(const char* level_path);
//void WriteLevelToLua();