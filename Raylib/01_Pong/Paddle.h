//
// Created by gaetz on 07/04/2020.
//

#ifndef INC_01_PONG_PADDLE_H
#define INC_01_PONG_PADDLE_H

#include "RectangleI.h"

class Paddle {
public:
    Paddle();
    Paddle(int xP, int yP, int widthP, int heightP, int speedP);
    ~Paddle();

    void Update();
    void Draw();

    RectangleI GetRect();
    void MoveUp();
    void MoveDown();
    void UpdateAI(int ballY);

private:
    int x;
    int y;
    int width;
    int height;
    int speedY;
};


#endif //INC_01_PONG_PADDLE_H
