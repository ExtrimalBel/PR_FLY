#include "Game.h"

Game::Game()
{
	try
	{
		ConfigReader::ReadGameConfig(BaseGamePath + "/Config.xml", Options);
	}
	catch (Exceptions::XMLDocumentReadError &Ex)
	{
		ErrScr = new Screens::ErrorScreen(cox, coy, BaseGamePath, "Ошибка при загрузке настроек\nУстанавливаем стандартные");
		State = ErrorMessage;
		Options.vidx = 640;
		Options.vidy = 480;
		Options.GameModePath = "./vanilla";
	}
	cox = Options.vidx;
	coy = Options.vidy;
	cox /= 1920;
	coy /= 1080;
	if (Options.Fullscreen == "Fullscreen") VideoMode = sf::Style::Fullscreen;
	else if (Options.Fullscreen == "Windowed") VideoMode = sf::Style::Default;
	else throw Exceptions::AbnormalException("Неизвестная ошибка");
	window = new sf::RenderWindow(sf::VideoMode(Options.vidx, Options.vidy), "PR_FLY", VideoMode);
	
	if (!CreateMainMenuScreen()) throw Exceptions::AbnormalException("Недостаточно памяти");
}

void Game::UpdateLoadGameScreen(sf::RenderWindow &window, float time) // Метолд обновляет экран загрузки игры
{
	LM->Update(time, window);
}

void Game::UpdateGameField(sf::RenderWindow &window, float time)
{
	Field->UpdateAll(time, window);
}

void Game::UpdateSettings(sf::RenderWindow &window, float time)
{
	//Todo Write Setting class
}

void Game::UpdateMainMenu(sf::RenderWindow &window, float time)
{
	Menu->Update(time, window);
}

bool Game::CreateGameField()
{
	if (Menu = new MainM(cox,coy,*SPlayer,BaseGamePath)) return true;
	else return false;
}

bool Game::CreateSoundSystem()
{
	if (SPlayer = new SoundSystem::SoundPlayer()) return true;
	else return false;
}

bool Game::CreateLoadGameScreen()
{
	if (LM = new LoadM(cox, coy, *SPlayer,BaseGamePath)) return true;
	else return false;
}

bool Game::CreateSettingsScreen()
{
	//Todo Write setting class
}

bool Game::CreateMainMenuScreen()
{
	if (Menu = new MainM(cox, coy, *SPlayer, BaseGamePath)) return true;
	else return false;
}


void Game::Update()
{
	while (window->isOpen())
	{
		window->setMouseCursorVisible(false);
		window->clear();
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		window->clear();
		switch (State)
		{
		case GameF:
			Field->UpdateAll(time, *window);
			if (Field->IfExit() == 1) // Выходим в главное меню
			{
				CreateMainMenuScreen();
				delete Field;
				State = MainMenu;
			}
			break;
		case Settings:
			break;
		case MainMenu:
			Menu->Update(time, *window);
			if (Menu->MenuSelect() == 1)
			{
				State = GameF;
				CreateGameField();
				delete Menu;
			}
			if (Menu->MenuSelect() == 4)
			{
				delete SPlayer;
				delete Menu;
				window->close();
			}
			if (Menu->MenuSelect() == 2)
			{
				LM = new LoadM(cox,coy,*SPlayer,BaseGamePath);
				State = LoadGame;
				delete Menu;
			}
			break;
		case LoadGame:
			LM->Update(time, *window);

			break;
		case ErrorMessage:
			ErrScr->Update(*window);
			if (ErrScr->IfExit())
			{
				if (!CreateMainMenuScreen()) throw Exceptions::AbnormalException("Недостаточно памяти");
				State = MainMenu;
			}

			break;

		}
		window->display();
	}
}


bool Game::CreateErrorMessage()
{

}