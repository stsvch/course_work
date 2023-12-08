#pragma once
#include <SFML/Graphics.hpp>

void initText(sf::Text& mtext, float xpos, float ypos, sf::String str, int size_font, sf::Color menu_text_color, int bord, sf::Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}
