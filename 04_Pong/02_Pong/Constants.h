#pragma once
#include "Vector2.h"

// Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Net
const int NET_WIDTH = 4;
const int NET_HEIGHT = 50;
const int NET_SPACE = 12;

// Game setup
const Vector2 BALL_START = Vector2(100, 100);
const Vector2 BALL_SPEED = Vector2(250, 250);
const Vector2 OPPONENT_START = Vector2(SCREEN_WIDTH - 20, 250);
const float PADDLE_BOUNCE_MULT = 10.f;
const int OPPONENT_SPEED = 5;
const int DEAD_ZONE_HEIGHT = 25;
const int MAX_SCORE = 3;
