#include "Entity.h"
#include <stdlib.h>
#include <errno.h>
#include <SDL3/SDL.h>
extern SDL_Renderer* Main_Renderer;
extern SDL_Color Window_Color;
#if 0
EntityData* Entity_Create(const char* name, const char* tex_path, SDL_Color debug_color, SDL_FRect spr_rect, SDL_FRect render_rect) {
	EntityData* entity = SDL_malloc(sizeof(EntityData));
	entity->name = name;
	if (tex_path == NULL || tex_path == "") {
		entity->tex_path = "";
		entity->entityDebugColor = debug_color;	
	}
	else {
		entity->tex_path = tex_path;
		entity->entitySprRect = spr_rect;
		entity->entityRenderRect = render_rect;

	}
}

void Entity_Init(EntityData* entity,EntityInitFlags init_flags) {
	switch (init_flags) {
	case INIT_USE_NAME_AS_TEX_NAME:
		Entity_CreateTexture(entity, entity->name);
		break;
	case INIT_USE_TEX_NAME:
		Entity_CreateTexture(entity, entity->tex_path);
		break;
	case INIT_NO_TEXTURE:
		break;
	}
	/*
	if (init_flags == INIT_USE_NAME_AS_TEX_NAME) {
		Entity_CreateTexture(entity, entity->name);
	}
	if (init_flags == INIT_USE_TEX_NAME) {
		Entity_CreateTexture(entity, entity->tex_path);
	}
	*/
}
#endif
struct EntityData* Entity_Create(const char* name, const char* tex_path, SDL_Color debug_color, float start_x, float start_y, float width, float height, float render_width, float render_height) {
	struct EntityData* entity = SDL_malloc(sizeof(struct EntityData));
	if (entity == NULL) {
		SDL_Log("%s\n", strerror(errno));
		exit(-6);
	}
	entity->name = name;
	if (tex_path == NULL || tex_path == "") {
		entity->tex_path = "";
		entity->entityDebugColor = debug_color;
	}
	else {
		entity->tex_path = tex_path;
		entity->entitySprRect.x = 0;
		entity->entitySprRect.y = 0;
		entity->entitySprRect.w = width;
		entity->entitySprRect.h = height;

		entity->entityRenderRect.x = start_x;
		entity->entityRenderRect.y = start_y;
		entity->entityRenderRect.w = render_width;
		entity->entityRenderRect.h = render_height;

	}
	return entity;
}
void Entity_CreateTexture(struct EntityData* entity,const char* tex_name) {
	SDL_Surface* entity_sw_tex = SDL_LoadPNG(tex_name);
	if (entity_sw_tex == NULL) {
		SDL_Log("Entity %s will be invisible as the specified texture is invaild! (%s)\n", entity->name,SDL_GetError());
		return;
	}
	entity->entityTex = SDL_CreateTextureFromSurface(Main_Renderer, entity_sw_tex);
	if (entity->entityTex == NULL) {
		SDL_Log(SDL_GetError());
		return;
	}
	//entity->entityTex 
}
#if 0
void Entity_Draw(EntityData* entity) {
	if (entity->entityTex == NULL) {
		SDL_SetRenderDrawColor(Main_Renderer, entity->entityDebugColor.r, entity->entityDebugColor.g, entity->entityDebugColor.b, entity->entityDebugColor.a);
		SDL_RenderRect(Main_Renderer, &entity->entityRenderRect);
		SDL_SetRenderDrawColor(Main_Renderer, Window_Color.r, Window_Color.g, Window_Color.b, Window_Color.a);
	}
	else {
		SDL_RenderTexture(Main_Renderer,entity->entityTex,&entity->entitySprRect,&entity->entityRenderRect);
	}
	
}
#endif
void Entity_NoPtrUpdate(struct EntityData entity) {
	Entity_NoPtrDraw(entity);
}
void Entity_NoPtrDraw(struct EntityData entity) {
	if (entity.entityTex == NULL) {
		SDL_SetRenderDrawColor(Main_Renderer, entity.entityDebugColor.r, entity.entityDebugColor.g, entity.entityDebugColor.b, entity.entityDebugColor.a);
		SDL_RenderRect(Main_Renderer, &entity.entityRenderRect);
		SDL_SetRenderDrawColor(Main_Renderer, Window_Color.r, Window_Color.g, Window_Color.b, Window_Color.a);
	}
	else {
		SDL_RenderTexture(Main_Renderer, entity.entityTex, &entity.entitySprRect, &entity.entityRenderRect);
	}

}
#if 0
void Entity_Update(EntityData* entity) {
	Entity_Draw(entity);
}
#endif
