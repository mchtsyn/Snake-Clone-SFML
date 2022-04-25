#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <string>
#include "fruit.h"
#include "reward.h"

using namespace sf;
using namespace std;
struct mySnake {
	//position, size, direction;
	int dir;
	int x, y;
	float speed;

	void x_and_y(int count)
	{
		for (int i = count;i > 0;--i)
		{
			s[i].x = s[i - 1].x; //pos.x gibi
			s[i].y = s[i - 1].y; //pos.y gibi
		}
		//direction control
		if (dir == 0)
			s[0].y -= 1 * speed;
		else if (dir == 1)
			s[0].x -= 1 * speed;
		else if (dir == 2)
			s[0].y += 1 * speed;
		else if (dir == 3)
			s[0].x += 1 * speed;

	}
	/*  dir = 0 -> W
		dir = 1 -> A
		dir = 2 -> S
		dir = 3 -> D
	*/
	void updateSnake()
	{
		//key input
		if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))&& dir != 2)
			dir = 0;
		else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) && dir != 3)
			dir = 1;
		else if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))&& dir != 0)
			dir = 2;
		else if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))&& dir != 1)
			dir = 3;
	}
}s[100];


void createWall(Sprite& sprite, RenderWindow& window) {
	//rows
	for (int i = 0;i < 40;i++)
	{
		sprite.setPosition(i * 20, 0);
		window.draw(sprite);
	}
	for (int i = 0;i < 40;i++)
	{
		sprite.setPosition(i * 20, 29*20);
		window.draw(sprite);
	}
	//columns
	for (int i = 0;i < 30;i++)
	{
		sprite.setPosition(0, i * 20);
		window.draw(sprite);
	}
	for (int i = 0;i < 30;i++)
	{
		sprite.setPosition(39*20, i * 20);
		window.draw(sprite);
	}
}

void showScore(int count, RenderWindow& window)
{
	Text score;
	Font font;
	if (!font.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\Roboto\\Roboto-Light.ttf"));
	score.setFont(font);
	score.setCharacterSize(24);
	score.setPosition((33), (28));
	score.setFillColor(Color(252, 255, 231));
	score.setString(to_string(count - 1));
	window.draw(score);
}
void showElapsedTime(int time,RenderWindow& window)
{
	Text elapsedTime;
	Font font;
	if (!font.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\Roboto\\Roboto-Light.ttf"));
	elapsedTime.setFont(font);
	elapsedTime.setCharacterSize(24);
	elapsedTime.setPosition((800-44-40), (600-55));
	elapsedTime.setFillColor(Color(252,255,231));
	if(time<10)
		elapsedTime.setString("00:0"+to_string(time));
	else if(time<60 && time >=10)
		elapsedTime.setString("00:" + to_string(time));
	else if (time >=60)
		elapsedTime.setString("0" + to_string(time/60)+":"+ to_string(time-60));
	window.draw(elapsedTime);
}

int main() {
	//reward fruit
	Texture rewardText;
	Sprite rewardSprite;
	if (!rewardText.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\gift.png"));
	rewardSprite.setTexture(rewardText);
	int snakeOnTheRewPoint = 0;
	giftFruit gift;
	gift.pos = Vector2f(0, 0);
	bool showGift = false;

	//eat sound effect
	SoundBuffer eat;
	if (!eat.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\bite.wav"));
	Sound eatEff;
	eatEff.setBuffer(eat);
	//death sound effect
	SoundBuffer death;
	if (!death.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\death.wav"));
	Sound deathEff;
	deathEff.setBuffer(death);

	//calculate elapsed time
	Clock elTime;
	int elTimer = 0;


	//Creating Window
	RenderWindow window(VideoMode(800, 600), "Snake");
	window.setFramerateLimit(15);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

	srand(time(0));

	//tick
	Clock clockTick;
	float timer = 0, delay = 0;

	// Textures
	Texture bodyTexture;
	Texture wall;
	if (!bodyTexture.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\snake_body.png"));
	Sprite sprite;
	sprite.setTexture(bodyTexture);
	int size_x = 20, size_y = 20;

	if (!wall.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\wall.png"));
	Sprite wall_s;
	wall_s.setTexture(wall);

	//snake 
	mySnake yilan;
	int count = 1;
	yilan.dir = 3; //initial direction
	yilan.speed = 1;
	Vector2f initPos = Vector2f((800 - 20 - 20) / (2 * 20), (600 - 20 - 20) / (2 * 20));
	s[0].x = (800-20-20)/(2*20); s[0].y = (600-20-20)/(2*20); //initial position

	//apple
	Elma fruit;
	fruit.pos = Vector2f(100, 100);
	fruit.initApple();

	//game 
	bool game = 1;

	//pause game
	int isSpacePressed = 0;
	int waitTime = 0;
	while (window.isOpen())
	{
		timer = clockTick.getElapsedTime().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

		}
		window.clear();

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			cout << "ALLAh  " << waitTime<< endl;
			if (isSpacePressed == 0)
			{
				waitTime = 20000;
				isSpacePressed = 1;
			}
			else if (isSpacePressed == 1)
			{
				waitTime = 0;
				isSpacePressed = 0;
			}
			game=0;
		}
		//calculate elapsed time
		elTimer = elTime.getElapsedTime().asSeconds();
		showElapsedTime(elTimer,window);
		showScore(count, window);
		//creating wall;
		createWall(wall_s, window);

		//randomPos for apple
		Vector2f appleRandomPos = Vector2f((rand() % 38 + 1)*20, (rand() % 28 + 1)*20);

		if (game) {

			//tick
			if (timer > delay)
			{
				yilan.x_and_y(count);
				clockTick.restart();

				//collision snake & apple
				if (s[0].x == fruit.pos.x / 20 && s[0].y == fruit.pos.y / 20)
				{
					fruit.checkCollision(appleRandomPos, count);
					eatEff.play();
				}
				//collision snake & wall
				if (s[0].x < 1 || s[0].x >38 || s[0].y < 1 || s[0].y>28)
				{
					deathEff.play();
					s[0].x = initPos.x;
					s[0].y = initPos.y;
					count = 1;
					Sleep(2000); // wait for 2secs.
					elTime.restart();

				}
				//collision snake & snake itself
				for (int i = 1;i < count;i++)
				{
					if (s[0].x == s[i].x && s[0].y == s[i].y)
					{
						deathEff.play();
						s[0].x = initPos.x;
						s[0].y = initPos.y;
						count = 1;
						Sleep(2000); // wait for 2secs.
						elTime.restart();
					}
				}
				//reward fruit
				if (s[0].x == 200/20 && s[0].y == 200/20) //200/20 is a position to count smth to get reward
				{
					snakeOnTheRewPoint++;
				}
				if (snakeOnTheRewPoint == 2)
				{
					showGift = true;
					cout << "earned" << endl;
					gift.earnedGift(appleRandomPos);
					snakeOnTheRewPoint = 0;
				}
				else if (snakeOnTheRewPoint < 2 && !showGift) gift.initGift();

				if ((s[0].x == gift.pos.x / 20 && s[0].y == gift.pos.y / 20)&&showGift)
				{
					gift.collisionGift(appleRandomPos, count);
					eatEff.play();
					snakeOnTheRewPoint = 0;
					showGift = false;
				}
			}
			

			//draw snake 
			for (int i = 0;i < count;i++)
			{
				sprite.setPosition(s[i].x * size_x, s[i].y * size_y);
				window.draw(sprite);
			}
			yilan.updateSnake();
			//draw apple
			fruit.drawApple(window);
			gift.drawGift(window);
		}
		

		window.display();
	}
}