#pragma once

#include "Engine.h"


class Panel 
{
public:
	
	sf::Vector2f initpos;
	sf::Vector2f initsize;

	sf::Vector2f pos;
	sf::Vector2f size;
	
	sf::RectangleShape rect;

	
	//bool isopen;
	//


	// Functions
	virtual void init();
	
	virtual void updateRects();

	//virtual void Input();

	virtual void Draw();
	
	// destructor
	virtual ~Panel() = default;
	

};

