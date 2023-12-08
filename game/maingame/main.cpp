#include <SFML/Graphics.hpp>
#include "menu.h"
#include "Engine.h"

using namespace sf;

void showRule(RenderWindow& window)
{
    bool end = false;
    Image img;
    img.loadFromFile("img/rule.png");
    Texture texture;
    texture.loadFromImage(img);
    Sprite background;
    background.setTexture(texture);
    background.setPosition(Vector2f(0, 0));
    while (window.isOpen() && !end)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    end = true;
                }
            }
        }
        window.clear(Color::Cyan);
        window.draw(background);
        window.display();
    }
}

int main()
{
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);
    window.setMouseCursorVisible(false);
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;
    Font font;
    if (!font.loadFromFile("ofont.ru_Montserrat Alternates.ttf")) return 5;
    Text titul;
    titul.setFont(font);
    initText(titul, 540, 50, L"Лабиринт", 150, Color(90, 90, 150), 4, Color(90, 97, 250));
    String name[]{ L"Старт", L"Загрузить",L"O игре",L"Выход" };
    GameMenu menu(window, 950, 400, 4, name); 
    menu.setColorText(Color(90, 97, 175), Color::Red, Color::Black);
    menu.alignMenu(2);
    Image img;
    img.loadFromFile("img/b.jpg");
    Texture texture;
    texture.loadFromImage(img);
    Sprite background;
    background.setTexture(texture);
    background.setPosition(Vector2f(0,0));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { menu.moveUp(); }
                if (event.key.code == Keyboard::Down) { menu.moveDown(); }
                if (event.key.code == Keyboard::Return)
                {
                    switch (menu.getSelectedMenu())
                    {
                    case 0: 
                    {   
                        Engine engine(window, false);
                        engine.start();
                        break; 
                    }
                    case 1:
                    {
                        Engine engine(window, true);
                        engine.start();
                        break;
                    }
                    case 2:
                    {
                        showRule(window);
                        break;
                    }
                    case 3:
                    {
                        window.close();
                        break;
                    }
                    }
                }
            }
        }

        window.clear(Color::Cyan);
        window.draw(background);
        window.draw(titul);
        menu.draw();
        window.display();
    }
    return 0;
}