#include "Engine.h"


using namespace sf;

int main() 
{
	// window setup
	//init engine

	Engine engine;

	// loop
	while(engine.getWindowIsOpen()) 
	{
		// UPDATE
		engine.update();
		
		// RENDER
		engine.render();
	}

	return 0;

}