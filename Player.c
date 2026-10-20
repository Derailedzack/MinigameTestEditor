#include "Player.h"
#include "Entity.h"
//#include "AppConfig.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAX_PLAYERS 512
extern SDL_Window* Main_Window;
extern SDL_Renderer* Main_Renderer;
extern SDL_FRect PlayerBleeding_Rect;
//extern AppConfig* Main_Cfg;
SDL_Surface* Player_SwTex;
SDL_Texture* Player_Tex;
int Player_Count;
struct EntityData* player_data;
float MouseX;
float MouseY;
float PlayerXSpeedModifier = 0.05f;
float PlayerYSpeedModifier = 0.05f;
//float PlayerFallSpeedModifier = 0.005f;
SDL_FRect Player_Rect = {0,0,128,128};
//SDL_FRect* PlayerTest_Rect;
SDL_FRect PlayerIdle_Rect = { 0,0,16,16 };
SDL_Color Empty_Color = {0,0,0,255 };
extern SDL_Color Window_Color;

//b2Vec2 Player_FallForce = {0.0f,4.0f};

void Player_Init(struct EntityData* data) {
	Player_SwTex = SDL_LoadPNG("res/TestSprite02a_Ghost_pal01_hatless.png");
	if (Player_SwTex == NULL) {
			SDL_Log("%s\n", SDL_GetError());
			//__debugbreak();
			exit(1);
	}
	
	data->entitySprRect.w = 16;
	data->entitySprRect.h = 16;
	data->entitySprRect.x = 0;
	data->entitySprRect.y = 0;
	data->entityRenderRect.x = 0;
	data->entityRenderRect.y = 100;
	data->entityRenderRect.w = 128;
	data->entityRenderRect.h = 128;


	Player_Tex = SDL_CreateTextureFromSurface(Main_Renderer, Player_SwTex);
	if (Player_Tex == NULL) {
		SDL_Log("Failed to create Player texture from surface! %s\n", SDL_GetError());
		//__debugbreak();
		exit(2);
	}
	
	SDL_SetTextureScaleMode(Player_Tex, SDL_SCALEMODE_PIXELART);
}
struct EntityData* PlayerEntity_Init() {
	struct EntityData* player_data_int = SDL_malloc(sizeof(struct EntityData)); //Entity_Create("Player", NULL, Empty_Color, 0.0f, 0.0f, 64.0f, 64.0f, 256.0f, 256.0f);
	if (player_data_int == NULL) {
		SDL_Log("%s\n", SDL_GetError());
		exit(-3);
	}
	player_data_int->Init = Player_Init;
	player_data_int->Draw = Player_Draw;
	player_data_int->Update = Player_Update;
	player_data_int->Init(player_data_int);
	//SDL_assert(player_data_int != NULL);
	//player_data_int->entityRenderRect.y = -2.0f;
	SDL_Log("%f\n",player_data_int->entityRenderRect.x);
	return player_data_int;
}

void Player_Draw(struct EntityData* data) {
	//Player_DrawMulti();
	//b2Body_ApplyForceToCenter(Player_BodyID, Player_FallForce, true);
	//SDL_Log("Test!\n");
	SDL_RenderTexture(Main_Renderer, Player_Tex, &data->entitySprRect, &data->entityRenderRect);
	//SDL_Log("%s\n",SDL_GetError());
}
void Player_Update(struct EntityData* data) {
	Player_Draw(data);
	#if 0
	bool can_jump = false;
	bool* is_keydown = SDL_GetKeyboardState(NULL);
	

	if (is_keydown[SDL_SCANCODE_S]) {
		//PlayerIdle_Rect.x = 32;
		data->entityRenderRect.y += PlayerYSpeedModifier;
	}
	if (is_keydown[SDL_SCANCODE_W]) {
		//PlayerIdle_Rect.x = 32;
		data->entityRenderRect.y -= PlayerYSpeedModifier;
	}
	if (is_keydown[SDL_SCANCODE_D]) {
		//PlayerIdle_Rect.x = 32;
		data->entityRenderRect.x += PlayerXSpeedModifier;
	}
	if (is_keydown[SDL_SCANCODE_A]) {
		//PlayerIdle_Rect.x = 32;
		data->entityRenderRect.x -= PlayerXSpeedModifier;
	}
		#endif

}
void Player_Reinit(struct EntityData* data) {
	SDL_DestroySurface(Player_SwTex);
	SDL_DestroyTexture(Player_Tex);
	Player_Init(data);
}