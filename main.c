#include "raylib.h"
#include <stdint.h>
const int height = 800;
const int width = 800;

Rectangle player = {
    .width = 30,
    .height = 20,
    .y = 760,
    .x = 400 - 30 / 2
};
int main(void){
    InitWindow(width,height,"Atari Breackout");

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(player.x,player.y,player.width,player.height,RAYWHITE);
        EndDrawing();

    }
    CloseWindow();
    
}