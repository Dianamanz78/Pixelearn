#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "raylib.h"
#include "raymath.h"

//compile:  gcc drawing.c raylib.dll -o draw -opengl32 -lgdi32 -lwinmm //////// ./pengl32.exe

int main(void)
{
    const int screenWidth = 426 * 2;
    const int screenHeight = 397 * 2;
    double penSize = 20;
    char lastLetter;
    int lastColor;
    Color chosenColor = BLACK;
    bool colorMenuActive;

    Image pen = LoadImage("penTool.png");
    Image eraser = LoadImage("eraserTool.png");
    Image circlepen = LoadImage("circlepenTool.png");
    Image squarepen = LoadImage("squarepenTool.png");
    Image test = LoadImage("colorTool.png");
    Image returnt = LoadImage("returnTool.png");

    Rectangle menuBar = {(screenWidth / 2) - 350, screenHeight - 75, 700, 75};
    Rectangle scrollBar = {(screenWidth / 2) - 350, screenHeight - 120, 700, 20};
    Rectangle scroll = {(screenWidth / 2) - 355, screenHeight - 125, 20, 30};

    InitWindow(screenWidth, screenHeight, "PIXELEARN");

    Rectangle colorRed = {82, screenHeight - 68, 64, 64};
    Rectangle colorOrange = {156, screenHeight - 68, 64, 64};
    Rectangle colorYellow = {230, screenHeight - 68, 64, 64};
    Rectangle colorGreen = {304, screenHeight - 68, 64, 64};
    Rectangle colorBlue = {378, screenHeight - 68, 64, 64};
    Rectangle colorPurple = {452, screenHeight - 68, 64, 64};
    Rectangle colorBlack = {526, screenHeight - 68, 64, 64};

    Texture2D penTex = LoadTextureFromImage(pen);
    Texture2D eraserTex = LoadTextureFromImage(eraser);
    Texture2D circlepenTex = LoadTextureFromImage(circlepen);
    Texture2D squarepenTex = LoadTextureFromImage(squarepen);
    Texture2D undoTex = LoadTextureFromImage(test);
    Texture2D returnTex = LoadTextureFromImage(returnt);

    Rectangle texRectpen = {82, 725, 64, 64};
    Rectangle texRecteraser = {156, 725, 64, 64};
    Rectangle texRectundo = {230, 725, 64, 64};
    Rectangle texRectreturn = {304, 725, 64, 64};
    Rectangle texRectsquarepen = {706, 725, 64, 64};
    Rectangle texRectcirclepen = {632, 725, 64, 64};


    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(canvas);
    ClearBackground(WHITE);
    EndTextureMode();

    Vector2 startMousePos = GetMousePosition();
    Vector2 endMousePos = GetMousePosition();

    SetTargetFPS(500);

    while (!WindowShouldClose())
    {
        endMousePos = GetMousePosition();

        if (CheckCollisionPointRec(GetMousePosition(), texRectpen) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'P';
        }
        else if (CheckCollisionPointRec(GetMousePosition(), texRecteraser) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'E';
        }
        else if (CheckCollisionPointRec(GetMousePosition(), texRectundo) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'O';
            colorMenuActive = true;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), texRectcirclepen) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'C';
        }
        else if (CheckCollisionPointRec(GetMousePosition(), texRectsquarepen) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'S';
        }
        else if (CheckCollisionPointRec(GetMousePosition(), texRectreturn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            lastLetter = 'U';
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), scroll) && GetMouseX() > scrollBar.x && GetMouseX() < (scrollBar.x + scrollBar.width))
        {
            penSize = 0;
            scroll.x = GetMouseX() - 10;
        }
   
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            BeginTextureMode(canvas);
            if (lastLetter == 'S')
            {
                DrawRectangle((int)GetMouseX(), (int)GetMouseY(), penSize, penSize, chosenColor);
            }
            else if (lastLetter == 'C')
            {
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), penSize / 2, chosenColor);
                DrawLineEx(startMousePos, endMousePos, penSize, chosenColor);
            }
            else if (lastLetter == 'E')
            {
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), penSize / 2, WHITE);
                DrawLineEx(startMousePos, endMousePos, penSize, WHITE);
            }
            EndTextureMode();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorRed))
        {
            chosenColor = RED;
            printf("red");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorOrange))
        {
            chosenColor = ORANGE;
            printf("orange");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorYellow))
        {
            chosenColor = YELLOW;
            printf("yellow");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorGreen))
        {
            chosenColor = GREEN;
            printf("green");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorBlue))
        {
            chosenColor = BLUE;
            printf("blue");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorPurple))
        {
            chosenColor = PURPLE;
            printf("purple");
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), colorBlack))
        {
            chosenColor = BLACK;
            printf("black");
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), menuBar))
        {
            colorMenuActive = false;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            penSize = 100 * ((scroll.x - scrollBar.x) / scrollBar.width);
        }

        if (lastLetter == 'O' && colorMenuActive == true)
        {
            BeginTextureMode(canvas);
            DrawRectangleRec(menuBar, GRAY);
            DrawRectangleRec(colorRed, RED);
            DrawRectangleRec(colorOrange, ORANGE);
            DrawRectangleRec(colorYellow, YELLOW);
            DrawRectangleRec(colorGreen, GREEN);
            DrawRectangleRec(colorBlue, BLUE);
            DrawRectangleRec(colorPurple, PURPLE);
            DrawRectangleRec(colorBlack, BLACK);
            EndTextureMode();
        }
        else
        {
            BeginTextureMode(canvas);
            DrawRectangleRec(menuBar, LIGHTGRAY);
            DrawTextureEx(penTex, (Vector2){82, 725}, 0, 0.5, WHITE);
            DrawTextureEx(eraserTex, (Vector2){156, 725}, 0, 0.5, WHITE);
            DrawTextureEx(squarepenTex, (Vector2){706, 725}, 0, 0.5, WHITE);
            DrawTextureEx(circlepenTex, (Vector2){632, 725}, 0, 0.5, WHITE);
            DrawTextureEx(undoTex, (Vector2){230, 725}, 0, 0.5, WHITE);
            DrawTextureEx(returnTex, (Vector2){304, 725}, 0, 0.5, WHITE);
            EndTextureMode();
        }

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureRec(canvas.texture, (Rectangle){0, 0, canvas.texture.width, -canvas.texture.height}, (Vector2){0, 0}, WHITE);
        
        DrawRectangleRec(scrollBar, GRAY);
        DrawRectangleRec(scroll, SKYBLUE);

        EndDrawing();
        startMousePos = endMousePos;
    }

    CloseWindow();

    return 0;
}
