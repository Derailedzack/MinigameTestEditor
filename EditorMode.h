typedef enum{
    NONE,
    PLACE_WALL,
    MOVE_WALL,
    PLACE_SPRITE,
    MOVE_SPRITE,
    PLACE_PLAYER_START,
    MOVE_PLAYER_START,
    SCALE_WALL,
    PLACE_TRIGGER,
    MOVE_TRIGGER,
    SCALE_TRIGGER,
    COLOR_WALL,
    COLOR_TRIGGER,
    //SPAWN_SPRITE
}EDITOR_MODE;
//I've decided I'll implement trigger placement and movement as a mode instead
typedef enum {
    CHANGE_INDEX,
    CHANGE_SELECTED_PROP, 
    REG_WALL, //Only vaild when in PLACE_WALL and MOVE_WALL mode or I could add this as a separate mode
    TRIGGER_WALL
}EDITOR_MODE_SUBCFG;
const char* ConvertEditorModeToStr(EDITOR_MODE mode);
void PlaceWall();
void MoveWall();
void PlaceSprite();
void Place_PlayerStart();
void HandleMode(EDITOR_MODE mode);
void HandleModeSelection(EDITOR_MODE mode);

//Triggers finally!
void PlaceTrigger();
void MoveTrigger();
//ScaleTrigger will be put in the EditorMenu code (NOT Editor mode as this doesn't have access to the UI)