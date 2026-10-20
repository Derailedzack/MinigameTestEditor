#include <lua-5.1/lua.h>
#include <lua-5.1/lauxlib.h>
#include <lua-5.1/lualib.h>
#include "PropEntity.h"
#include "Entity.h"
extern SDL_Color Empty_Color;
extern struct EntityData* CurrentEntities;
char PropName[1024];
lua_Debug PropScript_Debug;
int Script_PropToEntArray(lua_State* L){

    return 0;
}
int Script_ConvertPropToEntity(lua_State* L){
    
    luaL_checktype(L,1,LUA_TTABLE);
    lua_getfield(L,-1,"width");
    int width = lua_tointeger(L,-1);
    lua_getfield(L,-1,"height");
    int height = lua_tointeger(L,-1);
    lua_getfield(L,-1,"width_render");
    int width_scale = lua_tointeger(L,-1);
    lua_getfield(L,-1,"height_render");
    int height_scale = lua_tointeger(L,-1);
    lua_getfield(L,-1,"tex_path");
    const char* text_path = lua_tostring(L,-1);
    struct EntityData* entity = Entity_Create("LuaEntity",text_path,Empty_Color,0,0,width,height,width_scale,height_scale);
    lua_pushlightuserdata(L,entity);
   // lua_rawget(L,-1);
    return 1;
}
luaL_Reg Prop_Lib[] = {
    "AddPropToEntArray",Script_PropToEntArray,
    "ConvertToEntity",Script_ConvertPropToEntity,
    NULL,NULL 
};
lua_State* Prop_ScriptState;
void InitPropDef(){
    Prop_ScriptState = luaL_newstate();
    if(Prop_ScriptState == NULL){
        printf("Failed to init Prop Lua State!\n");
        exit(-1);
    }
    luaL_openlib(Prop_ScriptState,"",Prop_Lib,0);

}
struct EntityData* CreateFromScript(const char* script_fn){
    InitPropDef();
    
    if(luaL_dofile(Prop_ScriptState,script_fn) == 1){
        printf("%s\n",lua_tostring(Prop_ScriptState,-1));
        exit(-2);
        //lua_getstack(Prop_ScriptState,4,&PropScript_Debug);
        //printf("%s\n",PropScript_Debug.source);
    }
    //snprintf(PropName,1024,"_G.PropEntity[%s]",PropName);
    //lua_getglobal(Prop_ScriptState,PropName);

}