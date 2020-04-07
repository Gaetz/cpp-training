//
// Created by gaetz on 07/04/2020.
//

#ifndef INC_01_PONG_TEXT_H
#define INC_01_PONG_TEXT_H


#include <raylib.h>
#include <string>

using std::string;

class Text {
public:
    Text() = delete;
    Text(int xP, int yP, string text, int fontSizeP, Color colorP);
    ~Text();

    void Draw();

    void SetText(string textP);

private:
    int x;
    int y;
    string text;
    int fontSize;
    Color color;
};


#endif //INC_01_PONG_TEXT_H
