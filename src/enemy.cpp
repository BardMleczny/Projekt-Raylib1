#include <iostream>
#include "raylib.h"
#include "player.cpp"
#include "entity.cpp"
#include "bullet.cpp"
#pragma once

class Enemy : public Entity{
    private:
     void Movement(){
        return;
     }
     void GenerateEntity(){
        return;
     }

    public:
     bool isDead = false;
     int enemyID;
     void Movement(int playerX, int playerY, Bullet bullets[], int enemiesCounter, Player player, Enemy enemies[]){
         int distanceX = abs(playerX - entity.x); 
         int distanceY = abs(playerY - entity.y);
         if(distanceX >= distanceY){
             if(playerX < entity.x){
                 entity.x -= speed;
                 for(int i = 0; i < 20; i++){
                     if(CheckCollisionRecs(entity, enemies[i].entity) && enemies[i].enemyID != enemyID){ entity.x += speed; }
                 }
             }
             else{
                 entity.x += speed;
                 for(int i = 0; i < 20; i++){
                     if(CheckCollisionRecs(entity, enemies[i].entity) && enemies[i].enemyID != enemyID) { entity.x -= speed; }
                 }
             }
         }
         else {
             if(playerY < entity.y){
                 entity.y -= speed;
                 for(int i = 0; i < 20; i++){
                     if(CheckCollisionRecs(entity, enemies[i].entity) && enemies[i].enemyID != enemyID) { entity.y += speed; }
                 }
             }
             else{
                 entity.y += speed;
                 for(int i = 0; i < 20; i++){
                     if(CheckCollisionRecs(entity, enemies[i].entity) && enemies[i].enemyID != enemyID) { entity.y -= speed; }
                 }
             }
         }
         for(int i = 0; i < 100; i++){
            if(CheckCollisionRecs(entity, bullets[i].entity) && bullets[i].entity.x > 0){
                isDead = true;
                bullets[i].direction = 0;
                bullets[i].entity.x = -1000;
                entity.x = -100 * enemyID;
                entity.y = -300;
                speed = 0;
                enemiesCounter --;
            }
         }
         
         for(int i = 0; i < 20; i++){
            if(enemies[i].entity.x == entity.x && enemies[i].entity.y == entity.y && enemies[i].enemyID != enemyID){
                if(entity.x == 0) { entity.y += 36; }
                if(entity.x == GetScreenWidth() / 2) { entity.x += 36; }
                if(entity.x == GetScreenWidth() - 32) { entity.y += 36; }
            }
         }
         
     }

     Enemy(float x, float y, int ID){
        entity = {x, y, 32, 32};
        speed = 2;
        enemyID = ID;
     }

     Enemy(){
        speed = 0;
        entity = {-100, -100, 32, 32};
     }

     void GenerateEnemy(Player playerObj, Bullet bullets[], int enemiesCounter, Player player, Enemy enemies[]){
        DrawRectangleRec(entity, RED);
        Movement(playerObj.entity.x, playerObj.entity.y, bullets, enemiesCounter, player, enemies);
     }
};
