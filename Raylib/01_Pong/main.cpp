#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"
#include "Collisions.h"
#include "Text.h"

using std::to_string;

void Update();
void Draw();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;
int playerPoints = 0;
int opponentPoints = 0;

Text playerScoreText = Text(100, 100, to_string(playerPoints), 20, LIGHTGRAY);
Text opponentScoreText = Text(SCREEN_WIDTH - 100, 100, to_string(opponentPoints), 20, LIGHTGRAY);

int result = 0;
Text outcomeText = Text(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 3, "", 40, LIGHTGRAY);

Sound pingSound;
Sound outSound;
Sound wallSound;
Sound victorySound;
Sound defeatSound;
Sound restartSound;

int main() {

    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);
    InitAudioDevice();

    pingSound = LoadSound("assets/ping.wav");
    outSound = LoadSound("assets/out.wav");
    wallSound = LoadSound("assets/wall.wav");
    victorySound = LoadSound("assets/victory.wav");
    defeatSound = LoadSound("assets/defeat.wav");
    restartSound = LoadSound("assets/restart.wav");

    ball = Ball(100, 100, 32, 7, wallSound);
    leftPaddle = Paddle(0, 200, 32, 128, 4);
    rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 32, 128, 4);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Update();
        Draw();
    }

    UnloadSound(pingSound);
    UnloadSound(outSound);
    UnloadSound(wallSound);
    UnloadSound(victorySound);
    UnloadSound(defeatSound);
    UnloadSound(restartSound);
    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context
    return 0;
}

void Update() {
    // Normal game
    if(result == 0) {
        ball.Update();
        leftPaddle.Update();

        RectangleI ballRect = ball.GetRect();
        RectangleI leftPaddleRect = leftPaddle.GetRect();
        bool colliding = Collisions::AABBCollision(ballRect, leftPaddleRect);
        if (colliding) {
            ball.HorizontalBounce(leftPaddleRect.x + leftPaddleRect.width);
            PlaySound(pingSound);
        }

        RectangleI rightPaddleRect = rightPaddle.GetRect();
        colliding = Collisions::AABBCollision(ballRect, rightPaddleRect);
        if (colliding) {
            ball.HorizontalBounce(rightPaddleRect.x - ballRect.width);
            PlaySound(pingSound);
        }

        rightPaddle.UpdateAI(ballRect.y);

        // Points
        if (ball.GetX() < 0) {
            ++opponentPoints;
            ball.SetX(SCREEN_WIDTH / 2);
            ball.InvertSpeedX();
            opponentScoreText.SetText(to_string(opponentPoints));
            PlaySound(outSound);
            // Defeat
            if(opponentPoints >= 7) {
                result = 2;
                outcomeText.SetText("Defeat");
                PlaySound(defeatSound);
            }
        } else if (ball.GetX() > SCREEN_WIDTH - ball.GetWidth()) {
            ++playerPoints;
            ball.SetX(SCREEN_WIDTH / 2);
            ball.InvertSpeedX();
            playerScoreText.SetText(to_string(playerPoints));
            PlaySound(outSound);
            // Victory
            if(playerPoints >= 7) {
                result = 1;
                outcomeText.SetText("Victory");
                PlaySound(victorySound);
            }
        }
    }
    // End game
    else {
        if (IsKeyPressed(KEY_R)) {
            playerPoints = 0;
            opponentPoints = 0;
            playerScoreText.SetText(to_string(playerPoints));
            opponentScoreText.SetText(to_string(playerPoints));
            outcomeText.SetText("");
            PlaySound(restartSound);
            result = 0;
        }
    }
}

void Draw() {
    BeginDrawing();

    ClearBackground(BLACK);
    playerScoreText.Draw();
    opponentScoreText.Draw();
    ball.Draw();
    leftPaddle.Draw();
    rightPaddle.Draw();

    outcomeText.Draw();

    EndDrawing();
}
