#include <lua-5.1/lua.h>
#include <lua-5.1/lauxlib.h>
#include <lua-5.1/lualib.h>
#include "Entity.h"
extern struct EntityData* CurrentEntities;
int Script_PropToEntArray(lua_State* L){

}
luaL_Reg Prop_Lib = {
    "AddPropToEntArray",
    NULL,NULL 
};
lua_State* Prop_ScriptState;
void InitPropDef(){
    Prop_ScriptState = luaL_newstate();
    if(Prop_ScriptState == NULL){
        printf("Failed to init Prop Lua State!\n");
        exit(-1);
    }

}