#include "MainRenderer.h"
//#include <Windows.h>
#include "GuiRenderer.h"
#include <stdlib.h>
#include "WallTest.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include "Entity.h"
#include "Player.h"
#include "EditorMode.h"
#include "PropEntity.h"
#include <Windows.h>
#ifdef USE_NATIVE_MENU
#include "native_menu_bar.h"
#endif
//#include <assert.h>
extern SDL_Window* Main_Window;
extern SDL_Renderer* Main_Renderer;
extern SDL_FRect Player_Rect;
extern SDL_Event Main_Event;
bool ShouldDrop = true;
extern unsigned int Max_Props; 
extern struct EntityData* CurrentProps;
extern struct EntityData* RegisteredProps;
struct EntityData* CurrentEntities;
#ifdef USE_NATIVE_MENU
SDL_PropertiesID MainWin_Prop;
HWND Main_WinPtr;
#endif
SDL_FRect PlayerBleeding_Rect = { 0,0,730,45 };
SDL_Color Window_Color = { 0,0,0,255 };
EDITOR_MODE CurrentMode;
EDITOR_MODE_SUBCFG CurrentSubMode;
extern float StartWallX;
extern float StartWallY;

//int i = 0;
char EditorTitle[512];
extern int x;
extern int i_clamp;
extern int sel_val;
extern int sel_clamp;
int ModeClamp;
#ifdef USE_NATIVE_MENU
HMENU MainUi_Menu;
nmb_Handle SizeUi_Menu;
nmb_Handle ModePtr[8];
nmb_Event ModeEvent;
LPMENUITEMINFOW MainUi_TestItem;
#endif
extern int MainWin_Width;
void MainRenderer_Init() {
	CreateFromScript("res/PropInit.lua");
	CurrentEntities = calloc(MAX_ENTITES, sizeof(struct EntityData));
	if (CurrentEntities == NULL) {
		exit(-6);
	}
	//CurrentEntities[0] = *PlayerEntity_Init();
	CurrentEntities[0] = *WallInit(0,0,1024,128);
 //test = Enemy_Init();
		SDL_GetRenderDrawColor(Main_Renderer,&Window_Color.r,&Window_Color.g,&Window_Color.b,&Window_Color.a);
		for (int i = 0; i < MAX_ENTITES - 1; i++) {
			
			if (CurrentEntities[i].Init != NULL) {
			//SDL_Log("Is Player width set!:%i\n",CurrentEntities[64].entityRenderRect.w);
				CurrentEntities[i].Init(&CurrentEntities[i]);
			}

			//CurrentEntities[i].
		}
#if 0
		MainUi_TestItem = malloc(sizeof(MENUITEMINFOA));
		if (MainUi_TestItem == NULL) {
			exit(-4);
		}
#endif
#ifdef USE_NATIVE_MENU
		//MainUi_Menu = CreateMenu();
		MainWin_Prop = SDL_GetWindowProperties(Main_Window);
		Main_WinPtr = SDL_GetPointerProperty(MainWin_Prop, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
		//AppendMenu(MainUi_Menu, MF_STRING, 1, L"Mode");
#endif
#if 0
		MainUi_TestItem->fMask = MIIM_STRING;
		MainUi_TestItem->dwTypeData = L"Test";
		MainUi_TestItem->cch = 10;
		SetMenuItemInfoW(MainUi_Menu,1,TRUE, MainUi_TestItem);
		//InsertMenuItemW(MainUi_Menu, 1, TRUE, MainUi_TestItem);
		if (SetMenu(Main_WinPtr, MainUi_Menu) != TRUE) {
			SDL_Log("LastError:%i\n", GetLastError());
		}
#endif
#ifdef USE_NATIVE_MENU
		nmb_setup(Main_WinPtr,nmb_SetupFlags_createPlatformMenus);
		MainUi_Menu = nmb_appendMenu(NULL, "Mode");
		for (int i = 0; i < 8; i++) {
			
			ModePtr[i] = nmb_appendCheckMenuItem(MainUi_Menu, ConvertEditorModeToStr(i));
		}
#endif
		CurrentMode = NONE;
	//	SizeUi_Menu = nmb_appendMenu(NULL, "Change Size");
		
		//nmb_appendCheckMenuItem(MainUi_Menu, "Test");
		//nmb_appendMenu(MainUi_Menu, "Test");
		
	Nuklear_Init();
	//Player_Init();
}
void MainRenderer_Draw() {
			//Enemy_Draw(test);
	for (int i = 0; i < MAX_ENTITES - 1; i++) {
		if (CurrentEntities[i].Draw != NULL) {
			CurrentEntities[i].Draw(&CurrentEntities[i]);
		}
	}
	for (int i = 0; i < Max_Props - 1; i++) {
		if (CurrentProps[i].Draw != NULL) {
			CurrentProps[i].Draw(&CurrentProps[i]);
		}
	}
	
	//Nuklear_Draw();
	//Player_Draw();
}

void MainRenderer_EventTest(){
	//DrawMenuBar(Main_WinPtr);
#ifdef USE_NATIVE_MENU
	nmb_pollEvent(&ModeEvent);
	if (ModeEvent.event == nmb_EventType_itemTriggered) {

		if(ModeEvent.sender == ModePtr[NONE]){
			CurrentMode = NONE;
		}
		if (ModeEvent.sender == ModePtr[PLACE_WALL]) {
			CurrentMode = PLACE_WALL;
		}
		if (ModeEvent.sender == ModePtr[MOVE_WALL]) {
			CurrentMode = MOVE_WALL;
		}
		if (ModeEvent.sender == ModePtr[PLACE_SPRITE]) {
			CurrentMode = PLACE_SPRITE;
		}
		if (ModeEvent.sender == ModePtr[MOVE_SPRITE]) {
			CurrentMode = MOVE_SPRITE;
		}
		if (ModeEvent.sender == ModePtr[PLACE_PLAYER_START]) {
			CurrentMode = PLACE_PLAYER_START;
		}
		if (ModeEvent.sender == ModePtr[MOVE_PLAYER_START]) {
			CurrentMode = MOVE_PLAYER_START;
		}
		if (ModeEvent.sender == ModePtr[SCALE_WALL]) {
			CurrentMode = SCALE_WALL;
		}
		if (ModeEvent.sender == SizeUi_Menu) {
			//SDL_ShowMessageBox(SDL_MessageBoxButtonData)
		}
	}
#endif
	if(ShouldDrop == false){
		
			
		if(Main_Event.type == SDL_EVENT_MOUSE_MOTION){
			#if 0
	 	if(CurrentMode == PLACE_SPRITE){
				if(&CurrentProps[i_clamp].entityRenderRect != NULL){
					CurrentProps[i_clamp].entityRenderRect.x = Main_Event.motion.x;
					CurrentProps[i_clamp].entityRenderRect.y = Main_Event.motion.y;
			}
					#endif
				if (CurrentMode == MOVE_WALL) {
					CurrentEntities[i_clamp].entityRenderRect.x = Main_Event.motion.x;
					CurrentEntities[i_clamp].entityRenderRect.y = Main_Event.motion.y;
				}
				if (CurrentMode == MOVE_SPRITE) {
					CurrentProps[i_clamp].entityRenderRect.x = Main_Event.motion.x;
					CurrentProps[i_clamp].entityRenderRect.y = Main_Event.motion.y;
				}
			
				if (CurrentMode == MOVE_PLAYER_START) {
					CurrentEntities[i_clamp].entityRenderRect.x = Main_Event.motion.x;
					CurrentEntities[i_clamp].entityRenderRect.y = Main_Event.motion.y;
				}
				if (CurrentMode == MOVE_TRIGGER) {
					CurrentEntities[i_clamp].entityRenderRect.x = Main_Event.motion.x;
					CurrentEntities[i_clamp].entityRenderRect.y = Main_Event.motion.y;
				}
			//}
		
			//CurrentEntities[x].entityRenderRect.x = Main_Event.motion.x;
			//CurrentEntities[x].entityRenderRect.y = Main_Event.motion.y;
		}
		}
		
	#if 0
		if(Main_Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
			if(Main_Event.button.clicks == 1 && Main_Event.button.button == 1){
					//ShouldDrop = true;
					if(&CurrentEntities[i_clamp].entityRenderRect != NULL){
						CurrentEntities[i_clamp].entityRenderRect.x = Main_Event.motion.x;
						CurrentEntities[i_clamp].entityRenderRect.y = Main_Event.motion.y;
					}
	
			}
		}
			#endif

		if (Main_Event.type == SDL_EVENT_MOUSE_MOTION) {

			StartWallX = Main_Event.motion.x;
			StartWallY = Main_Event.motion.y;
		}

		
		if(Main_Event.type == SDL_EVENT_KEY_DOWN){
		
			switch (Main_Event.key.key)
			{
#if 0
			case SDLK_1:
				CurrentMode = PLACE_SPRITE;
				break;
			case SDLK_2:
				CurrentMode = MOVE_SPRITE;
				break;

			case SDLK_F1:
				//SDL_clamp(ModeClamp, 0, MOVE_PLAYER_START);
				CurrentMode++;
				//CurrentMode = ModeClamp;
				break;
				case SDLK_F2:
				//SDL_clamp(ModeClamp, 0, MOVE_PLAYER_START);
				CurrentMode--;
				//CurrentMode = ModeClamp;
				break;
#endif
			case SDLK_E:
				if (&CurrentEntities[i_clamp] == NULL){ //Damn me and my constant dropping of word(s) when typing anything
					exit(-4235); //I don't remember why this is -4235 (It was likely something I typed late at night.)
				}
				HandleMode(CurrentMode);
				//MoveWall();
				break;
			#if 0
			case SDLK_N:
	
				//AddWall();
			if(CurrentMode == PLACE_WALL){
			if(Main_Event.type == SDL_EVENT_MOUSE_MOTION){

			StartWallX = Main_Event.motion.x;
			StartWallY = Main_Event.motion.y;
			}
		
				//if(Main_Event.key.repeat == false){
					x++;
				AddNewWall(x,StartWallX,StartWallY,32,32);
					
				 SDL_Log("i:%i\n",i_clamp);
				// }
	

				MoveWall();
				break;
			#endif
			case SDLK_KP_PLUS:
				//if (CurrentSubMode != CHANGE_SELECTED_PROP) {
					x++;
					i_clamp = SDL_clamp(x, 0, MAX_ENTITES - 1);
					SDL_Log("Current (ADD) Index:%i\n", i_clamp);
					if (ShouldDrop == false) {
						ShouldDrop = true;
					}
					else {
						ShouldDrop = false;
					}
				//}
#if 0
				else {
					sel_val++;
					SDL_Log("Current (ADD) Index:%i\n", sel_val);
				}
#endif
			
				break;
				case SDLK_KP_MINUS:
					//if (CurrentSubMode != CHANGE_SELECTED_PROP) {
						x--;
						i_clamp = SDL_clamp(x, 0, MAX_ENTITES - 1);
						SDL_Log("Current (DEC) Index:%i\n", i_clamp);

						if (ShouldDrop == false) {
							ShouldDrop = true;
						}
						else {
							ShouldDrop = false;
						}
					//}
#if 0
					else {
						sel_val--;
						SDL_Log("Current (DEC) Index:%i\n", sel_val);
					}
#endif
				break;
#if 0
				case SDLK_F1:
#if 0
					x++;
					i_clamp = SDL_clamp(x, 0, MAX_ENTITES - 1);
#endif
					CurrentSubMode = CHANGE_SELECTED_PROP;
					break;
				case SDLK_F2:

					CurrentSubMode = CHANGE_INDEX;
					break;
#endif
				case SDLK_F1:
					if (CurrentSubMode == CHANGE_SELECTED_PROP) {
						CurrentSubMode = CHANGE_INDEX;
					}
					else {
						CurrentSubMode = CHANGE_SELECTED_PROP;
					}
				
					break;
				case SDLK_RIGHT:
					if (CurrentMode == PLACE_SPRITE) {
						sel_val++;
						sel_clamp = SDL_clamp(sel_val, 0, Max_Props - 1);

						//sel_val++;
						//sel_clamp = SDL_clamp(x, 0, Max_Props - 1);
						SDL_Log("sel_clamp:%i\n", sel_clamp);
					//	if (&RegisteredProps[i_clamp] != NULL) {
							CurrentProps[i_clamp] = RegisteredProps[sel_val];
							CurrentProps[i_clamp].Init = PropEntity_Init;
							CurrentProps[i_clamp].Update = PropEntity_Update;
						//}
					}
					//CurrentProps[i_clamp] = RegisteredProp
					break;
					case SDLK_LEFT:
					if (CurrentMode == PLACE_SPRITE) {
						sel_val--;
						sel_clamp = SDL_clamp(sel_val, 0, Max_Props - 1);
						SDL_Log("sel_clamp:%i\n", sel_clamp);
						if (&RegisteredProps[i_clamp] != NULL) {
							CurrentProps[i_clamp] = RegisteredProps[sel_val];
							CurrentProps[i_clamp].Init = PropEntity_Init;
							CurrentProps[i_clamp].Update = PropEntity_Update;
						}
					}
				
					break;
					case SDLK_R:
						break;
			}
		
			
			/*if(Main_Event.key.key == SDLK_N){
					x++;
				 SDL_Log("i:%i\n",x);
				}*/
		
			
		}

		
}
void MainRenderer_Update() {

			SDL_snprintf(EditorTitle, 512, "%s - Index %i (%s)\n", ConvertEditorModeToStr(CurrentMode), i_clamp,__TIMESTAMP__);
			//Enemy_Update(test);
			SDL_SetWindowTitle(Main_Window, EditorTitle);
			SDL_SetRenderDrawColor(Main_Renderer, 233, 45, 0, 255);
			SDL_RenderDebugTextFormat(Main_Renderer, Player_Rect.x - 16, Player_Rect.y - 16, "X:%f Y:%f\n", Player_Rect.x, Player_Rect.y);
			SDL_SetRenderDrawColor(Main_Renderer, Window_Color.r, Window_Color.g, Window_Color.b, Window_Color.a);
	
			//	Phys_Update();
			for (int i = 0; i < MAX_ENTITES - 1; i++) {
				if (CurrentEntities[i].Update != NULL) {
					CurrentEntities[i].Update(&CurrentEntities[i]);
				}

				//CurrentEntities[i].
			}
			
	for (int i = 0; i < Max_Props - 1; i++) {
		if (CurrentProps[i].Update != NULL) {
			CurrentProps[i].Update(&CurrentProps[i]);
		}

	}
	Nuklear_Update();
	//Player_Update();

}