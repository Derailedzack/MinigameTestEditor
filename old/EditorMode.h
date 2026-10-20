typedef enum{
    NONE,
    PLACE_WALL,
    MOVE_WALL,
    PLACE_SPRITE,
    MOVE_SPRITE,
    PLACE_PLAYER_START,
    MOVE_PLAYER_START
}EDITOR_MODE;
const char* ConvertEditorModeToStr(EDITOR_MODE mode);
void PlaceWall();
void MoveWall();
void PlaceSprite();
void Place_PlayerStart();
void HandleMode(EDITOR_MODE mode);