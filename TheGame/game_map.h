

#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction.h"
#include "ImageBase.h"

#define MAX_TILES 372

class TileMat : public ImageBase
{
public:
    TileMat() { ; }
    ~TileMat() { ; }
};

class GameMap
{
public:
    GameMap() { ; }
    ~GameMap() { ; }

    void LoadMap(const char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const { return game_map_; };
    void SetMap(Map& map_data) { game_map_ = map_data; };
private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];
};

#endif // GAME_MAP_H
