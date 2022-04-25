#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
class Elma {
	Sprite elma;
	Texture texture;
public:
	Vector2f pos;

	void initApple() {
		if (!texture.loadFromFile("C:\\Users\\Mücahit\\Desktop\\snake-png\\apple.png"));
		elma.setTexture(texture);
		elma.setPosition(pos);
	}

	void checkCollision( Vector2f randomm,int& counter)
	{
		pos = randomm;
		elma.setPosition(pos);
		counter++;
	}

	void drawApple(RenderWindow& window)
	{
		window.draw(elma);
	}
};