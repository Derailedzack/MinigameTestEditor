
typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int tile_size;
    unsigned int start_col;
    unsigned int start_row;
    char* tiles;
    const char* tile_tex;
}TilemapDat;
TilemapDat* CreateFromScript(const char* test);