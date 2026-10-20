#include "EditorMode.h"
#include "WallTest.h"
#include "Player.h"
#include <SDL3/SDL.h>
extern SDL_Event Main_Event;
extern SDL_Window* Main_Window;
extern EDITOR_MODE CurrentMode;
extern bool ShouldDrop;
extern struct EntityData* CurrentEntities;
extern struct EntityData* CurrentProps;
extern unsigned int Max_Props; 
float StartWallX;
float StartWallY;
int x;
int i_clamp;
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
    case NONE:
        return "None";
        break;
    default:
        return "Invaild MODE";
        break;
    }
}
void PlaceWall(){
   // if(CurrentMode == PLACE_WALL){
    	//i_clamp = SDL_clamp(x,0,63);
   
		if(Main_Event.type == SDL_EVENT_MOUSE_MOTION){

			StartWallX = Main_Event.motion.x;
			StartWallY = Main_Event.motion.y;
		}

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
    /*if(CurrentMode == PLACE_SPRITE){
        
    }else if(CurrentMode == MOVE_SPRITE){
        
    }*/
            x++;
            i_clamp = SDL_clamp(x,0,Max_Props-1);
            //CurrentProps[i_clamp].Init(&CurrentProps[i_clamp]);

   
}
void Place_PlayerStart(){
        i_clamp = MAX_ENTITES-1;
    //if(&CurrentEntities[64] == NULL){
        CurrentEntities[i_clamp] = *PlayerEntity_Init();
        CurrentEntities[i_clamp].Init(&CurrentEntities[i_clamp]);
    //}
    //i_clamp = 64;
    SDL_Log("Current W Pos:%f\n",CurrentEntities[64].entityRenderRect.w);
    /*if(CurrentMode == PLACE_PLAYER_START){

    }else if(CurrentMode == MOVE_PLAYER_START){

    }*/

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
        if(ShouldDrop == false){
			ShouldDrop = true;
		}else{
			ShouldDrop = false;
		}
                i_clamp = 0;
		if(Main_Event.type == SDL_EVENT_MOUSE_MOTION){
                CurrentEntities[0].entityRenderRect.x = Main_Event.motion.x;
                CurrentEntities[0].entityRenderRect.y = Main_Event.motion.y;
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
              i_clamp = SDL_clamp(x,65,127);

    break;
    default:
        break;
    }

    SDL_Log("Current Mode:%i\n",mode);
}