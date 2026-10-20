#pragma once
#include "Entity.h"
void Player_InitMulti();
void Player_DrawMulti();
void Player_UpdateMulti();

void Player_Init(struct EntityData* data);
struct EntityData* PlayerEntity_Init();
void Player_Draw(struct EntityData* data);
void Player_Update(struct EntityData* data);
void Player_Reinit(struct EntityData* data);