#include "Engine.h"
#include <SFML/Graphics.hpp>
#include<math.h>

Engine::Engine(RenderWindow& window, bool flag)
    :window(window)
{
    floorNumber = Floor::first;
    opponent.resize(opponentCount);
    px.resize(opponentCount);
    py.resize(opponentCount);
    loss = false;
    win = false;
    end = false;
    stop = false;
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    if (flag)
    {
        IFile f;
        f.load(map, player, opponent, floorNumber, heartCount, heartPos);
        map.setKeySpritePos();
        changeFloor();
    }
    else
    {
        heartCount = 5;
        heartPos.resize(heartCount);
        map.mazemake();
        setPlayerPos();
        setOpponentPos();
        setHeartPos();
    }

    view = window.getView(); 
    window.setView(view);
}

void Engine::start()
{
    Clock clock;
    float dTime = 0;
    while (window.isOpen()&&!end)
    {    
        if (loss || win) { drawMenu(); clock.restart(); }
        else if (stop) { drawStopMenu(); clock.restart(); }
        else 
        {
            float time = clock.getElapsedTime().asMilliseconds();
            clock.restart();
            dTime += time;

            if (dTime > 5500)
            {
                dTime = 0;
                clearStack();
                for (int i = 0; i < opponentCount; i++)
                {
                    changeDirection(opponent[i]);
                }
            }
            input(time / 100);
            opponentMove(time / 100);
            draw();
            update(time);
        }
    }
}

void Engine::setHeartPos()
{
    for (int i =0; i < heartCount;i++)
    {
        Vector2f v = map.getPos();
        heartPos[i].x = v.x + 20.0;
        heartPos[i].y = v.y + 20.0;
    }
}

void Engine::setHeartSprite()
{
    Image img;
    img.loadFromFile("img/h2.png");
    Texture texture;
    Sprite sprite;
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    for (int i = 0; i < heartCount; i++)
    {
        sprite.setPosition(heartPos[i]);
        window.draw(sprite);
    }
}

void Engine::checkHeart()
{
    for (int i = 0; i < heartCount; i++)
    {
        if (int(player.getXPos()/96) == int(heartPos[i].x/96) && int(player.getYPos()/96) == int(heartPos[i].y/96))
        {
            auto it = heartPos.begin();
            heartPos.erase(it + i);
            heartCount--;
            player.setLives(player.getLives() + 1);
        }
    }
}

void Engine::input(float dT)
{
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        stop = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::RShift) || Keyboard::isKeyPressed(Keyboard::LShift))
    {
        player.setSpeed(25);
    }
    else
    {
        player.setSpeed(15);
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        player.setDir(direction::left);
        if (!(map.itsWall(player.getYPos(), player.getXPos()-1)) && !(map.itsWall(player.getYPos() + player.getHeight() , player.getXPos()-1) ))
        {
            player.move(dT);
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        player.setDir(direction::up);
        if (!(map.itsWall(player.getYPos()-1, player.getXPos()))  && !(map.itsWall(player.getYPos() - 1, player.getXPos()+player.getWidth())))
        {
            player.move(dT);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        player.setDir(direction::right);
        if (!(map.itsWall(player.getYPos(), player.getXPos() + player.getWidth()+1))  && !(map.itsWall(player.getYPos() + player.getHeight(), player.getXPos() + player.getWidth()+1)))
        {
            player.move(dT);
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        player.setDir(direction::down);
        if (!(map.itsWall(player.getYPos()+ player.getHeight()+1, player.getXPos())) && !(map.itsWall(player.getYPos() + player.getHeight() + 1, player.getXPos() +player.getWidth())))
        {
            player.move(dT);
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    player.update();
    for (int i = 0; i < opponentCount; i++)
    {
        opponent[i].update();
    }
    view.setCenter(player.getXPos(), player.getYPos());
    window.setView(view);
    checkKey();
    checkWin();
    checkHeart();
    if (player.getLives()==0)
    {
        loss = true;
    }
}

void Engine::draw()
{
    if (floorNumber == Floor::first)
    {
        Color clr(79, 67, 103);
        window.clear(clr);
    }
    else if (floorNumber == Floor::second)
    {
        Color clr(57, 101, 48);
        window.clear(clr);
    }
    else
    {
        Color clr(125, 201, 223);
        window.clear(clr);
    }
    map.draw(window);
    setHeartSprite();
    window.draw(player.getSprite());
    for (int i = 0; i < opponentCount; i++)
    {
        window.draw(opponent[i].getSprite());
    }
    drawHeart();
    drawInfo();
    window.display();
}

void Engine::drawMenu()
{
    view.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    window.setView(view);
    Font font;
    font.loadFromFile("ofont.ru_Montserrat Alternates.ttf");
    Text titul;
    titul.setFont(font);
    if (win)
    {
        initText(titul, 650, 50, L"Победа", 150, Color(237, 147, 0), 3, Color(200, 147, 50));
        backgroundImg.loadFromFile("img/w.jpg");
    }
    else
    {
        initText(titul, 600, 50, L"Поражение", 150, Color(237, 147, 0), 3, Color(200, 147, 50));
        backgroundImg.loadFromFile("img/l.png");
    }
    backgroundTexture.loadFromImage(backgroundImg);
    background.setTexture(backgroundTexture);
    background.setPosition(Vector2f(0,0));
    String name[]{ L"Заново", L"Меню",L"Выход" }; 
    GameMenu menu(window, 825, 400, 3, name); 
    menu.setColorText(Color(237, 147, 75), Color::Red, Color::Black);

    while (window.isOpen() && (win||loss) && !end)
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
                    // Переходим на выбранный пункт меню 
                    switch (menu.getSelectedMenu())
                    {
                    case 0:
                    {
                        player.setLives(3);
                        win = false;
                        loss = false;
                        floorNumber = Floor::first;
                        reset();
                        break;
                    }
                    case 1:
                    {
                        end = true;
                        break;
                    }
                    case 2:
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
}

void Engine::opponentMove(float dT)
{
    check();
    for (int i = 0; i < opponentCount; i++)
    {
        if (!opponent[i].itsDetected())
        {
            randMove(opponent[i], dT);
        }
        else
        {
            moveToPos(opponent[i], dT, i);
            defeat(opponent[i]);
        }
    }
}

void Engine::check()
{
    for (int i = 0; i < opponentCount; i++)
    {
        int x, y, dx, dy;
        y = opponent[i].getYPos();
        x = opponent[i].getXPos();
        dx = player.getXPos();
        dy = player.getYPos();
        switch (opponent[i].getDir())
        {

        case direction::left:
        {
            int j = 0;
            while (!(map.itsWall(y, x - j)) && (j < 481))
            {
                j +=32;
            }
            if (((y / 96) == (dy / 96)) && (x >= dx) && (x - j <= dx))
            {
                opponent[i].setDetection(true);
            }
            break;
        }
        case direction::right:
        {
            int j = 0;
            while (!(map.itsWall(y, x + j)) && (j < 481))
            {
                j += 32;
            }
            if ((y / 96) == (dy / 96) && (x <= dx) && (x + j >= dx))
            {
                opponent[i].setDetection(true);
            }
            break;
        }
        case direction::up:
        {
            int j = 0;
            while (!(map.itsWall(y - j, x)) && (j < 481))
            {
                j += 32;
            }
            if ( (y  >= dy ) &&  ((x / 96) == (dx / 96)) && (y-j <= dy))
            {
                opponent[i].setDetection(true);
            }
            break;
        }
        case direction::down:
        {
            int j = 0;
            while (!(map.itsWall(y - j, x)) && (j < 481))
            {
                j += 32;
            }
            if ((y <= dy) && (((x) / 96) == (dx / 96)) && (y + j >= dy))
            {
                opponent[i].setDetection(true);
            }
            break;
        }
        }
    }
}

void Engine::checkWin()
{
    if (player.getXPos() + player.getWidth() >= map.getEndX() && player.getYPos() + player.getHeight() >= map.getEndY() && !map.getKey())
    {
        if (floorNumber == Floor::third)
        {
            win = true;
        }
        else if (floorNumber == Floor::second)
        {
            floorNumber = Floor::third;
            reset();
        }
        else
        {
            floorNumber = Floor::second;
            reset();
        }
    }
}

void Engine::checkKey()
{
    if (int(player.getXPos() / 96) == map.getKeyPos().x && int(player.getYPos() / 96) == map.getKeyPos().y)
    {
        map.setKey(false);
    }
}

void Engine::changeDir(Opponent& o)
{
    if (o.getDir() == direction::up || o.getDir() == direction::down)
    {
        if (!map.itsWall(o.getYPos(), o.getXPos() - 96))
        {
            o.setDir(direction::left);
        }
        else if (!map.itsWall(o.getYPos(), o.getXPos() + 96 + o.getWidth()))
        {
            o.setDir(direction::right);
        }
    }
    else
    {
        if (!map.itsWall(o.getYPos() + o.getHeight() + 96, o.getXPos()))
        {
            o.setDir(direction::down);
        }
        else if (!map.itsWall(o.getYPos() - 96, o.getXPos()))
        {
            o.setDir(direction::up);
        }
    }
}

void Engine::randMove(Opponent& opponent, float dT)
{
    switch (opponent.getDir())
    {
    case direction::left:
    {
        if (!(map.itsWall(opponent.getYPos(), opponent.getXPos() - 2)) && !(map.itsWall(opponent.getYPos() + opponent.getHeight(), opponent.getXPos() - 2)))
        {
            opponent.move(dT);
        }
        else
        {
            chooseDir(opponent);
        }
        break;
    }
    case direction::right:
    {
        if (!(map.itsWall(opponent.getYPos(), opponent.getXPos() + opponent.getWidth() + 2)) && !(map.itsWall(opponent.getYPos() + opponent.getHeight(), opponent.getXPos() + opponent.getWidth() + 2)))
        {
            opponent.move(dT);
        }
        else
        {
            chooseDir(opponent);
        }
        break;
    }
    case direction::up:
    {
        if (!(map.itsWall(opponent.getYPos() - 2, opponent.getXPos())) && !(map.itsWall(opponent.getYPos() - 2, opponent.getXPos() + opponent.getWidth())))
        {
            opponent.move(dT);
        }
        else
        {
            chooseDir(opponent);
        }
        break;
    }
    case direction::down:
    {
        if (!(map.itsWall(opponent.getYPos() + opponent.getHeight() + 2, opponent.getXPos())) && !(map.itsWall(opponent.getYPos() + opponent.getHeight() + 2, opponent.getXPos() + opponent.getWidth())))
        {
            opponent.move(dT);
        }
        else
        {
            chooseDir(opponent);
        }
        break;
    }
    }
}

void Engine::moveToPos(Opponent& o, float dT, int num)
{
    int dx, dy, x, y;
    dx = player.getXPos();
    x = o.getXPos();
    dy = player.getYPos();
    y = o.getYPos();
    int j = (y) / 96;
    int i = (x) / 96;
    if (pow(dx-x, 2) + pow(dy - y, 2) > 230400)
    {
        o.setDetection(false);
        while (!py[num].empty()) 
        {
            py[num].pop();
        }
        while (!px[num].empty())
        {
            px[num].pop();
        }
    }
    else
    {   
        if (px[num].empty() || py[num].empty()) { map.lee(x/96, y/96, dx/96, dy/96, px[num], py[num]); }
        if (!px[num].empty() && !py[num].empty())
        {
            if (px[num].top() * 96 > x && !(map.itsWall(y, x + o.getWidth() + 1)) && !(map.itsWall(y + o.getHeight(), x + o.getWidth() + 1)))
            {
                o.setDir(direction::right);
                o.move(dT);
            }
            else if (px[num].top() * 96 < x && !(map.itsWall(y, x - 1)) && !(map.itsWall(y + o.getHeight(), x - 1)))
            {
                o.setDir(direction::left);
                o.move(dT);
            }
            else if (py[num].top() * 96 > y && !(map.itsWall(y + o.getHeight() + 1, x)) && !(map.itsWall(y + o.getHeight() + 1, x + o.getWidth())))
            {
                o.setDir(direction::down);
                o.move(dT);
            }
            else if (py[num].top() * 96 < y && !(map.itsWall(y - 1, x)) && !(map.itsWall(y - 1, x + o.getWidth())))
            {
                o.setDir(direction::up);
                o.move(dT);
            }
            if (px[num].top() == i && py[num].top() == j)
            {
                px[num].pop();
                py[num].pop();
            }
        }
    }
}

void Engine::drawHeart()
{
    Image img;
    img.loadFromFile("img/h.png");
    Texture texture;
    Sprite sprite;
    int x = player.getXPos() - int(VideoMode::getDesktopMode().width/2);
    int y = player.getYPos() - int(VideoMode::getDesktopMode().height/2);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    for (int i = 0; i < player.getLives(); i++)
    {
        sprite.setPosition(Vector2f(x, y));
        window.draw(sprite);
        x += 75;
    }
}

void Engine::defeat(Opponent& o)
{
    if (int(o.getYPos()/96) == int(player.getYPos()/96) && int(o.getXPos()/96) == int(player.getXPos()/96))
    {
        setPlayerPos();
        player.decLives();
        setOpponentPos();
    }
}

void Engine::setPlayerPos()
{
    player.setXPos(map.getStartX());
    player.setYPos(map.getStartY());
}

void Engine::setOpponentPos()
{
    for (int i = 0; i < opponentCount; i++)
    {
        opponent[i].setPos(map.getPos());
        opponent[i].setDetection(false);
        while (!py[i].empty()) { py[i].pop(); }
        while (!px[i].empty()) { px[i].pop(); }
    }
}

void Engine::reset()
{
    map.mazemake();
    setPlayerPos();
    setOpponentPos();
    changeFloor();
    setHeartPos();
}

void Engine::drawInfo()
{
    String str;
    if (floorNumber == Floor::first) { str = L"этаж 1"; }
    if (floorNumber == Floor::second) { str = L"этаж 2"; }
    if (floorNumber == Floor::third) { str = L"этаж 3"; }
    int x = player.getXPos()-int(VideoMode::getDesktopMode().width / 2)+10;
    int y = player.getYPos() +int(VideoMode::getDesktopMode().height / 2.5);
    Text txt;
    Font font;
    font.loadFromFile("ofont.ru_InkVerse.ttf");
    txt.setFont(font);
    if (floorNumber == Floor::first)
    {
        txt.setFillColor(Color(90, 90, 150));
        txt.setOutlineColor(Color(70, 60, 120));
    }
    else if (floorNumber == Floor::second)
    {
        txt.setFillColor(Color(117, 232, 154));
        txt.setOutlineColor(Color(91, 174, 113));
    }
    else
    {
        txt.setFillColor(Color(94, 167, 206));
        txt.setOutlineColor(Color(69, 137, 188));
    }
    txt.setString(str);
    txt.setCharacterSize(50);
    txt.setOutlineThickness(5);
    txt.setPosition(Vector2f(x, y));
    window.draw(txt);
}

void Engine::changeFloor()
{
    if (floorNumber == Floor::first)
    {
        map.changeFloor("img/b0.png", "img/b1.png");
    }
    else if (floorNumber == Floor::second)
    {
        map.changeFloor("img/grass1.png", "img/grass.png");
    }
    else
    {
        map.changeFloor("img/space.png", "img/water.png");
    }
}

void Engine::drawStopMenu()
{
    view.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    window.setView(view);
    Font font;
    font.loadFromFile("ofont.ru_InkVerse.ttf");
    Text titul;
    titul.setFont(font);
    initText(titul, 650, 20, L"Пауза", 150, Color(216, 141, 224), 3, Color(122, 19, 162));
    backgroundImg.loadFromFile("img/stop.png");
    backgroundTexture.loadFromImage(backgroundImg);
    background.setTexture(backgroundTexture);
    background.setPosition(Vector2f(0, 0));
    String name[]{ L"Заново", L"Меню",L"Сохранить",L"Продолжить", L"Выход" };
    GameMenu menu(window, 925, 300, 5, name);
    menu.setColorText(Color(206, 121, 229), Color::Red, Color::White);
    menu.alignMenu(2);
    while (window.isOpen() && (stop) && !end)
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
                    // Переходим на выбранный пункт меню 
                    switch (menu.getSelectedMenu())
                    {
                    case 0:
                    {
                        player.setLives(3);
                        win = false;
                        loss = false;
                        stop = false;
                        floorNumber = Floor::first;
                        reset();
                        break;
                    }
                    case 1:
                    {
                        end = true;
                        break;
                    }
                    case 2:
                    {
                        IFile f;
                        f.save(map, player, opponent, floorNumber, heartCount, heartPos);
                        stop = false;
                        break;
                    }
                    case 3:
                    {
                        stop = false;
                        break;
                    }
                    case 4:
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
}

void Engine::changeDirection(Opponent& opponent)
{
    if (!opponent.itsDetected())
    {
        changeDir(opponent);
    }
}

void Engine::clearStack()
{
    for (int i = 0; i < opponentCount; i++)
    {

        while (!py[i].empty())
        {
            py[i].pop();
        }
        while (!px[i].empty())
        {
            px[i].pop();
        }
    }
}

void Engine::chooseDir(Opponent& o)
{
    switch (o.getDir())
    {
    case direction::up:
    {
        if (!map.itsWall(o.getYPos(), o.getXPos()-96))
        {
            o.setDir(direction::left);
        }
        else if (!map.itsWall(o.getYPos(), o.getXPos() + 96 + o.getWidth()))
        {
            o.setDir(direction::right);
        }
        else if (!map.itsWall(o.getYPos()+o.getHeight() + 96, o.getXPos()))
        {
            o.setDir(direction::down);
        }
        break;
    }

    case direction::down:
    {
        if (!map.itsWall(o.getYPos(), o.getXPos() - 96))
        {
            o.setDir(direction::left);
        }
        else if (!map.itsWall(o.getYPos(), o.getXPos() + 96 + o.getWidth()))
        {
            o.setDir(direction::right);
        }
        else if (!map.itsWall(o.getYPos() - 96, o.getXPos()))
        {
            o.setDir(direction::up);
        }
        break;
    }

    case direction::left:
    {
        if (!map.itsWall(o.getYPos()-96, o.getXPos()))
        {
            o.setDir(direction::up);
        }
        else if (!map.itsWall(o.getYPos() + o.getHeight() + 96, o.getXPos()))
        {
            o.setDir(direction::down);
        }
        else if (!map.itsWall(o.getYPos(), o.getXPos() + 96+o.getWidth()))
        {
            o.setDir(direction::right);
        }
        break;
    }

    case direction::right:
    {
        if (!map.itsWall(o.getYPos() - 96, o.getXPos()))
        {
            o.setDir(direction::up);
        }
        else if (!map.itsWall(o.getYPos() + o.getHeight() + 96, o.getXPos()))
        {
            o.setDir(direction::down);
        }
        else if (!map.itsWall(o.getYPos(), o.getXPos() - 96))
        {
            o.setDir(direction::left);
        }
        break;
    }
    }
}
