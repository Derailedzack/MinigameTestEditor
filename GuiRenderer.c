#include "GuiRenderer.h"
#include <SDL3/SDL.h>
#include <limits.h>
#include "NuklearConfig.h"
#include "EditorMode.h"
#include "EditorMenu.h"
#include "Player.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"
#define NK_SDL3_RENDERER_IMPLEMENTATION
#include "nuklear_sdl3_renderer.h"
struct nk_context* MainUi_Ctx;
extern SDL_Window* Main_Window;
extern SDL_Renderer* Main_Renderer;
extern EDITOR_MODE CurrentMode;
extern SDL_Event Main_Event;
extern int MainWin_Width;
extern int MainWin_Height;
bool IsUiVisible = true;
bool Test;
void Nuklear_DebugFontInit() {
	//Based on nuklear/demo/sdl3_renderer/main.c (Don't remove)
	struct nk_font_atlas* atlas;
	struct nk_font_config config = nk_font_config(0);
	struct nk_font* font;
	atlas = nk_sdl_font_stash_begin(MainUi_Ctx);
	font = nk_font_atlas_add_default(atlas, 13, &config);
	nk_sdl_font_stash_end(MainUi_Ctx);
	nk_style_set_font(MainUi_Ctx, &font->handle);
}

void Nuklear_Init() {
	MainUi_Ctx = nk_sdl_init(Main_Window, Main_Renderer, nk_sdl_allocator());
	Nuklear_DebugFontInit();
	nk_input_begin(MainUi_Ctx);
}
void Nuklear_Draw() {
	nk_input_end(MainUi_Ctx);
	if (IsUiVisible) {
#if 0
		if(nk_begin(MainUi_Ctx,"Phys Config",nk_rect(32,0,800,600),NK_WINDOW_CLOSABLE | NK_WINDOW_MOVABLE)){
		
			if(nk_group_begin(MainUi_Ctx,"Walls",0)){
			nk_layout_row_dynamic(MainUi_Ctx,0,5);
			nk_selectable_text(MainUi_Ctx,"Test",5,NK_WIDGET_CENTERED,&Test);
			}
		
			nk_group_end(MainUi_Ctx);
			
			//nk_selectable_label(MainUi_Ctx,"Test",NK_WIDGET_CENTERED,&Test);
			//
			//nk_list_view_begin()
			//nk_tree_push_id(MainUi_Ctx,NK_TREE_NODE,"Test",NK_MAXIMIZED,0);
			//nk_tree_pop(MainUi_Ctx);
			//nk_tree_push_id(MainUi_Ctx,NK_TREE_NODE,"Test23",NK_MAXIMIZED,1);
			//nk_tree_pop(MainUi_Ctx);
			//nk_tree_base(MainUi_Ctx,NK_TREE_NODE,NULL,"Test",NK_MAXIMIZED,"",5,0);
		}
#endif

		if (CurrentMode == SCALE_WALL || CurrentMode == SCALE_TRIGGER) {
			Menu_OpenResizeUI();
		}
		if (CurrentMode == COLOR_WALL) {
			Menu_OpenChangeColorUI();
		}
		
#if 0
		if (CurrentMode == PLACE_SPRITE) {
			Menu_OpenSpawnPropUI();
		}
#endif
		Menu_Init();
	
	}


}
void Nuklear_Update() {
	
	Nuklear_Draw();
	
	//nk_input_end(MainUi_Ctx);
	
	nk_sdl_render(MainUi_Ctx, NK_ANTI_ALIASING_OFF);
	nk_sdl_update_TextInput(MainUi_Ctx);
	nk_input_begin(MainUi_Ctx);
	nk_sdl_handle_event(MainUi_Ctx, &Main_Event);
}
