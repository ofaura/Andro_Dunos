#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL\include\SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define PIXEL_TO_DISTANCE_y(a) (192/307)
#define PI (3.141592)

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 1
#define REN_VSYNC 1

#define BEYBLADE 5
#define CIRCLE 5
#define FIRST 5
#define LITTLE_TURRET_DOWN_HP 5
#define LITTLE_TURRET_UP_HP 5
#define MISSILE_THROWER_HP 5
#define PIPELINER_HP 5
#define SHUTTLE_HP 5
#define SMALL_SPINNER_HP 5
#define SPACE_SHIP_HP 5
#define SPINNER_HP 5
#define WASP_HP 5
#define XWING_HP 5

#endif // __GLOBALS_H__
