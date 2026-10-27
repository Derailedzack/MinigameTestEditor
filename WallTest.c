#include "WallTest.h"
#include "Entity.h"
#include "nuklear.h"
extern SDL_Color Window_Color;
extern SDL_Renderer* Main_Renderer;
extern struct EntityData* CurrentEntities;
extern float PlayerXSpeedModifier;
extern float PlayerYSpeedModifier;
extern int i_clamp;
extern struct nk_colorf WallColor;
struct nk_color NewWallColor;
void Wall_Init(struct EntityData* data){
    #if 0
    data->entityRenderRect.x = 0;
    data->entityRenderRect.y = 0; 
    data->entityRenderRect.w = 1024;
    data->entityRenderRect.h = 128;
    #endif
    data->entityDebugColor.r = 128;
    data->entityDebugColor.g = data->entityDebugColor.r;
    data->entityDebugColor.b = data->entityDebugColor.r;
    data->entityDebugColor.a = 255;
    
}
void AddNewWall(int index, float start_x, float start_y, float start_w, float start_h) {

    //if(index > MAX_ENTITES && index < MAX_ENTITES == false){
    i_clamp = SDL_clamp(index, 0, MAX_ENTITES - 1);
    CurrentEntities[i_clamp] = *WallInit(start_x, start_y, start_w, start_h);
    //   / }

       //
}

void AddNewWallWithColor(int index, float start_x, float start_y, float start_w, float start_h,SDL_Color start_color) {

             //if(index > MAX_ENTITES && index < MAX_ENTITES == false){
             i_clamp = SDL_clamp(index, 0, MAX_ENTITES - 1);
             CurrentEntities[i_clamp] = *WallInit(start_x, start_y, start_w, start_h);
             CurrentEntities[i_clamp].entityDebugColor = start_color;
             //   / }

                //

}

void Wall_Draw(struct EntityData* data){
    SDL_SetRenderDrawColor(Main_Renderer, data->entityDebugColor.r, data->entityDebugColor.g, data->entityDebugColor.b,255);
    SDL_RenderFillRect(Main_Renderer,&data->entityRenderRect);
    SDL_SetRenderDrawColor(Main_Renderer,Window_Color.r,Window_Color.g,Window_Color.b,Window_Color.a);
}
void Wall_Update(struct EntityData* data){

    NewWallColor = nk_rgb_f(WallColor.r, WallColor.g, WallColor.b);
    if (WallColor.r != 0 && WallColor.g != 0 && WallColor.b != 0) {
            CurrentEntities[i_clamp].entityDebugColor.r = NewWallColor.r;
            CurrentEntities[i_clamp].entityDebugColor.g = NewWallColor.g;
            CurrentEntities[i_clamp].entityDebugColor.b = NewWallColor.b;
    }

 
    Wall_Draw(data);
    #if 0
    if(SDL_HasRectIntersectionFloat(&data->entityRenderRect,&CurrentEntities[0].entityRenderRect) == true){
        //PlayerYSpeedModifier = 0.05f;
        CurrentEntities[0].entityRenderRect.y += PlayerYSpeedModifier;
    }
    #endif
}

struct EntityData* WallInit(float start_x,float start_y,float start_w,float start_h){
  struct EntityData* data = SDL_malloc(sizeof(struct EntityData));
    if(data == NULL){
        return NULL;
    }
    data->entityRenderRect.x = start_x;
    data->entityRenderRect.y = start_y; 
    data->entityRenderRect.w = start_w;
    data->entityRenderRect.h = start_h;
    
    data->Draw = Wall_Draw;
    data->Update = Wall_Update;
    data->Init = Wall_Init;
    Wall_Init(data);
    return data;    
}
