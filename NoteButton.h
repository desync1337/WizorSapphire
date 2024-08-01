#pragma once


#include <fstream>
#include <iostream>

#include "Engine.h"

class Button
{

public:

	const char* name;
    
    std::string text;
    sf::Font font;
    sf::Text label;

    float roundness;

	sf::RectangleShape labelcircle;
	sf::CircleShape charcircle;

    sf::RectangleShape rect;
    sf::RectangleShape rect_vert;
    sf::RectangleShape rect_horiz;

    sf::CircleShape ULcircle;
    sf::CircleShape URcircle;
    sf::CircleShape DLcircle;
    sf::CircleShape DRcircle;

    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Color color;

	int i;
	bool isnote;
	bool typingnow;
	bool lowercase = true;
	bool charcirclevisible = true;
	float ftime = 0;
	sf::Clock clock;

	bool cancelwipe;


	sf::Vector2f interpolatevector(sf::Vector2f from, sf::Vector2f to,float fac)
	{
		float numx = (to.x - from.x) * fac;
		float numy = (to.y - from.y) * fac;

		return sf::Vector2f(from.x + numx, from.y + numy);

	}

	void endNote()
	{
		
		std::ofstream out("Categories/fuckyou.txt");

		out << text;
		out.close();

		std::cout << "saved as fuckyou.txt" << "\n";

		text = "";
		label.setCharacterSize(25);
		typingnow = false;
		size = sf::Vector2f(250.0f, 200.0f);
		label.setString(L"Saved!");
		charcirclevisible = false;

	}

	void CancelNote()
	{
		if (cancelwipe)	{ text = ""; } // delete whole text if cancelwipe == true
		label.setCharacterSize(25);
		typingnow = false;
		size = sf::Vector2f(250.0f, 200.0f); // yeah well buttons dont remember their original size so idk
		label.setString(L"...");			// i dont think this is a massive problem because its only needed on 'isnote' buttons
		charcirclevisible = false;
	}

	void StartNote()
	{

		typingnow = true;
		size = sf::Vector2f(700.0f, 580.0f);
		label.setString("");
		label.setCharacterSize(22);

	}

	void timer(float x)
	{
		if (ftime < x)
		{
			std::cout << clock.getElapsedTime().asSeconds() << "\n";
			ftime = clock.getElapsedTime().asSeconds();
		}
		else
		{
			updatecharcircle();
			ftime = 0;
			clock.restart();
		}
	}

	void updatecharcircle()
	{
		if (charcirclevisible)
			charcirclevisible = false;
		else
			charcirclevisible = true;
	}

	void Input(sf::Event ev)
	{
		
		if (typingnow) //- if were typing a new note
		{
			charcirclevisible = true;
			clock.restart();

			if (ev.key.code >= sf::Keyboard::A && ev.key.code <= sf::Keyboard::Z)
			{
				if (lowercase)
					text += static_cast<char>('a' + (ev.key.code - sf::Keyboard::A));
				else
					text += static_cast<char>('A' + (ev.key.code - sf::Keyboard::A));
			}

			if (ev.key.shift) // everything with shift pressed
			{

				if (ev.key.code == sf::Keyboard::Enter)
				{
					endNote();
				}


				if (ev.key.code >= 27 && ev.key.code <= 30) // symbols!! :3	(!@#$)							  <- this shit cause empty symbols
				{
					text += static_cast<char>('!' + (ev.key.code - sf::Keyboard::Num0 - 1));
					return;
				}
				if (ev.key.code == sf::Keyboard::Slash) //its stupid to add them one by one ,but cant help it!!! 
				{
					text += "?";
					return;
				}

				if (ev.key.code == 56)
				{
					text += "_";
					return;
				}

				if (ev.key.code == 26)
				{
					text += ")";
					return;
				}
				if (ev.key.code == 35)
				{
					text += "(";
					return;
				}

				if (ev.key.code == 48)
				{
					text += ":";
					return;
				}
			}


			if (ev.key.code == sf::Keyboard::Escape) //cancel note
			{
				CancelNote();

				return;
			}

			if (ev.key.code == sf::Keyboard::Backspace && text.size() > 0) // deleting chars
			{
				if (ev.key.control) { text = ""; return; } // If you hold ctrl whole text will be discombombulated
				text.pop_back();
				return;
			}

			if (ev.key.code == sf::Keyboard::Space) //space
			{
				text += " ";
			}

			if (ev.key.code == sf::Keyboard::Enter) // next row
			{
				text += "\n";
			}

			if (ev.key.code == -1) // Caps lock shit										// So APPARENTLY caps lock is not a thing in sfml							(maybe im retarded and there is a better way of doing this string shit but whatever fuck you im learning)
			{																				// 
				if (lowercase == true) { lowercase = false; }			// It has id -1 so its treated as unknown key
				else { lowercase = true; }			// 
				// SO IN MY PROGRAM EVERY UNKNOWN KEY WILL TRIGGER CAPS LOCK BECAUSE FUCK YOU!
			}

			if (ev.key.code == 50) //this is very stupid!!!
			{
				text += ".";

			}

			if (ev.key.code == 56)
			{
				text += "-";
			}



			if (ev.key.code >= 26 && ev.key.code <= 35) // numbers!! :3
			{
				text += static_cast<char>('0' + (ev.key.code - sf::Keyboard::Num0));
			}

			//std::cout << text<<"\n";
			std::cout << ev.key.code << "\n";


		}

	}

	void updateRectangles()		//move the visual part of the button according to the rect.
	{
		

		if (typingnow) 
		{
			label.setString(text);
			timer(0.5f);
		}

		if (label.findCharacterPos(text.size()).x > 740 && typingnow)
		{
			text += "\n";
		}

		//std::cout << label.findCharacterPos(text.size()).x << " " << label.findCharacterPos(text.size()).y << "\n";
		
		rect.setSize(interpolatevector(rect.getSize(), size, 0.25)); 

		charcircle.setPosition(interpolatevector(charcircle.getPosition(), label.findCharacterPos(text.size()), 0.25));
		charcircle.setPosition(charcircle.getPosition().x + 2.5, charcircle.getPosition().y + 3);
		//rect.setSize(size); std::cout << "setSize(" << size.x << " " << size.y << ");" << "\n";

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

	void init() // first setup when "born" <3
    {
		clock.restart();
		rect.setPosition(pos);
		rect.setSize(size); //std::cout << "setSize(" << size.x << " " << size.y << ");" << "\n";
		rect.setFillColor(sf::Color::Red);

		font.loadFromFile("Oxygen-Regular.ttf");

		label.setPosition(sf::Vector2f(rect.getPosition().x + roundness * 1, rect.getPosition().y + roundness * 0.3));

		label.setFont(font);
		label.setString(L"...");
		//label.setStyle(sf::Text::Bold);
		label.setCharacterSize(25);
		label.setFillColor(sf::Color(99, 99, 99, 255));
		//label.setFillColor(sf::Color::White);
		




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
		

		charcircle.setPosition(label.findCharacterPos(text.size()));
		charcircle.setRadius(3);
		charcircle.setFillColor(sf::Color(99, 99, 99, 255));

    }
};

