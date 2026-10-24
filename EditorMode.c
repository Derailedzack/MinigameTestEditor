#include "EditorMode.h"
#include "WallTest.h"
#include "TriggerWall.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include "PropEntity.h"
extern SDL_Event Main_Event;
extern SDL_Window* Main_Window;
extern EDITOR_MODE CurrentMode;
extern EDITOR_MODE_SUBCFG CurrentSubMode;
extern bool ShouldDrop;
extern struct EntityData* CurrentEntities;
extern struct EntityData* CurrentProps;
extern struct EntityData* RegisteredProps;
extern unsigned int Max_Props; 
float StartWallX;
float StartWallY;
int x;
int i_clamp;
int sel_clamp;
int sel_val;
const char* ConvertEditorModeToStr(EDITOR_MODE mode) {
    switch (mode) {
    case PLACE_WALL:
        return "Place Wall(s)";
        break;
    case MOVE_WALL:
        return "Move Wall(s)";
        break;
    case PLACE_SPRITE:
        return "Place Prop(s)";
        break;
    case MOVE_SPRITE:
        return "Move Prop(s)";
        break;
    case PLACE_PLAYER_START:
        return "Place Player Start";
        break;
    case MOVE_PLAYER_START:
        return "Move Player Start";
        break;
    case SCALE_WALL:
        return "Change Wall Size";
        break;
    case PLACE_TRIGGER:
        return "Place Trigger";
        break;
    case SCALE_TRIGGER:
        return "Scale Trigger";
        break;
    case MOVE_TRIGGER:
        return "Move Trigger";
        break;
    case COLOR_WALL:
        return "Change Wall Color";
        break;
    case NONE:
        return "None";
        break;
    case SAVE_FILE:
        return "Save Level Script";
        break;
    case OPEN_FILE:
        return "Open Level Script";
        break;
    default:
        return "Invaild MODE";
        break;
    }
}
void PlaceWall(){
   // if(CurrentMode == PLACE_WALL){
    	//i_clamp = SDL_clamp(x,0,63);
   
				//if(Main_Event.key.repeat == false){
            
				x++;
				AddNewWall(x,StartWallX,StartWallY,32,32);
					
				 SDL_Log("i:%i\n",i_clamp);
				// }
		//}
}
void MoveWall(){
    //if(CurrentMode == MOVE_WALL){
        if(ShouldDrop == false){
			ShouldDrop = true;
		}else{
			ShouldDrop = false;
		}
    //}else if (CurrentMode == PLACE_WALL)
    //{
      //  PlaceWall();
        /* code */
    //}
    
        
}
void PlaceSprite(){
   // if (CurrentSubMode != CHANGE_SELECTED_PROP) {
          x++;
            i_clamp = SDL_clamp(x, 0, Max_Props - 1); //Clamp the damn value else well find out what happens when you index something outside of an array
      // }
         //   if (CurrentSubMode == CHANGE_SELECTED_PROP) {
              
           // }
#if 0
            else {
                SDL_Log("i_clamp:%i\n", i_clamp);

                CurrentProps[i_clamp] = RegisteredProps[i_clamp];
                CurrentProps[i_clamp].Init = PropEntity_Init;
                CurrentProps[i_clamp].Update = PropEntity_Update;
            }
#endif      
            
#if 0
            if (RegisteredProps[i_clamp].entityTex == NULL && &RegisteredProps[i_clamp] != NULL) {
                Entity_CreateTexture(&RegisteredProps[i_clamp], RegisteredProps[i_clamp].tex_path);
            }
#endif
           
           
       
}
void Place_PlayerStart(){
    
        i_clamp = 62;
   //if(&CurrentEntities[i_clamp] == NULL){
        CurrentEntities[i_clamp] = *PlayerEntity_Init();

        CurrentEntities[i_clamp].Init(&CurrentEntities[i_clamp]);
      //  SDL_Log("RenderWidth=%f,RenderHeight=%f,RenderX=%f,RenderY=%f\n", CurrentEntities[i_clamp].entitySprRect.w, CurrentEntities[i_clamp].entitySprRect.h, CurrentEntities[i_clamp].entitySprRect.x, CurrentEntities[i_clamp].entitySprRect.y);
 
    //}
    //i_clamp = 64;
            // i_clamp = 0;
    //if (Main_Event.type == SDL_EVENT_MOUSE_MOTION) {
      //  CurrentEntities[i_clamp].entityRenderRect.x = 0.65f;
        //CurrentEntities[i_clamp].entityRenderRect.y = 0.65f;
    //}
    //SDL_Log("Is Rect NULL:%i\n",&CurrentEntities[i_clamp] == NULL);
    /*if(CurrentMode == PLACE_PLAYER_START){

    }else if(CurrentMode == MOVE_PLAYER_START){

    }*/

}
void HandleModeSelection(EDITOR_MODE mode) {
    
    switch (mode) {
    case PLACE_SPRITE:
        x++;
        sel_clamp = SDL_clamp(x, 0, Max_Props - 1);
        break;
    case PLACE_WALL: //For change the type of wall
        break;
    default:
        break;
    }
}
void PlaceTrigger() {

    x++;
    i_clamp = SDL_clamp(x, 0, MAX_ENTITES - 1);
#if 0
    if (&CurrentEntities[x] == NULL) {

    }
#endif
    AddNewTrigger(i_clamp, StartWallX, StartWallY, 32, 32);
    //AddNewWall(x, StartWallX, StartWallY, 32, 32);

    SDL_Log("i:%i\n", i_clamp);
}
void MoveTrigger() {
    if (ShouldDrop == false) {
        ShouldDrop = true;
    }
    else {
        ShouldDrop = false;
    }
   
}
void HandleMode(EDITOR_MODE mode){
   

    switch (mode)
    {
    case PLACE_WALL:
        PlaceWall();
        break;
    case MOVE_WALL:
        MoveWall();
    break;
    case PLACE_PLAYER_START:
        Place_PlayerStart();
    break;
    case MOVE_PLAYER_START:
        if (i_clamp != 62) { //If the current index isn't 62, set to 62 lest I want the editor to well explode in flames
            i_clamp = 62;
        }
        if(ShouldDrop == false){
			ShouldDrop = true;
		}else{
			ShouldDrop = false;
		}
               // i_clamp = 0;
		if(Main_Event.type == SDL_EVENT_MOUSE_MOTION){
                CurrentEntities[i_clamp].entityRenderRect.x = Main_Event.motion.x;
                CurrentEntities[i_clamp].entityRenderRect.y = Main_Event.motion.y;
        }


    break;

    case PLACE_SPRITE:
    PlaceSprite();
    break;

    case MOVE_SPRITE:
        if(ShouldDrop == false){
			ShouldDrop = true;
		}else{
			ShouldDrop = false;
		}
              i_clamp = SDL_clamp(x,0,Max_Props-1);

    break;

    case SCALE_WALL:
        //This is handled by the UI itself (So NO-OP)
        break;
    case PLACE_TRIGGER:
        PlaceTrigger();
        break;
        
    case MOVE_TRIGGER:
        MoveTrigger();
        break;
    case COLOR_WALL:
        break;
    default:
        break;
    }

    SDL_Log("Current Mode:%i\n",mode);
}