#include "raylib.h"
#include "components.h"
#include <stdio.h>
#include <stdlib.h>
const int height = 900;
const int width = 1500;
const int PlayerSpeed = 15;
int ballXspeed = 10;
int ballYspeed = 10;
int lifes = 5;
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
typeCollision colide(Rectangle rect1, Rectangle rect2){

    if(rect1.x + rect1.width >= rect2.x){
        if (rect1.x < rect2.x &&
            rect1.y + rect1.height > rect2.y &&
            rect1.y < rect2.y + rect2.height){
                
                return direita;
            }            
    }
    if (rect1.x <= rect2.x + rect2.width){
        if( rect1.x + rect1.width > rect2.x + rect2.width&&
            rect1.y + rect1.height > rect2.y &&
            rect1.y < rect2.y + rect2.height){
                
                return esquerda;
            }
    }
    if(rect1.y + rect1.height >= rect2.y){
        if( rect1.x + rect1.width >= rect2.x &&
            rect1.x <= rect2.x + rect2.width &&
            rect1.y < rect2.y){
           
                return baixo;
            }
    }
    if(rect1.y <= rect2.y + rect2.height){
        if( rect1.x + rect1.width >= rect2.x &&
            rect1.x <= rect2.x + rect2.width &&
            rect1.y + rect1.height > rect2.y + rect2.height){
               
                return cima;
            }
    }
    return nada;
        
}

void pysic(Rectangle player, CompleteBall* ball,blockers blocks[5][10],int lifes){
    
    
    

    ball->ballCords.y + ball->ballCords.height >= height || ball->ballCords.y <= 0? ball->spdY = -ball->spdY : 0;
    ball->ballCords.x + ball->ballCords.width >= width || ball->ballCords.x <= 0? ball->spdX = -ball->spdX : 0;
    ball->ballCords.x += ball->spdX;  
    ball->ballCords.y += ball->spdY;
    
    if(colide(ball->ballCords,player) == direita || colide(ball->ballCords,player) == esquerda)
        ball->spdX = -ball->spdX;
    else if(colide(ball->ballCords,player)== cima || colide(ball->ballCords,player) == baixo)
        ball->spdY = -ball->spdY;    
   
     
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 10; x++){
            if(blocks[y][x].state == true){
                //collision of blocks (ball[y][x].spec) it's the rectangle
                if(colide(ball->ballCords,blocks[y][x].spec) == cima || colide(ball->ballCords,blocks[y][x].spec) == baixo){
                    
                    blocks[y][x].state = false;
                    ball->spdY = -ball->spdY;
                }
                else if(colide(ball->ballCords,blocks[y][x].spec) == esquerda || colide(ball->ballCords,blocks[y][x].spec) == direita){
                    blocks[y][x].state = false;
                    ball->spdX = -ball->spdX;
                }

            }
        }
    }
}
int main(void){

   
    CompleteBall ball = {
        .ballCords = ballspecs,
        .spdX = ballXspeed,
        .spdY = ballYspeed 
    };
    char outputStr[5];

    bool pause = false;
    InitWindow(width,height,"Atari Breakout");
    SetTargetFPS(60);
    
    for(int y = 0; y < 5;y++){
       
        for(int x = 0; x < 10; x++){

        switch (y){
            case 0:
                blocks[y][x].blockColor = RED;
                break;
            case 1:
                blocks[y][x].blockColor = ORANGE;
                break;
            case 2:
                blocks[y][x].blockColor = YELLOW;
                break;
            case 3:
                blocks[y][x].blockColor = GREEN;
                break;
            case 4:
                blocks[y][x].blockColor = BLUE;  
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
           
                    
            pysic(player,&ball,blocks,lifes);
        }            
            

        itoa(lifes,outputStr,10); 
        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(50,800);
           
        for(int y = 0; y < 5;y++){
            for(int x = 0 ; x < 10; x++){
                if(blocks[y][x].state == true)
                    DrawRectangle(blocks[y][x].spec.x,blocks[y][x].spec.y,blocks[y][x].spec.width,blocks[y][x].spec.height,blocks[y][x].blockColor);
            }
        }
        DrawText(outputStr,1400,800,40,RAYWHITE);
        DrawRectangle(ball.ballCords.x,ball.ballCords.y,ball.ballCords.width,ball.ballCords.height,RAYWHITE);
        DrawRectangle(player.x,player.y,player.width,player.height,RAYWHITE);
        if(pause){
            DrawText("PAUSED",700,450,40,WHITE);
        }
        EndDrawing();
    }

        CloseWindow();
}
