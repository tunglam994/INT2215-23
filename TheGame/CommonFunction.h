#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

static bool musicOn = true;

//Screen
const int FRAME_PER_SECOND = 18; // fps
const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 576;
const int SCREEN_BPP = 32;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 214
#define TILE_SIZE 32

#define MAX_MAP_X 800
#define MAX_MAP_Y 18

#define GRAVITY_SPEED 1
#define MAX_FALL_SPEED 20

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X]; //mảng 2 chiều lưu tile map
    const char* file_name_;
};

typedef struct Input
{
    int left_;
    int right_;
    int jump_;
};

enum LSwitchSprite {
    SWITCH_SPRITE_MOUSE_ON,
    SWITCH_SPRITE_MOUSE_OFF,
    SWITCH_SPRITE_TOTAL
};
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_TOTAL
};

enum GameState
{
    GAME_IN,
    GAME_OVER,
    GAME_WIN,
    GAME_OUT,
};

namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // COMMON_FUNCTION_H_
