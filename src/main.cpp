#include "raylib.h"
#include <iostream>
#include "gameManager.cpp"
#include "player.cpp"
#include "enemy.cpp"

int main(void)
{
    const int maxNumberOfEnemies = 20;
    const int screenWidth = 1000;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Gamink");

    
    GameManager gameManager;
    Bullet bullets[100];
    Enemy enemies[20];
    
    Texture2D grass = LoadTexture("Tile.png");

    int bulletArrIndex = 0;
    int frameCounter = 0; 
    int enemyID = 0;
    static int enemiesCounter = 0;
    int points =0;
    Player player(screenWidth, screenHeight);

    gameManager.gameRunning = false;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(VIOLET);
        gameManager.GenerateBackGround(grass);
        gameManager.ShowMenu(screenWidth, screenHeight);
        if(gameManager.gameRunning)
        {
            gameManager.GeneratePoints(points);
            player.GenerateEntity();
            KeyboardKey pressedKey = KEY_NULL;
            if(IsKeyPressed(KEY_UP))    { pressedKey = KEY_UP; }
            if(IsKeyPressed(KEY_DOWN))  { pressedKey = KEY_DOWN; }
            if(IsKeyPressed(KEY_RIGHT)) { pressedKey = KEY_RIGHT; }
            if(IsKeyPressed(KEY_LEFT))  { pressedKey = KEY_LEFT; }

            if(pressedKey == KEY_UP || pressedKey == KEY_DOWN || pressedKey == KEY_RIGHT || pressedKey == KEY_LEFT){
                bool isFilled = false;
                do{
                if(bullets[bulletArrIndex].direction == 0){
                    bullets[bulletArrIndex] = player.Shooting(pressedKey);
                    isFilled = true;
                }
                bulletArrIndex++;
                } while(!isFilled);
                
                if(bulletArrIndex > 99){
                    bulletArrIndex = 0;
                }
            }
            
            if(frameCounter % 120 == 0){
                int enemiesToSpawn = std::rand() % 4 + 1;
                bool didSpawnEnemy;
                do{
                    if(enemiesToSpawn + enemiesCounter <= maxNumberOfEnemies){
                        for(int i = 0; i < enemiesToSpawn; i++){
                            int locationToSpawn = std::rand() % 4;
                            float x = 0, y = 0;
                            switch(locationToSpawn){
                                case 0:
                                    x = 0; y = GetScreenHeight() / 2;
                                    break;
                                case 1:
                                    x = GetScreenWidth() - 32; y = GetScreenHeight() / 2;
                                    break;
                                case 2:
                                    x = GetScreenWidth() / 2; y = 0;
                                    break;
                                case 3:
                                    x = GetScreenWidth() / 2; y = GetScreenHeight() - 32;
                                    break;
                            }
                            for(int i = 0; i < 20; i++){
                                if(enemies[i].speed == 0){
                                    Enemy enemySpawn(x, y, enemyID);
                                    enemyID++;
                                    enemies[i] = enemySpawn;
                                    break;
                                }
                            }
                        }
                        didSpawnEnemy = true;
                    }
                    else{
                        enemiesToSpawn --;
                    }
                }while(!didSpawnEnemy && enemiesToSpawn != 0);
                
            }
            
            for(int i = 0; i < 100; i++){
                if(bullets[i].direction != 0){
                    bullets[i].GenerateEntity();
                }
            }

            for(int i = 0; i < 20; i++){
                enemies[i].GenerateEnemy(player, bullets, enemiesCounter, player, enemies);
                if(CheckCollisionRecs(enemies[i].entity, player.entity)){
                    player.entity.x = GetScreenWidth() / 2;
                    player.entity.y = GetScreenHeight() / 2;
                    gameManager.gameRunning = false;
                    points = 0;
                    for(int j = 0; j < 20; j++)
                    {
                        enemies[j].speed = 0;
                        enemies[j].entity.x = -200;
                    }
                    for(int j = 0; j < 100; j++)
                    {
                        bullets[j].direction = 0;
                        bullets[j].entity.x = -200;
                    }
                }
                if(enemies[i].isDead){
                    enemies[i].isDead = false;
                    points += 10;
                }
            }
        }
        EndDrawing();
        frameCounter ++;
    } 

    UnloadTexture(grass);

    CloseWindow();
    return 0;
}