#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "Entity.h"
#include "PropEntity.h"
#include "EditorMode.h"
extern SDL_Color Empty_Color;
//extern struct EntityData* CurrentEntities;
unsigned int Max_Props;
struct EntityData* CurrentProps;
struct EntityData* RegisteredProps;
extern SDL_Renderer* Main_Renderer;
extern EDITOR_MODE CurrentMode;
//char PropName[1024];
lua_Debug PropScript_Debug;
void PropEntity_Init(struct EntityData* data){
    SDL_SetTextureScaleMode(data->entityTex, SDL_SCALEMODE_PIXELART);

}
void PropEntity_Draw(struct EntityData* data){

}
void PropEntity_Update(struct EntityData* data){
    SDL_RenderTexture(Main_Renderer, data->entityTex, &data->entitySprRect, &data->entityRenderRect);
}

int Script_PropToEntArray(lua_State* L){
  //  printf("Test!\n");
    int i = lua_tointeger(L,1);
    if(i > Max_Props){
        lua_pushstring(L,"Props Index is larger then Max_Props!\n");
        lua_error(L);
        return 1;
    }

    CurrentProps[i] = *(struct EntityData*)lua_touserdata(L,2);
    CurrentProps[i].Init = PropEntity_Init;
    CurrentProps[i].Init(&CurrentProps[i]);
    CurrentProps[i].Update = PropEntity_Update;
    return 0;
}
int Script_GetCurrentMode(lua_State* L){
    lua_pushinteger(L,CurrentMode);
    return 1;
}
int Script_ConvertPropToEntity(lua_State* L){
    
    luaL_checktype(L,1,LUA_TTABLE);
    //for (int i = 0; i > -4; i--)
    //{
    lua_getfield(L,1,"width");
    int width = lua_tointeger(L,2);
    lua_getfield(L,1,"height");
    int height = lua_tointeger(L,3);
    lua_getfield(L,1,"width_render");
    int width_scale = lua_tointeger(L,4);
    lua_getfield(L,1,"height_render");
    int height_scale = lua_tointeger(L,5);
    lua_getfield(L,1,"tex_path");
    const char* text_path = lua_tostring(L,6);
    lua_getfield(L,1,"name");
    const char* name = lua_tostring(L,7);
    
           //printf("%i\n",width);
    //}
    //printf("width:%i height:%i name:%s\n",width_scale,height,text_path);

    #if 0
    lua_getfield(L,1,"width");
    int width = lua_tointeger(L,1);
    lua_getfield(L,1,"height");
    int height = lua_tointeger(L,1);
    lua_getfield(L,1,"width_render");
    int width_scale = lua_tointeger(L,1);
    lua_getfield(L,1,"height_render");
    int height_scale = lua_tointeger(L,1);
    lua_getfield(L,1,"tex_path");
    const char* text_path = lua_tostring(L,1);
    struct EntityData* entity = Entity_Create("LuaEntity",text_path,Empty_Color,0,0,width,height,width_scale,height_scale);
    
    lua_pushlightuserdata(L,entity);
   // lua_rawget(L,-1);
    return 1;
    #endif
    struct EntityData* entity = Entity_Create(name,text_path,Empty_Color,64.0f,0.0f,width,height,width_scale,height_scale);
    Entity_CreateTexture(entity,entity->tex_path);
    
    lua_pushlightuserdata(L,entity);
    return 1;
}
//Just remember to call the init function of the prop if it has one (Oh wait no these don't)
int Script_RegisterProp(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int index = luaL_checkinteger(L, 2);
    if (index > Max_Props) {
        luaL_error(L,"Index is larger then Max_Props!\n");
        return 1;
    }
    lua_getfield(L, 1, "width");
    int width = lua_tointeger(L, 3);
    lua_getfield(L, 1, "height");
    int height = lua_tointeger(L, 4);
    lua_getfield(L, 1, "width_render");
    int width_scale = lua_tointeger(L, 5);
    lua_getfield(L, 1, "height_render");
    int height_scale = lua_tointeger(L, 6);
    lua_getfield(L, 1, "tex_path");
    const char* text_path = lua_tostring(L, 7);
    lua_getfield(L, 1, "name");
    const char* name = lua_tostring(L,8);
    //printf("Width=%i,Height=%i,Name=%s,TexPath=%s\n",width,height,name, text_path);

    struct EntityData* entity = Entity_Create(name, text_path, Empty_Color, 0, 0, width, height, width_scale, height_scale);
    RegisteredProps[index] = *entity;
   // SDL_Log("PropGFX_X=%f\n,")
    SDL_Log("PropWidth=%f,PropHeight=%f,PropX=%f,PropY=%f\n", RegisteredProps[index].entityRenderRect.w, RegisteredProps[index].entityRenderRect.h, RegisteredProps[index].entityRenderRect.x, RegisteredProps[index].entityRenderRect.y);
    SDL_Log("Prop_GFX_Width=%f,Prop_GFX_Height=%f,Prop_GFX_X=%f,Prop_GFX_Y=%f\n", RegisteredProps[index].entitySprRect.w, RegisteredProps[index].entitySprRect.h, RegisteredProps[index].entitySprRect.x, RegisteredProps[index].entitySprRect.y);
   // SDL_Log("PropTexturePath=%x\n");
    Entity_CreateTexture(&RegisteredProps[index], text_path);
    PropEntity_Init(&RegisteredProps[index]);

    return 0;
}

int Script_InitPropArray(lua_State* L){
    Max_Props = lua_tointeger(L,1);
    CurrentProps = calloc(Max_Props,sizeof(struct EntityData));
    if(CurrentProps == NULL){ 
        lua_pushstring(L,strerror(errno));
        lua_error(L);
        return 1;
    }
    return 0;
}
int Script_InitPropRegistry(lua_State* L) {
    Max_Props = lua_tointeger(L, 1);
    RegisteredProps = calloc(Max_Props, sizeof(struct EntityData));
    if (RegisteredProps == NULL) {
        lua_pushstring(L, strerror(errno));
        lua_error(L);
        return 1;
    }
    return 0;
}

luaL_Reg Prop_Lib[] = {
    "AddToEntArray",Script_PropToEntArray,
    "ConvertToEntity",Script_ConvertPropToEntity,
    "CreateArray",Script_InitPropArray,
    "CreateRegistryArray",Script_InitPropRegistry,
    "Register", Script_RegisterProp,
    NULL,NULL 
};

lua_State* Prop_ScriptState;
void InitPropDef(){
    //Max_Props = ;
    //Max_Props = 64;
    Prop_ScriptState = luaL_newstate();
    if(Prop_ScriptState == NULL){
        printf("Failed to init Prop Lua State!\n");
        exit(-1);
    }
    luaL_openlibs(Prop_ScriptState);
#if 0
    lua_register(Prop_ScriptState,"AddPropToEntArray",Script_PropToEntArray);
    lua_register(Prop_ScriptState,"ConvertToEntity",Script_ConvertPropToEntity);

    lua_register(Prop_ScriptState,"CreatePropArray",Script_InitPropArray);
#endif
    luaL_openlib(Prop_ScriptState, "Prop", Prop_Lib, 0);
#if 0
    RegisteredProps = calloc(Max_Props, sizeof(struct EntityData));
    if (RegisteredProps == NULL) {
        SDL_Log(strerror(errno));
        exit(-2);
       
    }
#endif
   // lua_register(Prop_ScriptState, "RegisterProp", Script_RegisterProp);

}

void CreateFromScript(const char* script_fn){
    InitPropDef();
    
    if(luaL_dofile(Prop_ScriptState,script_fn) == 1){
        printf("%s\n",lua_tostring(Prop_ScriptState,-1));
        exit(-2);
    }


}