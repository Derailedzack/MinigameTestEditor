#include <SDL3/SDL.h>
#include "MainRenderer.h"
//#include "AppConfig.h"
#include <stdio.h>
SDL_Window* Main_Window;
SDL_Renderer* Main_Renderer;
SDL_Event Main_Event;
SDL_DisplayMode* Main_VidMode;
int MainWin_Width;
int MainWin_Height;
extern bool IsUiVisible;
bool ShouldRun = true;
void SDL3_CreateWindow(int width,int height) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (width == NULL || height == NULL) {
		Main_VidMode = SDL_GetDesktopDisplayMode(1);
		width = Main_VidMode->w;
		height = Main_VidMode->h;
	}
	
	if (SDL_CreateWindowAndRenderer("Spirit Test", width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN, &Main_Window, &Main_Renderer) == false) {
		printf("Failed to create window or renderer! (Window and Renderer creation) %s\n", SDL_GetError());
		ShouldRun = false;
		return;
	}
	MainWin_Width = width;
	MainWin_Height = height;
	
	MainRenderer_Init();
	//MainRenderer_Draw();
}
void SDL3_StartMainLoop() {
	while (ShouldRun) {
		SDL_RenderClear(Main_Renderer);
		MainRenderer_Update();
		SDL_RenderPresent(Main_Renderer);
		SDL_PollEvent(&Main_Event);
		MainRenderer_EventTest();
#if 0
		if (Main_Event.type == SDL_EVENT_KEY_DOWN) {
			if (Main_Event.key.key == SDLK_Q) {
				ShouldRun = false;
			}
			
				//AddNewWall(i,0,0,32,32);
				
			//}
			#if 0
			if (Main_Event.key.key == SDLK_C) {
				if (IsUiVisible) {
					IsUiVisible = false;
				}
				else {
					IsUiVisible = true;
				}
			}
				#endif

		}
#endif

		if (Main_Event.type == SDL_EVENT_QUIT) {
			ShouldRun = false;
		}

		if (Main_Event.type == SDL_EVENT_WINDOW_RESIZED) {
			MainWin_Width = Main_Event.display.data1;
			MainWin_Height = Main_Event.display.data2;
		}
	}
}