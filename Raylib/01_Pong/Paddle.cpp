//
// Created by gaetz on 07/04/2020.
//

#include <raylib.h>
#include "Paddle.h"

Paddle::Paddle() {
    width = 32;
    height = 128;
    speedY = 4;
}

Paddle::Paddle(int xP, int yP, int widthP, int heightP, int speedP)
: x(xP), y(yP), width(widthP), height(heightP), speedY(speedP) {

}

Paddle::~Paddle() {

}

void Paddle::Update() {
    if(IsKeyDown(KEY_UP)) {
        MoveUp();
    }
    if(IsKeyDown(KEY_DOWN)) {
        MoveDown();
    }
}

void Paddle::Draw() {
    DrawRectangle(x, y, width, height, WHITE);
}

RectangleI Paddle::GetRect() {
    return RectangleI {x, y, width, height};
}

void Paddle::MoveUp() {
    y -= speedY;
    if(y < 0) {
        y = 0;
    }
}

void Paddle::MoveDown() {
    int screenHeight = GetScreenHeight();
    y += speedY;
    if(y > screenHeight - height) {
        y = screenHeight - height;
    }
}

void Paddle::UpdateAI(int ballY) {
    if(ballY < y + height / 4) {
        MoveUp();
    }
    if(ballY > y + 3 * height / 4) {
        MoveDown();
    }
}
