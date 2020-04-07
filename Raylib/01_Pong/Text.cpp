//
// Created by gaetz on 07/04/2020.
//

#include "Text.h"

Text::Text(int xP, int yP, string textP, int fontSizeP, Color colorP)
: x(xP), y(yP), text(textP), fontSize(fontSizeP), color(colorP) {

}

Text::~Text() {

}

void Text::SetText(string textP) {
    text = textP;
}

void Text::Draw() {
    DrawText(text.c_str(), x, y, fontSize, color);
}

