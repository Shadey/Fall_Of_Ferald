#include "Game.h"
#include <SFML/System/Vector2.hpp>
#include <list>
#include <thread>

Game::Game()
{
    window.create(sf::VideoMode(1280, 720), "Fall of Ferald - Refactoring");
}

Game::~Game()
{
    delete testLevel;
}

void Game::run()
{
    testLevel = new Level("levels/example/map.txt", "assets/images/tileSheets/spriteSheet.png", &imageManager);
    testLevel->initilizeAI("levels/example/units.txt", "assets/images/unitSprites", imageManager);

	// Loading the interface data
	imageManager.loadImage("assets/images/interface/tooltip.png", "tooltip");
	imageManager.loadImage("assets/images/interface/Dialogue.png", "dialogueBox");
	ui.addDialogueBox("dialogue/test.txt", imageManager.getTexture("dialogueBox"), 0, 500);

    //float lastTime = 0;
    //sf::Clock clock;
    window.setFramerateLimit(60);

	// Deactivating the window's openGL context
	window.setActive(false);

    while (!close)
    {
		// Launching the input thread
		std::thread inputThread(&Game::inputThread, this);

		// Updating during the main thread
        update();
        render();

		// Closing the input thread
		inputThread.join();
    }
}

void Game::update()
{
    //float currentTime = clock.restart().asSeconds();
    //float fps = 1.f / currentTime;//(currentTime - lastTime);
    //lastTime = currentTime;

    std::vector<sf::Vector3i> locations;
	std::stack<sf::Vector2i> path;

	// Updating the input manager
	//inputManager.update(window);

	// Updating the UI
	ui.update(inputManager.getMousePosition(), inputManager.getPrevMousePosition(),
			  inputManager.pressedOnce(sf::Mouse::Left), inputManager.pressedOnce(sf::Mouse::Right));

	// Updating the level
	testLevel->update(inputManager, ui);

	// Checking if the window's been closed
	if(inputManager.pressedOnce("cancel"))
	{
		std::cout << "Closing...!" << std::endl;
		close = true;
	}
	else if (inputManager.pressedOnce("confirm"))
	{
		ui.addTooltip("Test Tooltip", "Sometext", imageManager.getTexture("tooltip"), 50, 50);
	}
}

void Game::inputThread(void* args)
{
	// args should only ever be this, so static casting should be fine
	Game* thisGame = static_cast<Game*>(args);
	thisGame->getInputManager()->update(thisGame->getWindow());
	//return NULL;
}
void Game::render()
{
	/*sf::Context context;
	context.setActive(true);*/
	window.setActive(true);
    window.clear();
    testLevel->draw(window);
	ui.draw(&window);
    window.display();
}
