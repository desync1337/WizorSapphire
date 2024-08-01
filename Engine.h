#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Panel.h"
#include "NoteButton.h"


/*

	Class that acts as the engine
	like a wrapper fuck off

	i have no fucking clue who calls engine function bul atleast it works

*/
class Engine
{

private:

	
	

	//Vars
	bool MouseInside;

	sf::Event ev;
	sf::VideoMode videoMode;

	


	//Private functions
	void initializeVariables();
	void initWindow();
	void initObjects();

public:

	//Theme colors 
	static sf::Color panelcolor;

	static sf::RenderWindow* window;

	// Constructors / Destructors
	Engine();
	virtual ~Engine();
																																				 // Four walls closing in with regret      //
	//Accessors																																	 // I can tell by your silence		       //
	const bool getWindowIsOpen() const;																											 // Give up just in time to regress	       //
																																				 // Confidence in you is low		       //
	//Functions																																	 // 								       //
	void ButtonEvents(int i);																													 // Feeling more misguided			       //
																																				 // On and on this isn't vital		       //
	void debug();																																 // What should I know?				       //
																																				 // Crawling through the bullshit recourse //
	void finterpolate(float *from, float to, float fac);																						 // It's better left untold				   //

	void UpdatePanels();
	static void DrawRect(sf::RectangleShape shape);
	void CreatePanel(sf::Vector2f pos,sf::Vector2f size, sf::Color color);
	
	void DrawSideBar();

	void CreateNoteButton(bool isnote,const char* name,sf::Vector2f pos,sf::Vector2f size, float radius);
	void DrawNoteButton();

	void pollEvents();
	bool MouseInsideCheck(sf::Vector2f pos, sf::Vector2f size);
	void update();
	void render();

};

