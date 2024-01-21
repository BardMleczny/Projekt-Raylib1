#include "raylib.h"
#include "bullet.cpp"
#include "entity.cpp"
#pragma once

class Player : public Entity{
    private:
     void Movement() override{
         if(IsKeyDown(KEY_A)) { entity.x -= speed; if(entity.x < 0) { entity.x += speed; } }
         if(IsKeyDown(KEY_D)) { entity.x += speed; if(entity.x > GetScreenWidth() - 32) { entity.x -= speed; } }
         if(IsKeyDown(KEY_W)) { entity.y -= speed; if(entity.y < 0) { entity.y += speed; } }
         if(IsKeyDown(KEY_S)) { entity.y += speed; if(entity.y > GetScreenHeight()  - 32) { entity.y -= speed; } }
     }
 
    public: 
     Player(float width, float height){
         entity = {width / 2 - 16, height / 2 - 16, 32, 32};
         speed = 3;
     }

     void GenerateEntity() override{
        DrawRectangleRec(entity, BLACK);
        Movement();
     }
     
     Bullet Shooting(KeyboardKey key){
        int parameters[] = {0, 0, 0};
        switch (key)
        {
        case KEY_UP:
            parameters[0] = entity.x + 14;
            parameters[1] = entity.y - 5;
            parameters[2] = 1;
            break;

        case KEY_DOWN:
            parameters[0] = entity.x + 14;
            parameters[1] = entity.y + 32;
            parameters[2] = 2;
            break;

        case KEY_RIGHT:
            parameters[0] = entity.x + 32;
            parameters[1] = entity.y + 14;
            parameters[2] = 3;
            break;

        case KEY_LEFT:
            parameters[0] = entity.x - 5;
            parameters[1] = entity.y + 14;
            parameters[2] = 4;
            break;
        
        default:
            break;

        }

        Bullet bullet(parameters[0], parameters[1], parameters[2]);
        return bullet;
     }
};