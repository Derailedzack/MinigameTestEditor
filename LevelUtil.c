#include "LevelUtil.h"
#include <stdio.h>
#include "Entity.h"
//#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "WallTest.h"
#include "PropEntity.h"
FILE* LevelFile;
extern struct EntityData* CurrentEntities;
extern struct EntityData* CurrentProps;
extern int Max_Props;
lua_State* LevelScript_State;
extern SDL_Color Empty_Color;
luaL_Reg Level_Lib[] = {
	"AddWallToArray",Script_AddWallToEntites,
	"AddPropToArray",Script_AddPropsToCurrent,
	NULL,NULL
};
int Script_AddPropsToCurrent(lua_State* L) {
	//uaL_checktype(L, 1, LUA_TIN);
	  luaL_checktype(L,2,LUA_TTABLE);
    //for (int i = 0; i > -4; i--)
    //{
	int index_prop = luaL_checkinteger(L, 1);
	lua_getfield(L, 2, "tex_path");
	const char* text_path = lua_tostring(L, 3);
    lua_getfield(L,2,"width");
    float width = lua_tonumber(L,4);
    lua_getfield(L,2,"height");
	float height = lua_tonumber(L,5);
	lua_getfield(L, 2, "x");
	float x = lua_tonumber(L, 6);
	lua_getfield(L, 2, "y");
	float y = lua_tonumber(L, 7);
    lua_getfield(L,2,"render_width");
    float width_scale = lua_tonumber(L,8);
    lua_getfield(L,2,"render_height");
	float height_scale = lua_tonumber(L,9);


#if 0
    lua_getfield(L,1,"name");
    const char* name = lua_tostring(L,7);
#endif
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
#if 0
	struct EntityData entity = *Entity_Create("LuaEntity", text_path, Empty_Color, x, y, width, height, width_scale, height_scale);

	CurrentProps[index_prop] = entity;

	Entity_CreateTexture(&CurrentProps[index_prop], text_path);
	PropEntity_Init(&CurrentProps[index_prop]);
	//CurrentProps[index_prop].Update = PropEntity_Update;
	//CurrentProps[index_prop].Init = PropEntity_Init;
	//CurrentProps[index_prop].Init(&CurrentProps[index_prop]);
#endif

	struct EntityData* entity = Entity_Create("TestEntity", text_path, Empty_Color, x, y, width, height, width_scale, height_scale);
	CurrentProps[index_prop] = *entity;
	CurrentProps[index_prop].Update = PropEntity_Update;
	
	printf("RenderWidth=%f,RenderHeight=%f,RenderX=%f,RenderY=%f\n", CurrentProps[index_prop].entityRenderRect.w, CurrentProps[index_prop].entityRenderRect.h, CurrentProps[index_prop].entityRenderRect.x, CurrentProps[index_prop].entityRenderRect.y);
	printf("TexWidth=%f,TexHeight=%f,TexX=%f,TexY=%f\n", CurrentProps[index_prop].entitySprRect.w, CurrentProps[index_prop].entitySprRect.h, CurrentProps[index_prop].entitySprRect.x, CurrentProps[index_prop].entitySprRect.y);
	//CurrentProps[index_prop].Update = PropEntity_Update;
	// SDL_Log("PropGFX_X=%f\n,")
#if 0
	SDL_Log("PropWidth=%f,PropHeight=%f,PropX=%f,PropY=%f\n", CurrentProps[index_prop].entityRenderRect.w, RegisteredProps[index].entityRenderRect.h, RegisteredProps[index].entityRenderRect.x, RegisteredProps[index].entityRenderRect.y);
	SDL_Log("Prop_GFX_Width=%f,Prop_GFX_Height=%f,Prop_GFX_X=%f,Prop_GFX_Y=%f\n", RegisteredProps[index].entitySprRect.w, RegisteredProps[index].entitySprRect.h, RegisteredProps[index].entitySprRect.x, RegisteredProps[index].entitySprRect.y);
	// SDL_Log("PropTexturePath=%x\n");
#endif

	Entity_CreateTexture(&CurrentProps[index_prop], text_path);
	//PropEntity_Init(&CurrentProps[index_prop]);
	PropEntity_Init(&CurrentProps[index_prop]);

	//__debugbreak();
	
	return 0;
}
int Script_AddWallToEntites(lua_State* L) {
	//luaL_checktype(L, 1, LUA_TTABLE);
	//int wall_index = luaL_checkint(L, 2);
#if 0
	lua_getfield(L, 1, "x");
	float wall_x = lua_tonumber(L, 2);
	lua_getfield(L, 1, "y");
	float wall_y = lua_tonumber(L, 3);
	lua_getfield(L, 1, "width");
	float wall_width = lua_tonumber(L, 4);
	lua_getfield(L, 1, "height");
	float wall_width = lua_tonumber(L, 5);
#endif
	luaL_checktype(L, 5, LUA_TTABLE);
	int wall_r = lua_tointeger(L, 1);
	int wall_g = lua_tointeger(L, 2);
	int wall_b = lua_tointeger(L, 3);
	int wall_index = lua_tointeger(L, 4);
	SDL_Color wall_color;
	wall_color.r = wall_r;
	wall_color.g = wall_g;
	wall_color.b = wall_b;
	wall_color.a = 255;

	lua_getfield(L, 5, "x");
	float wall_x = lua_tonumber(L, 6);
	lua_getfield(L, 5, "y");
	float wall_y = lua_tonumber(L, 7);
	lua_getfield(L, 5, "width");
	float wall_width = lua_tonumber(L, 8);
	lua_getfield(L, 5, "height");
	float wall_height = lua_tonumber(L, 9);

#ifdef USE_UD_FOR_COLOR
	float wall_x = lua_tonumber(L, 1);
	float wall_y = lua_tonumber(L, 2);
	float wall_width = lua_tonumber(L, 3);
	float wall_height = lua_tonumber(L, 4);
	SDL_Color* wall_color = lua_touserdata(L, 5);
	int wall_index = lua_tointeger(L, 6);'
#endif
	AddNewWallWithColor(wall_index, wall_x, wall_y, wall_width, wall_height, wall_color);
	//CurrentEntities[wall_index] = AddNewWall();
	return 0;
}
int Script_ConvertToEntityDat(lua_State* L) {
	return 1;
}
void WriteLevelToScript(const char* level_path) {
	LevelFile = fopen(level_path,"w");
	if (LevelFile == NULL) {
		printf("%s\n",strerror(errno));
		return;
	}
	else {
		//TODO: Figure out how the hell I want to divide props,walls and the level configuration
		fprintf(LevelFile, "local Wall = {}\n");
		for (int i = 0; i < MAX_ENTITES - 1; i++) {
			if (CurrentEntities[i].Update != NULL) {
				fprintf(LevelFile, "Wall[%i]={}\n", i);
				fprintf(LevelFile, "Wall[%i].color={}\n", i);
				fprintf(LevelFile, "Wall[%i].color.r=%i\n",i,CurrentEntities[i].entityDebugColor.r);
				fprintf(LevelFile, "Wall[%i].color.g=%i\n", i, CurrentEntities[i].entityDebugColor.g);
				fprintf(LevelFile, "Wall[%i].color.b=%i\n", i, CurrentEntities[i].entityDebugColor.b);
				fprintf(LevelFile, "Wall[%i].color.a=%i\n", i, CurrentEntities[i].entityDebugColor.a);
				fprintf(LevelFile, "Wall[%i].width=%f\n", i, CurrentEntities[i].entityRenderRect.w);
				fprintf(LevelFile, "Wall[%i].height=%f\n", i, CurrentEntities[i].entityRenderRect.h);
				fprintf(LevelFile, "Wall[%i].x=%f\n", i, CurrentEntities[i].entityRenderRect.x);
				fprintf(LevelFile, "Wall[%i].y=%f\n", i, CurrentEntities[i].entityRenderRect.y);
			}
		}
#if 0
		fprintf(LevelFile, "for k,v in pairs(Wall) then\n");
		fprintf(LevelFile, "AddWallToArray(Wall[k],Wall[k].color.r,Wall[k].color.g,Wall[k].color.b,k)\n");
		fprintf(LevelFile, "end\n");
#endif
		fprintf(LevelFile, "local MapProps = {}\n");
		for (int i = 0; i < Max_Props - 1; i++) {
			if (CurrentProps[i].Update != NULL) {
				fprintf(LevelFile, "MapProps[%i]={}\n", i);
				fprintf(LevelFile, "MapProps[%i].tex_path='%s'\n", i, CurrentProps[i].tex_path);
				fprintf(LevelFile, "MapProps[%i].render_width=%f\n", i, CurrentProps[i].entityRenderRect.w);
				fprintf(LevelFile, "MapProps[%i].render_height=%f\n", i, CurrentProps[i].entityRenderRect.h);
				fprintf(LevelFile, "MapProps[%i].width=%f\n", i, CurrentProps[i].entitySprRect.w); //Why didn't I catch these being the wrong value
				fprintf(LevelFile, "MapProps[%i].height=%f\n", i, CurrentProps[i].entitySprRect.h);
				fprintf(LevelFile, "MapProps[%i].x=%f\n", i, CurrentProps[i].entityRenderRect.x);
				fprintf(LevelFile, "MapProps[%i].y=%f\n", i, CurrentProps[i].entityRenderRect.y);
			}
		}
		fprintf(LevelFile, "require('LoadLevel')\n");
		fprintf(LevelFile, "PopulateWallsFromWallTable()\n");
		fprintf(LevelFile, "PopulatePropsFromPropsTable()\n");
		fclose(LevelFile);
	}
}

void LoadLevelFromScript(const char* script_fn) {
	LevelScript_State = luaL_newstate();
	if (LevelScript_State == NULL) {
		printf("Failed to init Level Lua State!\n");
		//exit(-1);
		return;
	}
	luaL_register(LevelScript_State, "Level", Level_Lib);
	luaL_openlibs(LevelScript_State);
	
	if (luaL_dofile(LevelScript_State, script_fn) == 1) {
		printf("%s\n", lua_tostring(LevelScript_State, -1));
		return;
		//exit(-2);
	}
}