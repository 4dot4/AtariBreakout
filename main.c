#include "raylib.h"
#include "components.h"

#include <stdio.h>

const int height = 900;
const int width = 1500;

const int PlayerSpeed = 15;
int score  = 0;
int ballXspeed = 10;
int ballYspeed = -10;
int start = 0;
unsigned char canceled = 0;

Rectangle rec = {
    .width = 139,
    .height = 30,
    .y = 30
    
};
Rectangle player = {
    .width = 150,
    .height = 30,
    .y = 850,
    .x = 400 - 150 / 2
};
Rectangle ballspecs = {
    .width = 10,
    .height = 10,
    .y = 750,
    .x = 750
};

blockers blocks[5][10];
void restartBall(CompleteBall* ball){
    ball->ballCords.x = GetRandomValue(10,1480);
    ball->ballCords.y = 750;
    ball->spdX = 10;
    ball->spdY = -10;
}
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

void pysic(Rectangle player, CompleteBall* ball,blockers blocks[5][10],int* lifes){
    
    
    

    ball->ballCords.y <= 0? ball->spdY = -ball->spdY : 0;
    ball->ballCords.x + ball->ballCords.width >= width || ball->ballCords.x <= 0? ball->spdX = -ball->spdX : 0;
    ball->ballCords.x += ball->spdX;  
    ball->ballCords.y += ball->spdY;
    if(ball->ballCords.y > height){
        *lifes -= 1;
        restartBall(ball);
    }

    if(colide(ball->ballCords,player) == direita || colide(ball->ballCords,player) == esquerda)
        ball->spdX = -ball->spdX;
    else if(colide(ball->ballCords,player)== cima || colide(ball->ballCords,player) == baixo)
        ball->spdY = -ball->spdY;    
   
     
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 10; x++){
            if(blocks[y][x].state == true){
                //collision of blocks (ball[y][x].spec) it's the rectangle
                if(colide(ball->ballCords,blocks[y][x].spec) == cima || colide(ball->ballCords,blocks[y][x].spec) == baixo){
                    score += 10;
                    canceled++;                    
                    blocks[y][x].state = false;
                    ball->spdY = -ball->spdY;
                }
                else if(colide(ball->ballCords,blocks[y][x].spec) == esquerda || colide(ball->ballCords,blocks[y][x].spec) == direita){
                    blocks[y][x].state = false;
                    canceled++;
                    ball->spdX = -ball->spdX;
                    score += 10;
                }

            }
        }
    }
}
void restartlife(int* lifes){ 
    *lifes = 5;
}
void restartScore(int* score){
    *score = 0;
}
void restartBlocks(int* nivel){

  
    
    canceled = 0;
    rec.y = 30;
    Color levels[6][5] = {
        {RED,ORANGE,YELLOW,GREEN,BLUE},//rainbow
        {BLUE,PINK,RAYWHITE,PINK,BLUE},//tran
        {RAYWHITE,BLUE,BLUE,BLUE,RED},//russia
        {GREEN,YELLOW,BLUE,YELLOW,GREEN},//brasil
        {PINK,PINK,PURPLE,BLUE,BLUE},//bi
        {BLUE,BLUE,BLUE,YELLOW,YELLOW}//ulkraine
    };

    for(int y = 0; y < 5;y++){   
        for(int x = 0; x < 10; x++){

        switch (y){
            case 0:
                blocks[y][x].blockColor = levels[*nivel][0];
                break;
            case 1:
                blocks[y][x].blockColor = levels[*nivel][1];
                break;
            case 2:
                blocks[y][x].blockColor = levels[*nivel][2];
                break;
            case 3:
                blocks[y][x].blockColor = levels[*nivel][3];
                break;
            case 4:
                blocks[y][x].blockColor = levels[*nivel][4];  
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
}
int main(void){

  
    int logoPositionX = GetScreenWidth()/2 - 128;
    int logoPositionY = GetScreenHeight()/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;

    int lifes = 5;
    int nivel = GetRandomValue(0,5);

    CompleteBall ball = {
        .ballCords = ballspecs,
        .spdX = ballXspeed,
        .spdY = ballYspeed 
    };
    
     
    Color lifeColor = GREEN;
    
    bool pause = false;
    InitWindow(width,height,"Atari Breakout");
    InitAudioDevice();
    SetTargetFPS(60); 
    
    Music music1 = LoadMusicStream("../resources/music1.mp3");
    music1.looping = true;
    PlayMusicStream(music1);
    
   
    restartBlocks(&nivel);
    
    while (!WindowShouldClose()){
       
        UpdateMusicStream(music1);

        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter/12)       // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if(state == 4){ 
            
        }
        if(start >0){
          if(IsKeyPressed(KEY_P)){
            
            
                if(pause){
                        ResumeMusicStream(music1);
                    pause = false;
                }else{
                    PauseMusicStream(music1);
                    pause = true;
                }

            }  
        }
        
        
        if(!pause){
            if(IsKeyDown(KEY_A))
                if(player.x > 0)
                    player.x -= PlayerSpeed;
            if(IsKeyDown(KEY_D))
                if(player.x + player.width < width)
                    player.x += PlayerSpeed;
            if(lifes > 0){
                if(start == 1){
                    if(canceled != 50)
                        pysic(player,&ball,blocks,&lifes);
                    else{
                        nivel = GetRandomValue(0,5);    
                        restartBlocks(&nivel);
                        restartBall(&ball);
                        lifes++;
                    }    
                }    
            }           
               
        }            
        if(lifes == 0){
            if(IsKeyPressed(KEY_R)){
                restartBlocks(&nivel);
                restartlife(&lifes);
                restartBall(&ball);
                restartScore(&score);
            }
        }    
        if(lifes < 3)
            lifeColor = RED;
        else if(lifes > 3)
            lifeColor = GREEN;
        
        BeginDrawing();

        ClearBackground(BLACK);

        if(start == 0){
           if (state == 0)
            {
                if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, WHITE);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

                DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

                DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

                DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

                DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
            }
            else if(state == 4){
                start = 1;
            } 
        }
        
        if(start == 1){
          if(lifes > 0){
            for(int y = 0; y < 5;y++){
                for(int x = 0 ; x < 10; x++){
                    if(blocks[y][x].state == true)
                        DrawRectangle(blocks[y][x].spec.x,blocks[y][x].spec.y,blocks[y][x].spec.width,blocks[y][x].spec.height,blocks[y][x].blockColor);
                    }
                }
            DrawText(TextFormat("Score: %d",score),1200,800,40,RAYWHITE);   
            DrawText(TextFormat("%d",lifes),50,800,40,lifeColor);
            DrawRectangle(ball.ballCords.x,ball.ballCords.y,ball.ballCords.width,ball.ballCords.height,RAYWHITE);
            DrawRectangle(player.x,player.y,player.width,player.height,RAYWHITE);
            if(pause){
                DrawText("PAUSED",700,450,40,WHITE);
            }  
        }else{
            DrawText("Game Over",580,450,80,RED);
            DrawText(TextFormat("Score: %d",score),680,600,40,RAYWHITE);
            DrawText("Press r to restart",640,700,30,RAYWHITE);
        }  
        }    
        
        
        EndDrawing();
    }
    UnloadMusicStream(music1);
    CloseAudioDevice();
    CloseWindow();
}
