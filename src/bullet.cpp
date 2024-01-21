#include "raylib.h"
#include "entity.cpp"
#pragma once

class Bullet : public Entity{
    private:
     void Movement() override{
        switch (direction)
        {
        case 1:
            entity.y -= speed;
            break;

        case 2:
            entity.y += speed;
            break;

        case 3:
            entity.x += speed;
            break;

        case 4:
            entity.x -= speed;
            break;

        default:
            break;
        }
        if(entity.x < -20 || entity.x > GetScreenWidth() || entity.y < -20 || entity.y > GetScreenHeight()){
            direction = 0;
            entity.x = -1000;
        }
     }

    public:
     int direction;
     Bullet(float x, float y,  int direction){
        this -> direction = direction;
        entity = {x, y, 5, 5};
        speed = 4;
     }

     Bullet(){
        direction = 0;
     }

     void GenerateEntity() override{
        DrawRectangleRec(entity, RED);
        Movement();
     }
};
