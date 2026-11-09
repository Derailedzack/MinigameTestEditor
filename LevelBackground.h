#pragma once
#include <stdbool.h>
#include "Entity.h"
//struct EntityData* LevelBG_EntityInit();
struct EntityData* LevelBG_InitNoUpdate(const char* tex_path, bool reinit, int tile_width, int tile_height);
struct EntityData* LevelBG_Init(const char* tex_path, bool reinit, int tile_width, int tile_height);
//void LevelBG_InitWithSize(const char* tex_path, int bg_tile_width, int bg_tile_height, bool bg_reinit);
void LevelBG_Update(struct EntityData* data);