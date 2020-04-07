//
// Created by gaetz on 03/04/2020.
//

#ifndef INC_01_PONG_BALL_H
#define INC_01_PONG_BALL_H


#include "RectangleI.h"

class Ball {
public:
    Ball();
    Ball(int xP, int yP, int sizeP, int speedP, Sound& wallSound);
    ~Ball();

    void Update();
    void Draw();

    RectangleI GetRect();
    void HorizontalBounce(int newX);
    void VerticalBounce(int newY);

    int GetX() const;
    void SetX(int xP);
    void InvertSpeedX();

    int GetWidth() const;

private:
    int x;
    int y;
    int size;
    int speedX;
    int speedY;
    Sound wallSound;
};


#endif //INC_01_PONG_BALL_H
