#include "map.h"

Map::Map()
{
	width = sf::VideoMode::getDesktopMode().width*3;
	height = sf::VideoMode::getDesktopMode().height*2;
	cols =  width / 96;
	rows =  height / 96;

	imgWall.loadFromFile("img/b1.png");
	textureWall.loadFromImage(imgWall);
	spriteWall.setTexture(textureWall);

	imgFloor.loadFromFile("img/b0.png");
	textureFloor.loadFromImage(imgFloor);
	spriteFloor.setTexture(textureFloor);

	keyImg.loadFromFile("img/key.png");
	keyTexture.loadFromImage(keyImg);
	keySprite.setTexture(keyTexture);

	liftImg.loadFromFile("img/lift.png");
	liftTexture.loadFromImage(liftImg);
	liftSprite.setTexture(liftTexture);
	liftSprite.setPosition(sf::Vector2f(96 * (cols - 1), 96 * (rows - 2)));
}
Map::~Map()
{

}

void Map::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)
			{
				spriteWall.setPosition(j * 96, i * 96);
				window.draw(spriteWall);
			}
			else
			{
				spriteFloor.setPosition(j * 96, i * 96);
				window.draw(spriteFloor);
			}
		}
	}
	window.draw(liftSprite);
	if (key)
	{
		window.draw(keySprite);
	}

}

bool Map::itsWall(float height, float width)
{
	if (height < sf::VideoMode::getDesktopMode().height * 3 && width < sf::VideoMode::getDesktopMode().width * 3)
	{
		return map[int(height / 96)][int(width / 96)] == 0;
	}
}
;

void::Map::mazemake()
{
	end_x = cols - 2;
	end_y = rows - 2;
	key = true;
	prepare();
	int rep = 0;
	srand(time(NULL));
	int point = rand() % number;
	while (map[end_y][end_x] != 1) {
		point = rand() % number;

		switch (rand() % 4)
		{
		case 0: if (testXY(points_y[point] - 1, points_x[point]) && map[points_y[point] - 2][points_x[point]] != 1) {
			map[points_y[point] - 1][points_x[point]] = 1;
			if (testXY(points_y[point] - 2, points_x[point])) {
				map[points_y[point] - 2][points_x[point]] = 1;
				points_x.push_back(points_x[point]);
				points_y.push_back(points_y[point] - 2);
				number++;
			}
		}	break;
		case 1: if (testXY(points_y[point], points_x[point] + 1) && map[points_y[point]][points_x[point] + 2] != 1) 
		{
			map[points_y[point]][points_x[point] + 1] = 1;
			if (testXY(points_y[point], points_x[point] + 2)) 
			{
				map[points_y[point]][points_x[point] + 2] = 1;
				points_x.push_back(points_x[point] + 2);
				points_y.push_back(points_y[point]);
				number++;
			}
			break;
		}
		case 2: 
			if (testXY(points_y[point] + 1, points_x[point]) && map[points_y[point] + 2][points_x[point]] != 1)
			{
			map[points_y[point] + 1][points_x[point]] = 1;
			if (testXY(points_y[point] + 2, points_x[point])) 
			{
				map[points_y[point] + 2][points_x[point]] = 1;
				points_x.push_back(points_x[point]);
				points_y.push_back(points_y[point] + 2);
				number++;
			}
			}	
			break;
		case 3: 
			if (testXY(points_y[point], points_x[point] - 1) && map[points_y[point]][points_x[point] - 2] != 1) 
			{
			map[points_y[point]][points_x[point] - 1] = 1;
			if (testXY(points_y[point], points_x[point] - 2)) 
{
				map[points_y[point]][points_x[point] - 2] = 1;
				points_x.push_back(points_x[point] - 2);
				points_y.push_back(points_y[point]);
				number++;
			}
			}	
			break;
		default:
			break;
		}
		rep++;
		testforDEADEND(point);
	}
	setKeyPos();
}

sf::Vector2f Map::getPos()
{
	int i, j;
	i = rand() % rows;
	j = rand() % cols;
	while (map[i][j]==0 || i<5 ||j<5 || i > rows - 5 || j > cols - 5)
	{
		i = rand() % rows;
		j = rand() % cols;
	}
	return sf::Vector2f((((float)j)*96.0)+1.0, (((float)i)*96.0)+1.0);
}

void Map::prepare()
{
	map.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		map[i].resize(cols);
	}
	points_x.clear();
	points_y.clear();

	for (int i = 0; i < rows; i++) 
	{
		for (int i1 = 0; i1 < cols; i1++) 
		{ 
			map[i][i1] = 0;
		}
	}
	number = 1;
	startX = 2;
	startY = 2;
	map[startY][startX] = 1;
	points_x.push_back(startX);
	points_y.push_back(startY);
}
bool Map::testXY(int y, int x)
{
		if (x == end_x && y == end_y) { return true; }
		else if (x<1 || y<1 || x>end_x || y>end_y || map[y][x] == 1) { return false; }
		else if (map[y - 1][x - 1] + map[y - 1][x] + map[y][x - 1] == 3) { return false; }
		else if (map[y - 1][x] + map[y - 1][x + 1] + map[y][x + 1] == 3) { return false; }
		else if (map[y + 1][x - 1] + map[y + 1][x] + map[y][x - 1] == 3) { return false; }
		else if (map[y + 1][x] + map[y + 1][x + 1] + map[y][x + 1] == 3) { return false; }
		else { return true; }
}
void Map::testforDEADEND(int num)
{
	if (!testXY(points_y[num] - 2, points_x[num])) {
		if (!testXY(points_y[num] + 2, points_x[num])) {
			if (!testXY(points_y[num], points_x[num] - 2)) {
				if (!testXY(points_y[num], points_x[num] + 2)) {
					near_finish(num);
					if (number > 1) {
						auto iter = points_x.cbegin();
						points_x.erase(iter + num);
						auto iter2 = points_y.cbegin();
						points_y.erase(iter2 + num);
						number--;
					}
				}
			}
		}
	}
}
void Map::near_finish(int num)
{
	if (abs(points_y[num] - end_y) <= 2 && abs(points_x[num] - end_x) <= 2)
	{
		for (int i = end_y - 1; i <= end_y; i++)
		{
			for (int i1 = end_x - 1; i1 <= end_x; i1++) 
			{
				map[i][i1] = 1;
			}
		}
	}
}
void Map::setKeyPos()
{
	int i, j;
	i = rand() % rows;
	j = rand() % cols;
	while (map[i][j] == 0 || i < 5 || j < 5 || i > rows- 5 || j > cols- 5)
	{
		i = rand() % rows;
		j = rand() % cols;
	}
	keyPos.x = j;
	keyPos.y = i;
	setKeySpritePos();
};

bool Map::lee(int ax, int ay, int bx, int by, stack<int>& px, stack<int>& py)  
{
	while (!py.empty()) { py.pop(); }
	while (!px.empty()) { px.pop(); }
	int dx[4] = { 1, 0, -1, 0 };  
	int dy[4] = { 0, 1, 0, -1 };   
	int d, x, y, k;
	bool stop;
	vector<vector<int>> grid(rows, vector<int>(cols));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			grid[i][j] = -1;
		}
	}

	if (map[ay][ax] == 0 || map[by][bx] == 0) return false; 

	d = 0;
	grid[ay][ax] = 0;            
	do {
		stop = true;             
		for (y = 0; y < rows; ++y)
			for (x = 0; x < cols; ++x)
				if (grid[y][x] == d)                 
				{
					for (k = 0; k < 4; ++k)            
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < rows && ix >= 0 && ix < cols && map[iy][ix] == 1)
						{
							stop = false;           
							grid[iy][ix] = d + 1;    
						}
					}
				}
		d++;
	} while (!stop && grid[by][bx] == -1);

	int len = grid[by][bx];       
	x = bx;
	y = by;
	d = len;
	while (d > 0)
	{
		px.push(x);
		py.push(y);               
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < rows && ix >= 0 && ix < cols && grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];    
				break;
			}
		}
	}
	return true;
}

void Map::changeFloor(string floor, string wall)
{
	imgWall.loadFromFile(wall);
	textureWall.loadFromImage(imgWall);
	spriteWall.setTexture(textureWall);
	imgFloor.loadFromFile(floor);
	textureFloor.loadFromImage(imgFloor);
	spriteFloor.setTexture(textureFloor);
}
 


