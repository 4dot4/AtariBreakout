#include "raylib.h"
#include "components.h"
#include <stdio.h>
#include <stdint.h>
const int height = 900;
const int width = 1500;
const int PlayerSpeed = 10;
int ballXspeed = 10;
int ballYspeed = 10;

Rectangle rec = {
    .width = 139,
    .height = 30,
    .y = 30
    
};
Rectangle player = {
    .width = 150,
    .height = 20,
    .y = 850,
    .x = 400 - 150 / 2
};
Rectangle ballspecs = {
    .width = 10,
    .height = 10,
    .y = 450,
    .x = 750
};






blockers blocks[5][10];
void pysic(Rectangle player, CompleteBall* ball,blockers* blocks){

}
int main(void){

    CompleteBall ball = {
        .ballCords = ballspecs,
        .spdX = 10,
        .spdY = 10 
    };

    bool pause = false;
    InitWindow(width,height,"Atari Breakout");
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

            
            if(x == 0){
                rec.x = 10;
                
            }else{
                rec.x += rec.width + 10;
                
            }
            
            blocks[y][x].spec = rec;
            blocks[y][x].state = true;
        
        }
        rec.y += rec.height + 10;
    }
    
    while (!WindowShouldClose()){


        if(IsKeyPressed(KEY_P)){

            if(pause)
                pause = false;
            else
                pause = true;
        }
        if(!pause){
            if(IsKeyDown(KEY_A))
                if(player.x > 0)
                    player.x -= PlayerSpeed;
            if(IsKeyDown(KEY_D))
                if(player.x + player.width < width)
                    player.x += PlayerSpeed;
            pysic(player,&ball,blocks);
        }            
            


        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(50,800);

        for(int y = 0; y < 5;y++){
            for(int x = 0 ; x < 10; x++){
                if(blocks[y][x].state == true)
                    DrawRectangle(blocks[y][x].spec.x,blocks[y][x].spec.y,blocks[y][x].spec.width,blocks[y][x].spec.height,blocks[y][x].blockColor);
            }
        }
        DrawRectangle(ball.ballCords.x,ball.ballCords.y,ball.ballCords.width,ball.ballCords.height,RAYWHITE);
        DrawRectangle(player.x,player.y,player.width,player.height,RAYWHITE);
        if(pause){
            DrawText("PAUSED",700,450,40,WHITE);
        }
        EndDrawing();
    }

        CloseWindow();
}