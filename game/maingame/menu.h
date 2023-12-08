#pragma once
#include <SFML/Graphics.hpp>

inline void initText(sf::Text& mtext, float xpos, float ypos, sf::String str, int size_font, sf::Color menu_text_color, int bord, sf::Color border_color)
{
	mtext.setCharacterSize(size_font);
	mtext.setPosition(xpos, ypos);
	mtext.setString(str);
	mtext.setFillColor(menu_text_color);
	mtext.setOutlineThickness(bord);
	mtext.setOutlineColor(border_color);
}

	class GameMenu
	{
		float menuX;	
		float menuY;
		int menuStep;	
		int maxMenu;	
		int sizeFont;		
		int selected;	
		sf::Font font;		
		sf::Text* menuText;		
		sf::Color colorText = sf::Color::Cyan;
		sf::Color choseText = sf::Color::Blue;
		sf::Color borderText = sf::Color::Black;

		void setInitText(sf::Text& text, sf:: String str, float xpos, float ypos);

		sf::RenderWindow& myWindow;
	public:
		GameMenu(sf::RenderWindow& window, float menux, float menuy, int index, sf::String name[], int sizefont = 60, int step = 150);
		~GameMenu() { delete[] menuText; };
		void draw();
		void moveUp();
		void moveDown();
		void setColorText(sf::Color mainColor, sf::Color choseColor, sf::Color borderColor);
		void alignMenu(int pos);
		int getSelectedMenu()
		{
			return selected;
		};
	};