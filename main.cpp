#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>
#include "spaceShip.h"
#include "bullet.h"
#include "asteroid_B.h"
#include "asteroid_M.h"
#include "asteroid_S.h"
#define random(a, b) (rand()%(b - a + 1) + a)

using namespace sf;
using namespace std;

bool isPlaying = false;
bool isWon = false;
bool isMenu = true;
float level = 1;
int playerLives = 2;
int playerPoints = 0;
Text playPointsT;
Text playLivesT;
Text levelsT;
Font font;
RenderWindow window;
SoundBuffer bufferShoot;
Sound soundShoot;
SoundBuffer bufferExplode;
Sound soundExplode;
SoundBuffer bufferShipExplode;
Sound soundShipExplode;
SoundBuffer bufferLevel;
Sound soundLevel;
Texture backTex;
Sprite backGround;

const float BUCKET_WIDTH = 100;
const float BUCKET_HEIGHT = 100;
const int COLUMNS = 16;
const int ROWS = 9;
vector<gameObject*> grid[COLUMNS][ROWS];
vector<gameObject*> buckets[5];

void update_state(float dt);
void render_frame();
void render_menu();
void addGameObject(gameObject* obj);
void asteroids_creator();
Vector2i getBucket(Vector2f pos);
void bucket_add(Vector2i b, gameObject* obj);
void bucket_remove(Vector2i b, gameObject* obj);
void detect_collisions(gameObject* obj, Vector2i b);

int main()
{
	window.create(VideoMode(1600, 900), "Yaowen's Asteroids!");
	
	Clock clock;

	font.loadFromFile("arial.ttf");
	bufferShoot.loadFromFile("shoot.wav");
	soundShoot.setBuffer(bufferShoot);
	bufferExplode.loadFromFile("explode.wav");
	soundExplode.setBuffer(bufferExplode);
	bufferShipExplode.loadFromFile("shipExplode.wav");
	soundShipExplode.setBuffer(bufferShipExplode);
	bufferLevel.loadFromFile("newlevel.wav");
	soundLevel.setBuffer(bufferLevel);
	backTex.loadFromFile("bimage.jpg");
	backGround.setTexture(backTex);
	spaceShip theShip;
	addGameObject(&theShip);
	asteroids_creator();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				break;
			}
			if (!isPlaying && isMenu && Keyboard::isKeyPressed(Keyboard::Space))
			{
				isPlaying = true;
				isMenu = false;
				playerLives = 2;
				playerPoints = 0;
				level = 1;
				for (int i = 1; i < 5; ++i)
				{
					for (gameObject* obj : buckets[i])
					{
						obj->killObject();
					}
				}
				buckets[1].clear();
				buckets[2].clear();
				buckets[3].clear();
				buckets[4].clear();
				asteroids_creator();
			}
			if (!isPlaying && !isWon && Keyboard::isKeyPressed(Keyboard::R))
			{
				isMenu = true;
			}
			if (!isPlaying && isWon && Keyboard::isKeyPressed(Keyboard::Space))
			{
				isPlaying = true;
				isWon = false;
				level++;
				for (gameObject* obj : buckets[1])
				{
					obj->killObject();
				}
				buckets[1].clear();
				asteroids_creator();
			}
		}

		if (isPlaying)
		{
			float dt = clock.restart().asSeconds();

			if (buckets[2].size() == 0 && buckets[3].size() == 0 && buckets[4].size() == 0)
			{
				isWon = true;
				isPlaying = false;
				soundLevel.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Space) && soundShoot.getStatus() != Sound::Playing)
			{
				soundShoot.play();
				if (buckets[1].size() == 5)
				{
					buckets[1].erase(buckets[1].begin());
				}
				bullet* b = new bullet(theShip.getPosition(), theShip.getVelocity(), theShip.getRotation());
				addGameObject(b);
			}

			for (int i = 0; i < 5; ++i)
			{
				for (unsigned j = 0; j < buckets[i].size();)
				{
					gameObject* obj = buckets[i][j];
					if (obj->isDead() && obj->getRenderBucket() == 2)
					{
						soundExplode.play();
						playerPoints += 100;
						asteroid_M* a1 = new asteroid_M(obj->getPosition(), { (float)random(-100, 100), (float)random(-100, 100) }, level);
						asteroid_M* a2 = new asteroid_M(obj->getPosition(), { (float)random(-100, 100), (float)random(-100, 100) }, level);
						buckets[i].erase(buckets[i].begin() + j);
						obj->killObject();
						buckets[a1->getRenderBucket()].push_back(a1);
						buckets[a2->getRenderBucket()].push_back(a2);
						continue;
					}
					if (obj->isDead() && obj->getRenderBucket() == 3)
					{
						soundExplode.play();
						playerPoints += 100;
						asteroid_S* a1 = new asteroid_S(obj->getPosition(), { (float)random(-100, 100), (float)random(-100, 100) }, level);
						asteroid_S* a2 = new asteroid_S(obj->getPosition(), { (float)random(-100, 100), (float)random(-100, 100) }, level);
						buckets[i].erase(buckets[i].begin() + j);
						obj->killObject();
						buckets[a1->getRenderBucket()].push_back(a1);
						buckets[a2->getRenderBucket()].push_back(a2);
						continue;
					}
					if (obj->isDead() && obj->getRenderBucket() == 4)
					{
						soundExplode.play();
						playerPoints += 100;
						buckets[i].erase(buckets[i].begin() + j);
						obj->killObject();
						continue;
					}
					if (obj->isDead() && obj->getRenderBucket() == 0 && playerLives > 0)
					{
						soundShipExplode.play();
						--playerLives;
						obj->reset();
						continue;
					}
					if (obj->isDead() && obj->getRenderBucket() == 0 && playerLives == 0)
					{
						soundShipExplode.play();
						theShip.reset();
						isPlaying = false;
						break;
					}
					if (obj->isDead() && obj->getRenderBucket() == 1)
					{
						buckets[i].erase(buckets[i].begin() + j);
						obj->killObject();
						continue;
					}
					++j;
				}
			}
			update_state(dt);
			render_frame();
		}
		else if (!isPlaying && !isMenu)
		{
			render_frame();
			continue;
		}

		if (isMenu)
		{
			render_menu();
		}
		window.display();
	}

	return 0;
}

void addGameObject(gameObject* obj)
{
	int i = obj->getRenderBucket();
	buckets[i].push_back(obj);
}

void asteroids_creator()
{
	srand((unsigned)time(NULL));
	
	for (int i = 0; i < 3; ++i)
	{
		asteroid_B* a = new asteroid_B({(float)random(30, 700) - i * 10, (float)random(30, 870) - i * 10}, { (float)random(-100, 10), (float)random(-100, 100) }, level);
		addGameObject(a);
	}

	for (int i = 0; i < 2; ++i)
	{
		asteroid_B* a = new asteroid_B({ (float)random(950, 1570) + i * 10, (float)random(30, 870) + i * 10}, { (float)random(-10, 100), (float)random(-100, 100) }, level);
		addGameObject(a);
	}
}

Vector2i getBucket(Vector2f pos)
{
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0)
	{
		col = 0;
	}
	else if (col >= COLUMNS)
	{
		col = COLUMNS - 1;
	}

	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0)
	{
		row = 0;
	}
	else if (row >= ROWS)
	{
		row = ROWS - 1;
	}
	return Vector2i(col, row);
}

void bucket_add(Vector2i b, gameObject* obj)
{
	vector<gameObject*> & v = grid[b.x][b.y];

	v.push_back(obj);
}

void bucket_remove(Vector2i b, gameObject* obj)
{
	vector<gameObject*> & v = grid[b.x][b.y];

	for (unsigned i = 0; i < v.size(); ++i)
	{
		if (v[i] == obj)
		{
			v.erase(v.begin() + i);
			break;
		}
	}
}

void detect_collisions(gameObject* obj, Vector2i b)
{
	int left = max(b.x - 1, 0);
	int right = min(b.x + 1, COLUMNS - 1);
	int top = max(b.y - 1, 0);
	int bot = min(b.y + 1, ROWS - 1);

	for (int bx = left; bx <= right; ++bx)
	{
		for (int by = top; by <= bot; ++by)
		{
			vector<gameObject*> & v = grid[bx][by];
			for (gameObject* o : v)
			{
				if (o != obj)
				{
					obj->checkCollisionWith(o);
				}
			}
		}
	}
}

void update_state(float dt)
{
	for (int i = 0; i < 5; ++i)
	{
		for (gameObject* obj : buckets[i])
		{
			Vector2i curBucket = getBucket(obj->getCenter());
			obj->update(dt);
			Vector2i newBucket = getBucket(obj->getCenter());
			if (curBucket != newBucket)
			{
				bucket_remove(curBucket, obj);
				bucket_add(newBucket, obj);
			}
			detect_collisions(obj, newBucket);
		}
	}
}

void render_menu()
{
	window.clear();

	window.draw(backGround);

	if (!isPlaying && isMenu)
	{
		Text menuText;
		Text startText;
		Text exitText;
		menuText.setFont(font);
		menuText.setString("Asteroids");
		menuText.setCharacterSize(200);
		menuText.setPosition({ 420, 150 });
		window.draw(menuText);
		startText.setFont(font);
		startText.setString("Press Space to start");
		startText.setCharacterSize(60);
		startText.setPosition({ 590, 600 });
		window.draw(startText);
		exitText.setFont(font);
		exitText.setString("Press ESC to Exit");
		exitText.setCharacterSize(60);
		exitText.setPosition({ 590, 700 });
		window.draw(exitText);
	}
}


void render_frame()
{
	window.clear();

	window.draw(backGround);

	if (!isPlaying && !isWon)
	{
		Text loseText;
		Text restartText;
		loseText.setFont(font);
		loseText.setString("Your Points: " + to_string(playerPoints));
		loseText.setCharacterSize(100);
		loseText.setPosition({ 460, 180 });
		window.draw(loseText);
		restartText.setFont(font);
		restartText.setString("Press R to restart");
		restartText.setCharacterSize(60);
		restartText.setPosition({ 600, 600 });
		window.draw(restartText);
	}

	if (!isPlaying && isWon)
	{
		Text winText;
		Text levelText;
		winText.setFont(font);
		winText.setString("Yeah! You win!");
		winText.setCharacterSize(100);
		winText.setPosition({ 490, 180 });
		window.draw(winText);
		levelText.setFont(font);
		levelText.setString("Press Space to next level");
		levelText.setCharacterSize(60);
		levelText.setPosition({ 475, 600 });
		window.draw(levelText);
	}

	if (isPlaying)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (gameObject* obj : buckets[i])
			{
				obj->draw();
			}
		}

		playPointsT.setFont(font);
		playPointsT.setString("Points: " + to_string(playerPoints));
		playPointsT.setCharacterSize(30);
		playPointsT.setPosition({ 30, 120 });
		window.draw(playPointsT);
		playLivesT.setFont(font);
		playLivesT.setString("Lives: " + to_string(playerLives));
		playLivesT.setCharacterSize(30);
		playLivesT.setPosition({ 30, 150 });
		window.draw(playLivesT);
		levelsT.setFont(font);
		levelsT.setString("Level: " + to_string((int)level));
		levelsT.setCharacterSize(50);
		levelsT.setPosition({ 30, 30 });
		window.draw(levelsT);
	}
}