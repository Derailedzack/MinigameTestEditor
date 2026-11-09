#include "LevelBackground.h"
#include <SDL3/SDL.h>
#if 0
SDL_FRect BG_SrcRect;
SDL_FRect BG_DstRect;
#endif
SDL_Surface* BG_SwTex;
SDL_Texture* BG_Tex;
extern SDL_Renderer* Main_Renderer;
extern int MainWin_Width;
extern int MainWin_Height;
extern SDL_Color Empty_Color;
//TODO: Convert to EntityData
struct EntityData* LevelBG_EntityInit(const char* tex_path) {
	struct EntityData* level_bg_data = SDL_malloc(sizeof(struct EntityData));
	if (level_bg_data == NULL) {
		SDL_Log("%s\n", SDL_GetError());
		exit(-3);
	}
	//}/*
	//level_bg_data->Init = LevelBG_Init;*/
	level_bg_data->Update = LevelBG_Update;
	level_bg_data->Init(level_bg_data);
	return level_bg_data;

}
struct EntityData* LevelBG_InitNoUpdate(const char* tex_path, bool reinit, int tile_width, int tile_height) {
	struct EntityData* entity = Entity_Create("BG0", tex_path, Empty_Color, 0.0f, 0.0f, tile_width, tile_height, 1024, 768);
	//Entity_CreateTexture(entity, entity->tex_path);

	SDL_SetTextureScaleMode(entity->entityTex, SDL_SCALEMODE_PIXELART);
	entity->Init = NULL;
	//entity->Update = LevelBG_Update;

	return entity;

}
struct EntityData* LevelBG_Init(const char* tex_path,bool reinit,int tile_width,int tile_height) {
#if 0
	data->entitySprRect.w = BG_SwTex->w;
	data->entitySprRect.h = BG_SwTex->h;
	data->entitySprRect.x = 0;
	data->entitySprRect.y = 0;
	data->entityRenderRect.w = 1024;
	data->entityRenderRect.h = 768;
	data->entityRenderRect.x = 0;
	data->entityRenderRect.y = 0;
	Entity_CreateTexture(data, "");
#endif
	struct EntityData* entity = Entity_Create("BG0", tex_path, Empty_Color, 0.0f, 0.0f, tile_width , tile_height, 1024, 768);
	Entity_CreateTexture(entity, entity->tex_path);

	SDL_SetTextureScaleMode(entity->entityTex, SDL_SCALEMODE_PIXELART);
	entity->Init = NULL;
	entity->Update = LevelBG_Update;

	return entity;
}
void LevelBG_Update(struct EntityData* data) {
	SDL_RenderTextureTiled(Main_Renderer, data->entityTex, &data->entitySprRect, 1, &data->entityRenderRect);
}
#if 0
void LevelBG_Init(const char* tex_path, bool bg_reinit) {

	if (bg_reinit == true) {
		SDL_DestroySurface(BG_SwTex);
		SDL_DestroyTexture(BG_Tex);
	}
	BG_SwTex = SDL_LoadPNG(tex_path);
	if (BG_SwTex == NULL) {
		SDL_Log(SDL_GetError());
		exit(-190);
	}
	
	BG_SrcRect.w = BG_SwTex->w;
	BG_SrcRect.h = BG_SwTex->h;
	BG_SrcRect.x = 0;
	BG_SrcRect.y = 0;
	BG_DstRect.w = 1024;
	BG_DstRect.h = 768;
	BG_DstRect.x = 0;
	BG_DstRect.y = 0;

	BG_Tex = SDL_CreateTextureFromSurface(Main_Renderer, BG_SwTex);
}
void LevelBG_InitWithSize(const char* tex_path, int bg_tile_width, int bg_tile_height, bool bg_reinit) {

	if (bg_reinit == true) {
		SDL_DestroySurface(BG_SwTex);
		SDL_DestroyTexture(BG_Tex);
	}
	BG_SwTex = SDL_LoadPNG(tex_path);
	if (BG_SwTex == NULL) {
		SDL_Log(SDL_GetError());
		exit(-190);
	}

	BG_SrcRect.w = bg_tile_width;
	BG_SrcRect.h = bg_tile_height;
	BG_SrcRect.x = 0;
	BG_SrcRect.y = 0;
	BG_DstRect.w = 1024;
	BG_DstRect.h = 768;
	BG_DstRect.x = 0;
	BG_DstRect.y = 0;

	BG_Tex = SDL_CreateTextureFromSurface(Main_Renderer, BG_SwTex);
}
void LevelBG_Update() {
	BG_DstRect.w = MainWin_Width;
	BG_DstRect.h = MainWin_Height;
	BG_DstRect.x = 0;
	BG_DstRect.y = 0;
	SDL_RenderTextureTiled(Main_Renderer, BG_Tex,&BG_SrcRect,1 ,&BG_DstRect);
}
#endif