#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#define MAX_ENTITES 128
#include <SDL3/SDL.h>
#if 0
typedef void (EntityInit_Func)(EntityData data);
typedef void (EntityDraw_Func)(EntityData data);
typedef void (EntityUpdate_Func)(EntityData data);
#endif

struct EntityData {
	//SDL_Surface* Entity_SwTex;
	const char* name;
	const char* tex_path;
	SDL_Texture* entityTex;
	SDL_Color entityDebugColor;
	SDL_FRect entitySprRect;
	SDL_FRect entityRenderRect;
	
	void (*Draw)(struct EntityData* data);
	void (*Update)(struct EntityData* data);
	void (*Init)( struct EntityData* data);
	
	
};

typedef enum EntityInitFlags {
	INIT_USE_NAME_AS_TEX_NAME,
	INIT_USE_TEX_NAME,
	INIT_NO_TEXTURE
}EntityInitFlags;

void Entity_CreateTexture(struct EntityData* entity, const char* tex_name);
struct EntityData* Entity_Create(const char* name, const char* tex_path, SDL_Color debug_color, float start_x, float start_y, float width, float height, float render_width, float render_height);
//EntityData* Entity_Create(const char* name,const char* tex_path, SDL_Color debug_color, SDL_FRect spr_rect, SDL_FRect render_rect);
//void Entity_Init(EntityData* entity,EntityInitFlags init_flags);

void Entity_NoPtrDraw(struct EntityData entity);
void Entity_NoPtrUpdate(struct EntityData entity);
#if 0
void Entity_Draw(EntityData* entity);
void Entity_Update(EntityData* entity);
#endif
#endif