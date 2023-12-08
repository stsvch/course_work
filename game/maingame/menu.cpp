#include "menu.h"

void GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos)
{
	text.setFont(font);
	text.setFillColor(colorText);
	text.setString(str);
	text.setCharacterSize(sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(5);
	text.setOutlineColor(borderText);
}

void GameMenu::alignMenu(int pos)
{
	float nullx = 0;
	for (int i = 0; i < maxMenu; i++) {
		switch (pos)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = menuText[i].getLocalBounds().width;
			break;
		case 2:
			nullx = menuText[i].getLocalBounds().width / 2;
			break;
		}
		menuText[i].setPosition(menuText[i].getPosition().x - nullx, menuText[i].getPosition().y);
	}
}

GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int index, sf::String name[], int sizefont, int step)
	:myWindow(window), menuX(menux), menuY(menuy), sizeFont(sizefont), menuStep(step)
{
	if (!font.loadFromFile("ofont.ru_Montserrat Alternates.ttf")) { exit(32); }
	maxMenu = index;
	menuText = new sf::Text[maxMenu]; 
	for (int i = 0, ypos = menuY; i < maxMenu; i++, ypos += menuStep)
	{
		setInitText(menuText[i], name[i], menuX, ypos);
	}
	selected = 0;
	menuText[selected].setFillColor(choseText);
}

void GameMenu::moveUp()
{
	selected--;
	if (selected >= 0) 
	{
		menuText[selected].setFillColor(choseText); 
		menuText[selected + 1].setFillColor(colorText);
	}
	else
	{
		menuText[0].setFillColor(colorText);
		selected = maxMenu - 1;
		menuText[selected].setFillColor(choseText);
	}
}

void GameMenu::moveDown()
{
	selected++;
	if (selected < maxMenu)
	{
		menuText[selected - 1].setFillColor(colorText);
		menuText[selected].setFillColor(choseText);
	}
	else
	{
		menuText[maxMenu - 1].setFillColor(colorText);
		selected = 0;
		menuText[selected].setFillColor(choseText);
	}
}

void GameMenu::draw()
{
	for (int i = 0; i < maxMenu; i++)
	{
		myWindow.draw(menuText[i]);
	}
}

void GameMenu::setColorText(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	colorText = menColor;
	choseText = ChoColor;
	borderText = BordColor;
	for (int i = 0; i < maxMenu; i++)
	{
		menuText[i].setFillColor(colorText);
		menuText[i].setOutlineColor(borderText);
	}
	menuText[selected].setFillColor(choseText);
}
