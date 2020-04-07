//
// Created by gaetz on 03/04/2020.
//

#include <raylib.h>
#include "Ball.h"

Ball::Ball() {
    x = 0;
    y = 0;
    size = 32;
}

Ball::Ball(int xP, int yP, int sizeP, int speedP, Sound& wallSoundP)
: x(xP), y(yP), size(sizeP), speedX(speedP), speedY(speedP), wallSound(wallSoundP) {

}

Ball::~Ball() {

}

void Ball::Update() {
    x += speedX;
    y += speedY;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    if(y < 0) {
        PlaySound(wallSound);
        VerticalBounce(0);
    }
    if(y > screenHeight - size) {
        PlaySound(wallSound);
        VerticalBounce(screenHeight - size);
    }
}

void Ball::Draw() {
    DrawRectangle(x, y, size, size, WHITE);
}

RectangleI Ball::GetRect() {
    return RectangleI {x, y, size, size};
}

void Ball::HorizontalBounce(int newX) {
    InvertSpeedX();
    x = newX;
}

void Ball::VerticalBounce(int newY) {
    speedY = -speedY;
    y = newY;
}

int Ball::GetX() const {
    return x;
}

void Ball::SetX(int xP) {
    x = xP;
}

int Ball::GetWidth() const {
    return size;
}

void Ball::InvertSpeedX() {
    speedX = -speedX;
}
