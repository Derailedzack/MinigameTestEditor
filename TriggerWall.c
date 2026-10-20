#include "TriggerWall.h"
extern SDL_Color Window_Color;
extern SDL_Renderer* Main_Renderer;
extern struct EntityData* CurrentEntities;
extern float PlayerXSpeedModifier;
extern float PlayerYSpeedModifier;
extern int i_clamp;
void AddNewTrigger(int index, float start_x, float start_y, float start_w, float start_h) {
    i_clamp = SDL_clamp(index, 0, MAX_ENTITES-1);
    CurrentEntities[i_clamp] = *TriggerInit(start_x, start_y, start_w, start_h);
}
void Trigger_Init(struct EntityData* data) {
#if 0
    data->entityRenderRect.x = 0;
    data->entityRenderRect.y = 0;
    data->entityRenderRect.w = 1024;
    data->entityRenderRect.h = 128;
#endif
    data->entityDebugColor.r = 120;
    data->entityDebugColor.g = 0;
    data->entityDebugColor.b = 0;
    data->entityDebugColor.a = 255;

}
void Trigger_Draw(struct EntityData* data) {

    SDL_SetRenderDrawColor(Main_Renderer, data->entityDebugColor.r, data->entityDebugColor.g, data->entityDebugColor.b, 255);
    SDL_RenderFillRect(Main_Renderer, &data->entityRenderRect);
    SDL_SetRenderDrawColor(Main_Renderer, Window_Color.r, Window_Color.g, Window_Color.b, Window_Color.a);
}
void Trigger_Update(struct EntityData* data) {

    Trigger_Draw(data);

}
struct EntityData* TriggerInit(float start_x, float start_y, float start_w, float start_h) {
    struct EntityData* data = SDL_malloc(sizeof(struct EntityData));
    if (data == NULL) {
        return NULL;
    }
    data->entityRenderRect.x = start_x;
    data->entityRenderRect.y = start_y;
    data->entityRenderRect.w = start_w;
    data->entityRenderRect.h = start_h;

    data->Draw = Trigger_Draw;
    data->Update = Trigger_Update;
   // data->Init = Trigger_Init; //This doesn't nothing as it's no-op
    Trigger_Init(data);
}
