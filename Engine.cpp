#include <iostream>

#include "SideBar.h"
#include "NoteButton.h"
#include "FileList.h"

using namespace sf;
																 // В планах сделать мобильную версию но я не ебу как?
/*																 
																 							
Цель: Полный рефакторинг кода и максимальное продумывание программы

Причина: 500 строк абсолютно одинакового говна которое еще и запутывается и мешает продолжать разработку

Проблемы: 
	1-нет масок я не могу прятать один обьект в другом

Идея такая: вместо кнопок 'панели' которые раскрываются и показывают рабочий контент внутри
Реализация контента: определенный файл класса который содержит все говно внутри(лайаут логика переменные)

Когда панель инициализируется она будет прогружать именно тот контент который выбран при ее создании
Таким образом все панели хранятся в одном списке до них легко достучаться и манипулировать

Кнопку записок придется оставить отдельным обьектом потому что она слишком уникальна и я ебал рот ее 

Так же нужно добавить кучу переменных про тему (цвета формы кнопок и панелей) чтобы легко ими управлять 
и не переписывать 300 раз одно и тоже



Короче ебля: 
Другие классы нихуя не могут лезть в переменные engine

Значит что тут правит маскулинность и панели должны приказывать контенту и вызывать их функции(которые должны принимать одни и те же аргументы)

 
scenecore - frou,lungskull (24072024)
*/



//already existing shitt									
Button notebutton;															     	 
SideBar sidebar;

 // content
FileList c_filelist;

bool alerted = false;


Color Engine::panelcolor = sf::Color(199, 199, 199, 255);
//Color Engine::panelcolor = sf::Color(37, 26, 80, 255);
RenderWindow* Engine::window = nullptr;


void Engine::initializeVariables()
{
	//this->window = nullptr;
}

void Engine::initWindow()
{

	videoMode.height = 600;
	videoMode.width = 800;


	//this->videoMode.getDesktopMode; /  get the dimenstions of screen

	this->window = new RenderWindow(this->videoMode, ":3", Style::Titlebar | Style::Close);

	auto icon = Image{};

	icon.loadFromFile("vently.png");

	this->window->setIcon(icon.getSize().x,icon.getSize().y, icon.getPixelsPtr());
	this->window->setFramerateLimit(60);
}

void Engine::initObjects() // birth centre | this is where you can "create" objects
{
	sidebar.init();
	CreateNoteButton(true,"NoteCreator", Vector2f(60.0f, 10.0f), Vector2f(250.0f, 200.0f), 10.0f);
	CreatePanel(Vector2f(320.0f, 10.0f), Vector2f(100.0f, 100.0f), panelcolor);
	
	c_filelist.initsize = Vector2f(100.0f, 100.0f);
	c_filelist.initpos = Vector2f(320.0f, 10.0f);
	c_filelist.init();

}

//Constructors / Destructors

Engine::Engine()
{
	this->initializeVariables();
	this->initWindow();
	this->initObjects();
}

Engine::~Engine() // this prevents memory leaks!!
{
	delete this->window;
}

//Functions

const bool Engine::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Engine::ButtonEvents(int i)
{
	
	

}

void Engine::debug() // func 4 info printing
{
	//std::cout << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	//std::cout << MouseInsideCheck(filelists[0].pos.x, filelists[0].pos.y, filelists[0].size.x, filelists[0].size.y) << "\n";
}

void Engine::finterpolate(float *from, float to, float fac)
{
	float newnum = (to - *from) * fac;
	*from += newnum;
}

void Engine::UpdatePanels()
{
	
}

void Engine::DrawRect(RectangleShape shape)
{

	window->draw(shape);

}

void Engine::CreatePanel(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	
	

}

void Engine::DrawSideBar()
{

	if (MouseInsideCheck(Vector2f(sidebar.pos.x, sidebar.pos.y), Vector2f(sidebar.size.x, sidebar.size.y)))
	{
		finterpolate(&sidebar.pos.x, 0, 0.25);
	}
	else
	{
		finterpolate(&sidebar.pos.x, -100, 0.25);
	}

	sidebar.settingslabel.setPosition(sidebar.pos.x + 10, sidebar.pos.y + 5);
	sidebar.rect.setPosition(sidebar.pos);

	window->draw(sidebar.rect);
	window->draw(sidebar.settingslabel);
}

void Engine::CreateNoteButton(bool isnote,const char* name, sf::Vector2f pos, sf::Vector2f size,float radius)
{
	std::cout << "created a button. Size is: " << size.x << " " << size.y << "\n";
	notebutton.size = Vector2f(size.x , size.y );
	notebutton.pos = Vector2f(pos.x, pos.y);
	notebutton.name = name;
	notebutton.roundness = radius;
	notebutton.isnote = isnote;
	notebutton.charcirclevisible = false;
	notebutton.color = panelcolor;

	notebutton.init();
}

void Engine::DrawNoteButton()
{
	window->draw(notebutton.ULcircle);
	window->draw(notebutton.URcircle);
	window->draw(notebutton.DLcircle);
	window->draw(notebutton.DRcircle);
	window->draw(notebutton.rect_horiz);
	window->draw(notebutton.rect_vert);
	window->draw(notebutton.label);
	
	if (notebutton.charcirclevisible) { window->draw(notebutton.charcircle); }
}

void Engine::pollEvents() // Input shit
{
	
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case Event::Closed():
			this->window->close();
			break;
	//case Event::TextEntered:
	//	if (ev.text.unicode < 128) 																						<--	doesn't work!!!
	//	{
	//		std::wcout << "ASCII char entered: " << static_cast<char>(ev.text.unicode) << std::endl;
	//	}
	//	else
	//	{
	//		std::wcout << "Unicode char entered: " << static_cast<wchar_t>(ev.text.unicode) << std::endl;
	//		Buttons[0].text += static_cast<wchar_t>(ev.text.unicode);
	//	}
		
		case Event::KeyPressed:
			notebutton.Input(ev);
			break;

		case Event::MouseEntered:
			MouseInside = true;
			break;

		case Event::MouseLeft:
			MouseInside = false;
			break;

		case Event::MouseButtonReleased: //--  MOUSE BUTTON PRESS CHECK
			
			if (MouseInsideCheck(notebutton.pos, notebutton.size))
			{
				notebutton.StartNote();
			}

			//for (auto &e : Panels)
			//{
			//
			//	if (MouseInsideCheck(e.pos,e.size))
			//	{
			//		
			//	}
			//
			//}

			sidebar.checklabelclick();

		//case Event::MouseMoved: // WHEN MOUSE MOVES
			//for (auto& e : Panels)
			//{
			//
			//	if (Mouse::getPosition(*window).x > e.rect.getPosition().x && Mouse::getPosition(*window).x < (e.rect.getPosition().x + e.rect.getSize().x) && Mouse::getPosition(*window).y > e.rect.getPosition().y && Mouse::getPosition(*window).y < (e.rect.getPosition().y + e.rect.getSize().y))
			//	{
			//	//	std::cout << e.name << "\n";
			//	//	std::cout << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << "\n";
			//	}
			//
			//}

		}
	}
}

bool Engine::MouseInsideCheck(Vector2f pos, Vector2f size)
{
	if (MouseInside && Mouse::getPosition(*window).x > pos.x && Mouse::getPosition(*window).x < pos.x + size.x      &&     Mouse::getPosition(*window).y > pos.x && Mouse::getPosition(*window).y < pos.y + size.y)
	{
		return true;
	}
	
	else return false;
		
}

// sadfadfadfadfadfadfadfadfaddfsaaaaaaaaaa
void Engine::update()
{
	
	pollEvents();

}

void Engine::render()
{
	//-   clear shit
	window->clear(Color(220, 220, 220,255));





	//-   60 tick update
	notebutton.updateRectangles();
	UpdatePanels();
	c_filelist.updateRects();

	//-   draw shit here
	//DrawPanels();
	DrawNoteButton();
	DrawSideBar();
	c_filelist.Draw();

	//- 

	window->display();
}
