#include "Engine.h"
#include "FileList.h"

void FileList::init() 
{
	rect.setFillColor(Engine::panelcolor);
	std::cout << "FUCK YOU" << "\n";

	pos = initpos;
	size = initsize;

}

void FileList::updateRects()
{

	rect.setPosition(pos);
	rect.setSize(size);
	
}

void FileList::Draw()
{
	Engine::window->draw(rect);
	//Engine::DrawRect(rect);
}
