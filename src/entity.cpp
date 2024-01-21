#include "raylib.h"
#pragma once
class Entity{
    protected:
     virtual void Movement();
     
    public:
     float speed;
     Rectangle entity;
     virtual void GenerateEntity();
};
