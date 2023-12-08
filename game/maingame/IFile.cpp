#include "IFile.h"


IFile::IFile()
{

}

void IFile::save(Map map, Player player, vector<Opponent> o, Floor floorNumber, int heartCount, vector<sf::Vector2f> heartPos)
{
    ofstream fout(path, ios_base::trunc);
    if (!fout.is_open())
    {
        std::cout << "Ошибка открытия файла" << std::endl;
    }
    fout << "[Map]\n";
    vector<vector<int>> m = map.getMap();
    fout << "m.size()=" << m.size() << "\n";
    fout << "m[0].size()=" << m[0].size() << "\n";

    fout <<"map.getKey()=" <<map.getKey() << "\n";
    fout << "map.getKeyPos().x="<<map.getKeyPos().x << "\n";
    fout<< "map.getKeyPos().y="<<map.getKeyPos().y << "\n";
    fout << "map.getStartX()="<<map.getStartX() << "\n";
    fout<< "map.getStartY()="<<map.getStartY() << "\n";
    fout << "map.getEndX()="<<map.getEndX() << "\n";
    fout<< "map.getEndY()="<<map.getEndY() << "\n";
    fout << "\n";
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            fout << "(" << i << ")(" << j << ")=" << m[i][j] << "\n";
        }
    }
    fout << "[Player]\n";
    fout << "player.getXPos()="<<player.getXPos() << "\n";
    fout<< "player.getYPos()="<<player.getYPos() << "\n";
    fout << "player.getLives()="<<player.getLives() << "\n";
    fout << "player.getDir()="<< static_cast<int>(player.getDir()) << "\n";
    fout << "\n";

    fout << "[Vector]\n";
    fout <<"o.size()="<< o.size() << "\n";
    fout << "\n";
    for (int i = 0; i < o.size(); i++)
    {
        fout << "[Opponent"<< i <<"]\n";
        fout << "getDir()=" << static_cast<int>(o[i].getDir()) << "\n";
        fout << "getXPos()=" << o[i].getXPos() << "\n";
        fout << "getYPos()=" << o[i].getYPos() << "\n";
        fout << "itsDetected()=" << o[i].itsDetected() << "\n";
        fout << "\n";
    }

    fout << "[Game]\n";
    fout <<"floorNumber=" << static_cast<int>(floorNumber) << "\n";
    fout << "heartCount=" << heartCount << "\n";
    for (int i = 0; i < heartCount; i++)
    {
        fout << "[Heart"<< i <<"]\n";
        fout << "X" <<"="<< heartPos[i].x << "\n";
        fout << "Y" <<"="<< heartPos[i].y << "\n";
    }
    fout.close();
}

void IFile::load(Map& map, Player& player, vector<Opponent>& o, Floor& floorNumber, int &heartCount, vector<sf::Vector2f>& heartPos)
{
    config.clear();
    std::ifstream fin(path);
    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла" << std::endl;
    }
    std::string line;
    std::string currentSection;
    while (std::getline(fin, line))
    {
        //Пропускаем пустые строки
        if (line.empty())
            continue;

        if (line[0] == '[' && line[line.size() - 1] == ']')
        {
            //Найдена новая секция
            currentSection = line.substr(1, line.size() - 2);
            continue;
        }

        std::istringstream iss(line);
        std::string key;
        std::string value;

        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            config[currentSection][key] = value;
        }
    }

    fin.close();

    vector<vector<int>> m;
    m.resize((stoi(config["Map"]["m.size()"])));
    for (int i = 0; i < m.size(); i++)
    {
        m[i].resize((stoi(config["Map"]["m[0].size()"])));
    }
    floorNumber = static_cast<Floor>((stoi(config["Game"]["floorNumber"])));
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            string str = "(" + to_string(i) + ")(" + to_string(j) + ")";
            m[i][j] = (stoi(config["Map"][str]));
        }
    }
    map.setEndX((stoi(config["Map"]["map.getEndX()"])));
    map.setEndY((stoi(config["Map"]["map.getEndY()"])));
    map.setKey((stoi(config["Map"]["map.getKey()"])));
    map.setKeyPosX(stoi(config["Map"]["map.getKeyPos().x"]));
    map.setKeyPosY(stoi(config["Map"]["map.getKeyPos().y"]));
    map.setStartX(stoi(config["Map"]["map.getStartX()"]));
    map.setStartY(stoi(config["Map"]["map.getStartY()"]));

    heartCount = stoi(config["Game"]["heartCount"]);
    heartPos.resize(heartCount);
    for (int i = 0; i < heartCount; i++)
    {
        string str = "Heart" + to_string(i);
        heartPos[i].x = stof(config[str]["X"]);
        heartPos[i].y = stof(config[str]["Y"]);
    }
    player.setDir(static_cast<direction>(stoi(config["Player"]["player.getDir()"])));
    player.setLives((stoi(config["Player"]["player.getLives()"])));
    player.setXPos((stof(config["Player"]["player.getXPos()"])));
    player.setYPos((stof(config["Player"]["player.getYPos()"])));
    int opponentSize = stoi(config["Vector"]["o.size()"]);
    for (int i = 0; i < opponentSize; i++)
    {
        string str = "Opponent" + to_string(i);
        o[i].setDir(static_cast<direction>(stoi(config[str]["getDir()"])));
        o[i].setXPos(stof(config[str]["getXPos()"]));
        o[i].setYPos(stof(config[str]["getYPos()"]));
        o[i].setDetection(stoi(config[str]["itsDetected()"]));
    }
    map.setMap(m);
}
