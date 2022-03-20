#include "raylib.h"
#include <stdio.h>
#include <stdint.h>
const int height = 900;
const int width = 1500;
const int PlayerSpeed = 10;
int ballXspeed = 10;
int ballYspeed = 10;
typedef struct blockers{
    Rectangle spec;
    bool state;
    Color blockColor;
}blockers;

Rectangle rec = {
    .width = 138,
    .height = 30,
    
};
Rectangle player = {
    .width = 150,
    .height = 20,
    .y = 850,
    .x = 400 - 150 / 2
};
Rectangle ball = {
    .width = 10,
    .height = 10,
    .y = 450,
    .x = 750
};
blockers blocks[5][10];
int main(void){
    InitWindow(width,height,"Atari Breackout");
    SetTargetFPS(60);
    
    for(int y = 0; y < 5;y++){
    
        for(int x = 0; x < 10; x++){

        switch (y){
            case 0:
                blocks[0][x].blockColor = RED;
                break;
            case 1:
                blocks[1][x].blockColor = ORANGE;
                break;
            case 2:
                blocks[2][x].blockColor = YELLOW;
                break;
            case 3:
                blocks[3][x].blockColor = GREEN;
                break;
            case 4:
                blocks[4][x].blockColor = BLUE;  
                break;            
            default:
                break;
            }

            if(y == 0)  
                rec.y = 30;
            if(x == 0){
                rec.x = 10;
                
            }else{
                rec.x = rec.x + rec.width + 10;
                
            }
            
            blocks[y][x].spec = rec;
            blocks[y][x].state = true;
        
        }
        rec.y = rec.y + rec.height + 10;
    }
    
    while (!WindowShouldClose()){

        if(IsKeyDown(KEY_A))
            if(player.x > 0)
                player.x -= PlayerSpeed;
        if(IsKeyDown(KEY_D))
            if(player.x + player.width < width)
                player.x += PlayerSpeed;        
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawFPS(50,800);
       
        for(int y = 0; y < 5;y++){
            for(int x = 0 ; x < 10; x++){
                if(blocks[y][x].state == true)
                    DrawRectangle(blocks[y][x].spec.x,blocks[y][x].spec.y,blocks[y][x].spec.width,blocks[y][x].spec.height,blocks[y][x].blockColor);
            }
        }
        DrawRectangle(ball.x,ball.y,ball.width,ball.height,RAYWHITE);
        DrawRectangle(player.x,player.y,player.width,player.height,RAYWHITE);
        EndDrawing();
    }

        CloseWindow();
}