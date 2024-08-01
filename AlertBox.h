#pragma once

#include "Engine.h"
#include <iostream>


class AlertBox
{

public:

    std::string text;
    sf::Font font;
    sf::Text titlelabel;

    float roundness = 10;



	sf::RectangleShape graybg;

    sf::RectangleShape rect;
    sf::RectangleShape rect_vert;
    sf::RectangleShape rect_horiz;
	sf::RectangleShape rect_top;

	sf::RectangleShape okrect;
	sf::CircleShape Rcircle;
	sf::CircleShape Lcircle;

    sf::CircleShape ULcircle;
    sf::CircleShape URcircle;
    sf::CircleShape DLcircle;
    sf::CircleShape DRcircle;

    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Color color;
	sf::Color titlecolor;
	sf::Color recttopcolor;
	sf::Color graybgcolor;
	sf::Color buttoncolor;

	sf::Vector2f interpolatevector(sf::Vector2f from, sf::Vector2f to, float fac)
	{
		float numx = (to.x - from.x) * fac;
		float numy = (to.y - from.y) * fac;

		return sf::Vector2f(from.x + numx, from.y + numy);

	}

	void updateRectangles()
	{

		rect.setSize(interpolatevector(rect.getSize(), size, 0.25));

		ULcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(0)));

		URcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(1)));
		URcircle.setPosition(URcircle.getPosition().x - (roundness * 2), URcircle.getPosition().y);

		DRcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(2)));
		DRcircle.setPosition(DRcircle.getPosition().x - (roundness * 2), DRcircle.getPosition().y - (roundness * 2));

		DLcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(3)));
		DLcircle.setPosition(DLcircle.getPosition().x, DLcircle.getPosition().y - (roundness * 2));

		rect_horiz.setPosition(ULcircle.getPosition().x + roundness, ULcircle.getPosition().y);
		rect_horiz.setSize(sf::Vector2f(rect.getPoint(2).x - (roundness * 2), rect.getSize().y));

		rect_vert.setPosition(ULcircle.getPosition().x, ULcircle.getPosition().y + roundness);
		rect_vert.setSize(sf::Vector2f(rect.getPoint(2).x, rect.getSize().y - (roundness * 2)));
	}

	void init()
	{
		color = sf::Color(244, 244, 244, 255);
		titlecolor = sf::Color(99, 99, 99, 255);
		recttopcolor = sf::Color(111, 111, 111, 111);
		graybgcolor = sf::Color(1, 1, 1, 50);
		buttoncolor = sf::Color(129, 219, 255, 255);

		okrect.setFillColor(buttoncolor);
		okrect.setSize(sf::Vector2f(100.0f, 50.0f));
		okrect.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		okrect.setPosition(pos.x + (size.x / 2) - 50.0f , pos.y + size.y - 60.0f);

		Lcircle.setFillColor(buttoncolor);
		Lcircle.setRadius(25.0f);
		Lcircle.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		Lcircle.setPosition(okrect.getPosition().x - 25.0f, okrect.getPosition().y);

		Rcircle.setFillColor(buttoncolor);
		Rcircle.setRadius(25.0f);
		Rcircle.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		Rcircle.setPosition(okrect.getPosition().x + 75.0f, okrect.getPosition().y);

		rect.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		rect.setPosition(sf::Vector2f(400.0f, 300.0f ));
		rect.setSize(size); //std::cout << "setSize(" << size.x << " " << size.y << ");" << "\n";

		font.loadFromFile("Oxygen-Bold.ttf");

		titlelabel.setFont(font);
		titlelabel.setString(text);

		titlelabel.setCharacterSize(20);
		titlelabel.setFillColor(titlecolor);
		sf::FloatRect textRect = titlelabel.getLocalBounds();
		titlelabel.setOrigin(textRect.width / 2, textRect.height / 2);
		titlelabel.setPosition(rect.getPosition().x - 5.0f, rect.getPosition().y - (size.y / 2) + 25.0f);

		graybg.setSize(sf::Vector2f(800.0f, 600.0f));
		graybg.setFillColor(graybgcolor);

		rect_top.setSize(sf::Vector2f(size.x * 0.95, 3.0f));
		rect_top.setOrigin(sf::Vector2f(rect_top.getSize().x / 2, rect_top.getSize().y / 2));
		rect_top.setFillColor(recttopcolor);
		rect_top.setPosition(rect.getPosition().x, rect.getPosition().y - (size.y / 2) + 7.0f);
		

		ULcircle.setRadius(roundness);
		ULcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(0)));
		ULcircle.setFillColor(color);
		
	    URcircle.setRadius(roundness);
	    URcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(1)));
	    URcircle.setPosition(URcircle.getPosition().x - (roundness * 2), URcircle.getPosition().y);
	    URcircle.setFillColor(color);
	    
	    DRcircle.setRadius(roundness);
	    DRcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(2)));
	    DRcircle.setPosition(DRcircle.getPosition().x - (roundness * 2), DRcircle.getPosition().y - (roundness * 2));
	    DRcircle.setFillColor(color);
	    
	    DLcircle.setRadius(roundness);
	    DLcircle.setPosition(rect.getTransform().transformPoint(rect.getPoint(3)));
	    DLcircle.setPosition(DLcircle.getPosition().x, DLcircle.getPosition().y - (roundness * 2));
	    DLcircle.setFillColor(color);
	    
	    rect_horiz.setPosition(ULcircle.getPosition().x + roundness, ULcircle.getPosition().y);
	    rect_horiz.setSize(sf::Vector2f(rect.getPoint(2).x - (roundness * 2), rect.getSize().y));
	    rect_horiz.setFillColor(color);
	    
	    rect_vert.setPosition(ULcircle.getPosition().x, ULcircle.getPosition().y + roundness);
	    rect_vert.setSize(sf::Vector2f(rect.getPoint(2).x, rect.getSize().y - (roundness * 2)));
	    rect_vert.setFillColor(color);

	}

};

