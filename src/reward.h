#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class giftFruit {
	Texture text;
	Sprite sprite;
public:
	Vector2f pos;

	void initGift() {
		if (!text.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\gift.png"));
		sprite.setTexture(text);
		sprite.setColor(Color(0, 0, 0, 0));
	}

	void earnedGift(Vector2f randomm)
	{
		sprite.setColor(Color(255, 255,255, 255));
		pos = randomm;
		sprite.setPosition(pos);
	}

	void collisionGift(Vector2f randomm, int& counter)
	{
		pos = randomm;
		sprite.setPosition(pos);
		counter += 4;
	}
	void drawGift(RenderWindow& window)
	{
		window.draw(sprite);
	}
};