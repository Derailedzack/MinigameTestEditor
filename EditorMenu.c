#include "EditorMenu.h"
#include "EditorMode.h"

#include "nuklear.h"
#include "Entity.h"
#include <float.h>
#include <SDL3/SDL.h>
#include "LevelUtil.h"
#include "LevelBackground.h"
extern struct nk_context* MainUi_Ctx;
extern int MainWin_Width;
extern EDITOR_MODE CurrentMode;
extern struct EntityData* CurrentEntities;
extern struct EntityData* RegisteredProps;
struct EntityData NullEntity;
extern int i_clamp;
extern unsigned int Max_Props;
int SelectedPropIndex;
const char* PropTextList;
const char* OpenFileName;
struct nk_colorf WallColor;
const SDL_DialogFileFilter Level_Filters[] = {
	{"Lua","lua"}
};
char TexPathBuf[512];
char BG_TexPathBuf[512];
char start_w_conv[5];
char start_h_conv[5];
char end_w_conv[5];
char end_h_conv[5];
int start_w = 32;
int start_h = 32;
int end_w = 1024;
int end_h = 768;
extern float StartWallX;
extern float StartWallY;
//nk_bool* IsPropSelected; 
void Menu_FileDialogFunc(void* ud, const char** filelist, int filter) {
	if (filelist == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Level Save", SDL_GetError(), NULL);
		return;
	}
	if (CurrentMode == SAVE_FILE) {
		PropTextList = filelist[0]; //Ignore every other file except the first one as we don't need to support multiple files
	}
	else {
		OpenFileName = filelist[0];
		LoadLevelFromScript(OpenFileName);
	}
	//WriteLevelToScript(PropTextList);
}
void Menu_Init() {
	if (nk_begin(MainUi_Ctx, "Resize", nk_rect(0, 0, MainWin_Width, 34), 0)) {

		nk_menubar_begin(MainUi_Ctx);
		nk_layout_row_begin(MainUi_Ctx, NK_STATIC, 25, 4);
		//nk_layout_row_dynamic(MainUi_Ctx, 4, 1);
		//nk_menu_begin_text()
		nk_layout_row_push(MainUi_Ctx, 45);
		if (nk_menu_begin_label(MainUi_Ctx, "File", NK_TEXT_LEFT, nk_vec2(140, 200))) {
			nk_layout_row_dynamic(MainUi_Ctx, 25, 1);
			Menu_PopulateFile();
			nk_menu_end(MainUi_Ctx);
		}
		if (nk_menu_begin_label(MainUi_Ctx, "Mode", NK_TEXT_LEFT, nk_vec2(140, 200))) {
			nk_layout_row_dynamic(MainUi_Ctx, 25, 1);
			Menu_Populate();
			nk_menu_end(MainUi_Ctx);
		}
		if (nk_menu_begin_label(MainUi_Ctx, "Trig.", NK_TEXT_LEFT, nk_vec2(140, 200))) {
			nk_layout_row_dynamic(MainUi_Ctx, 25, 1);
			Menu_PopulateTrigger();
			nk_menu_end(MainUi_Ctx);
		}

		//nk_button_color(MainUi_Ctx, CurrentEntities[i_clamp].entityDebugColor);
		nk_menubar_end(MainUi_Ctx);
		nk_end(MainUi_Ctx);
	}


}
//Might be better to go back to the old system on this one
void Menu_OpenSpawnPropUI() {
	for (int i = 0; i < Max_Props; i++) {
		SDL_Log(RegisteredProps[i].name);
		if (RegisteredProps[i].name == NULL) {
			//nk_image_lab
			break;
		
		}
	}
	if (nk_begin(MainUi_Ctx, "Spawn Prop", nk_rect(0, 0, 640, 480), NK_WINDOW_TITLE | NK_WINDOW_MOVABLE)) {
		nk_layout_row_dynamic(MainUi_Ctx, 25, 1);
		//int count;

		
			//nk_textedit_init()
			
			//nk_combobox_string(MainUi_Ctx, RegisteredProps[i].name, &SelectedPropIndex, Max_Props, 4, nk_vec2(320, 200));

		//nk_property_int(MainUi_Ctx,"PropIndex",1,i)
		nk_end(MainUi_Ctx);
	}
	
}
void Menu_OpenChangeColorUI() {
//	if (nk_button_color(MainUi_Ctx, nk_rgba(CurrentEntities[i_clamp].entityDebugColor.r, CurrentEntities[i_clamp].entityDebugColor.g, CurrentEntities[i_clamp].entityDebugColor.b, 255))) {
		if (nk_begin(MainUi_Ctx, "Color", nk_rect(0, 220, 320, 200), NK_WINDOW_MOVABLE | NK_WINDOW_TITLE)) {
			nk_layout_row_dynamic(MainUi_Ctx, 64, 1);
			WallColor = nk_color_picker(MainUi_Ctx, WallColor, NK_RGBA);
		
			nk_end(MainUi_Ctx);
			
		}

}
extern SDL_Color Window_Color;
void Menu_OpenCreateBG_UI() {
	

	if (nk_begin(MainUi_Ctx, "Create BG", nk_rect(0, 220, 320, 400), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
#if 0
		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "Start X", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &start_x, 8192, 1);
		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "Start Y", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &start_y, 8192, 1);
		

		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "BG Width", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &start_w, 8192, 1);
		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "BG Height", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &start_h, 8192, 1);
		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "BG Width End", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &end_w, 8192, 1);
		nk_layout_row_dynamic(MainUi_Ctx, 16, 4);
		nk_label(MainUi_Ctx, "BG Height End", NK_TEXT_ALIGN_TOP);
		nk_slider_int(MainUi_Ctx, 0, &end_h, 8192, 1);
#endif
		//CurrentEntities[i_clamp] = *LevelBG_InitNoUpdate(BG_TexPathBuf, false, start_w, start_h);
		
#if 0
		nk_layout_row_dynamic(MainUi_Ctx, 32, 4);
		nk_property_int(MainUi_Ctx, "BG Tile Height", 0, &start_h, 8192, 1, 1.0f);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 4);
		nk_property_int(MainUi_Ctx, "BG Width", 0, &end_w, 8192, 1, 1.0f);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 4);
		nk_property_int(MainUi_Ctx, "BG Height", 0, &end_h, 8192, 1, 1.0f);
#endif
		nk_layout_row_dynamic(MainUi_Ctx, 32, 2);
		nk_label(MainUi_Ctx, "BG Texture Path", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, BG_TexPathBuf, 512, NULL);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 2);
		nk_label(MainUi_Ctx, "BG Tile Width", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, start_w_conv, 5, NULL);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 2);
		nk_label(MainUi_Ctx, "BG Tile Height", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, start_h_conv, 5, NULL);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 2);
		nk_label(MainUi_Ctx, "BG Width", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, end_w_conv, 5, NULL);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 2);
		nk_label(MainUi_Ctx, "BG Height", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, end_h_conv, 5, NULL);
		//nk_layout_row_push(MainUi_Ctx, 50.0);
		nk_layout_row_static(MainUi_Ctx, 0, 64, 2);

		if (nk_button_label(MainUi_Ctx, "Create") == true) {
			if (CurrentEntities[i_clamp].Update == NULL) {
				CurrentEntities[i_clamp] = *Entity_Create("BG0", TexPathBuf, Window_Color, 0, 0, SDL_atof(start_w_conv), SDL_atof(start_h_conv), SDL_atof(end_w_conv), SDL_atof(end_w_conv));
				Entity_CreateTexture(&CurrentEntities[i_clamp], TexPathBuf);
				CurrentEntities[i_clamp].Update = LevelBG_Update;
			}
			
#if 0
			CurrentEntities[i_clamp].entityRenderRect.w = SDL_atoi(end_w_conv);
			CurrentEntities[i_clamp].entityRenderRect.h = SDL_atoi(end_h_conv);;
			CurrentEntities[i_clamp].entityRenderRect.x = StartWallX;
			CurrentEntities[i_clamp].entityRenderRect.y = StartWallY;
#endif
			
			CurrentMode = NONE;
		}

	nk_end(MainUi_Ctx);
}

}
void Menu_OpenResizeUI() {
	if (nk_begin(MainUi_Ctx, "Test", nk_rect(0, 220, 320,200),  NK_WINDOW_MOVABLE | NK_WINDOW_TITLE)) {
		nk_layout_row_dynamic(MainUi_Ctx, 25, 1);
		//nk_layout_row_end(MainUi_Ctx);

		//nk_slider_float(MainUi_Ctx, 0.0f, &CurrentEntities[0].entityRenderRect.w, 720.0f, 1.0f);
		//nk_knob_float(MainUi_Ctx, 0.0f, &test, 2000.0f, 0.5f, NK_RIGHT, 0.0f);
		nk_property_float(MainUi_Ctx, "width", 0.0f, &CurrentEntities[i_clamp].entityRenderRect.w, 8192.0f, 1.0f, 1.0f);
		nk_property_float(MainUi_Ctx, "height", 0.0f, &CurrentEntities[i_clamp].entityRenderRect.h, 8192.0f, 1.0f, 1.0f);
		nk_end(MainUi_Ctx);
	}


}
void Menu_OpenTextureCfgUI() {
	
	if (nk_begin(MainUi_Ctx, "Test", nk_rect(0, 220, 320, 200), NK_WINDOW_MOVABLE | NK_WINDOW_TITLE)) {
		nk_layout_row_dynamic(MainUi_Ctx, 16, 1);
		//TexPathBuf = CurrentEntities[i_clamp].tex_path;
		nk_label(MainUi_Ctx, "BG0 Texture Path", NK_TEXT_ALIGN_TOP);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 1);
		//SDL_Log("&CurrentEntities[0].tex_path=%s,CurrentEntities[0].tex_path=%s", &CurrentEntities[0].tex_path, CurrentEntities[0].tex_path);
		nk_edit_string_zero_terminated(MainUi_Ctx, NK_EDIT_DEFAULT | NK_EDIT_BOX, TexPathBuf,512,NULL);
		nk_layout_row_dynamic(MainUi_Ctx, 32, 1);
		if (nk_button_text(MainUi_Ctx, "Set Texture", 11)) {
			SDL_DestroyTexture(CurrentEntities[0].entityTex);
			Entity_CreateTextureWithTexRes(&CurrentEntities[0], TexPathBuf);
			CurrentMode = NONE;
		}
		nk_end(MainUi_Ctx);
	}
}
void Menu_Populate() {
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(PLACE_WALL), NK_TEXT_LEFT)) {
		CurrentMode = PLACE_WALL;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(MOVE_WALL), NK_TEXT_LEFT)) {
		CurrentMode = MOVE_WALL;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(PLACE_PLAYER_START), NK_TEXT_LEFT)) {
		CurrentMode = PLACE_PLAYER_START;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(MOVE_PLAYER_START), NK_TEXT_LEFT)) {
		CurrentMode = MOVE_PLAYER_START;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(PLACE_SPRITE), NK_TEXT_LEFT)) {
		CurrentMode = PLACE_SPRITE;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(MOVE_SPRITE), NK_TEXT_LEFT)) {
		CurrentMode = MOVE_SPRITE;
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(SCALE_WALL), NK_TEXT_LEFT)) {
		CurrentMode = SCALE_WALL;
		//Menu_OpenResizeUI();
	}
	
	
	
}
void Menu_PopulateFile() {
	if (nk_menu_item_label(MainUi_Ctx, "New", NK_TEXT_LEFT)) {
		//CurrentMode = PLACE_WALL;
		//}
		for (int i = 0; i < MAX_ENTITES - 1; i++) {
			if (CurrentEntities[i].Update != NULL) {
				CurrentEntities[i].Update = NULL;
				CurrentEntities[i] = NullEntity;
			}
		}
	}
	if (nk_menu_item_label(MainUi_Ctx, "Open", NK_TEXT_LEFT)) {
		//CurrentMode = PLACE_WALL;
		CurrentMode = OPEN_FILE;
		//if (OpenFileName == NULL || strlen(OpenFileName) == 0) {
			SDL_ShowOpenFileDialog(Menu_FileDialogFunc, NULL, NULL, Level_Filters, 1, SDL_GetCurrentDirectory(),false);
			//Write
		
		//}
		//else {
			//WriteLevelToScript(PropTextList);
		//}

	}
	if (nk_menu_item_label(MainUi_Ctx, "Save",NK_TEXT_LEFT)) {
		//CurrentMode = PLACE_WALL;
		CurrentMode = SAVE_FILE;
		if (PropTextList == NULL || strlen(PropTextList) == 0) {
			SDL_ShowSaveFileDialog(Menu_FileDialogFunc, NULL, NULL, Level_Filters, 1, SDL_GetCurrentDirectory());
			//Write
			
		}
		else {
			WriteLevelToScript(PropTextList);
		}
	}


}
void Menu_PopulateTrigger() {
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(PLACE_TRIGGER), NK_TEXT_LEFT)) {
		CurrentMode = PLACE_TRIGGER;
		//Menu_OpenResizeUI();
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(MOVE_TRIGGER), NK_TEXT_LEFT)) {
		CurrentMode = MOVE_TRIGGER;
		//Menu_OpenResizeUI();
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(CREATE_BG), NK_TEXT_LEFT)) {
		CurrentMode = CREATE_BG;
		//Menu_OpenResizeUI();
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(COLOR_WALL), NK_TEXT_LEFT)) {
		CurrentMode = COLOR_WALL;
		//Menu_OpenResizeUI();
		//Menu_OpenChangeColorUI();
	}
	if (nk_menu_item_label(MainUi_Ctx, ConvertEditorModeToStr(CHANGE_BGTEX), NK_TEXT_LEFT)) {
		CurrentMode = CHANGE_BGTEX;
		//Menu_OpenResizeUI();
		//Menu_OpenChangeColorUI();
	}
}
