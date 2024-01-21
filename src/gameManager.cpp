#include "raylib.h"
#include <iostream>
#include <sstream>
#include <string.h>

class GameManager{
    public:
     bool gameRunning;

     void ShowMenu(int width, int height)
     {
     if(!gameRunning)
     {
         DrawText("Press space to start", width / 2 - 120, height / 2 - 40, 20, BLACK);
         if(IsKeyPressed(KEY_SPACE))
             gameRunning = true;
     }
     }

     void GenerateBackGround(Texture2D grass){
     for(int i = 0; i <= 20; i++){
         for(int j = 0; j <= 20; j++){
             if(i == 0 || i == 19 || j == 0 || j == 11){
                 DrawTexture(grass, i * 50, j * 50, WHITE);
             }
         }
     }
     DrawTexture(grass, 0, 0, WHITE);
     }

     void GeneratePoints(int points){
         std::stringstream buferStream;
         buferStream << points;
         std::string bufer = buferStream.str();
         char* textPoints = (char*) bufer.c_str();
         DrawText(textPoints, 100, 100, 40, BLACK);
     }
};