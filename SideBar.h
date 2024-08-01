#pragma once
#include "Engine.h"

class SideBar
{
public:
	
	sf::Sprite icon;

	sf::RectangleShape rect;																													 // тупая сука уйди из моей головы
																																				 
	sf::Vector2f pos;																															 
	sf::Vector2f size;

	sf::Font font;

	sf::Text settingslabel;
	sf::Text aboutlabel;
	
	void checklabelclick()
	{



	}

	void init()
	{
		
		pos = sf::Vector2f(-100.0f, 0.0f);
		size = sf::Vector2f(150.0f, 600.0f);

		rect.setPosition(sf::Vector2f(-100.0f, 0.0f));
		rect.setSize(sf::Vector2f(150.0f, 600.0f));
		rect.setFillColor(sf::Color(240, 240, 240, 255));
		rect.setOutlineColor(sf::Color(200, 200, 200, 255));
		rect.setOutlineThickness(2.0f);

		font.loadFromFile("Industry.ttf");

		settingslabel.setPosition(rect.getPoint(1));
		
		settingslabel.setFont(font);
		settingslabel.setString(L"Vently");
		settingslabel.setCharacterSize(17);
		settingslabel.setFillColor(sf::Color(99, 99, 99, 255));
	}
};

