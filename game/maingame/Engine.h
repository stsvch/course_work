#pragma once
#include"menu.h"
#include "IFile.h"

using namespace sf;

class Engine
{
private:
    Floor floorNumber;
    int opponentCount = 4;
    RenderWindow& window;
    Player player;
    vector<Opponent> opponent;
    vector<Vector2f> heartPos;
    void setHeartPos();
    int heartCount;
    void setHeartSprite();
    void checkHeart();
    Image backgroundImg;
    Texture backgroundTexture;
    Sprite background;
    Map map;
    bool win;
    bool end;
    bool loss;
    bool stop;
    void input(float dT);
    void update(float dtAsSeconds);
    void draw();
    View view;
    void drawMenu();
    void opponentMove(float dT);
    void chooseDir(Opponent& o);
    void check();
    void checkWin();
    void checkKey();
    void changeDir(Opponent& o);
    void randMove(Opponent& opponent, float dT);
    void moveToPos(Opponent& o, float dT, int num);
    void drawHeart();
    void defeat(Opponent& o);
    vector<stack<int>> px;
    vector<stack<int>> py;
    void setPlayerPos();
    void setOpponentPos();
    void reset();
    void drawInfo();
    void changeFloor();
    void drawStopMenu();
    void changeDirection(Opponent &opponent);
    void clearStack();
public:
    Engine(RenderWindow& window, bool flag);
    void start();
};

