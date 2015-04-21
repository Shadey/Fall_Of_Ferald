#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Pathfinder.h"
#include "InputManager.h"
#include "UserInterface.h"
#include "AI.h"
#include <iostream>
#include <list>

class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
        void render();
        void update();
    private:
        ImageManager imageManager;
		InputManager inputManager;
        sf::RenderWindow window;
		sf::Event event;
		UserInterface ui;
        Level* testLevel;

		bool close = false;
        bool turnPassed = false;    // Flag to stop the AI from taking multiple turns

		// Private functions for threading
        static void* inputThread(void* args);
		inline InputManager* getInputManager() { return &inputManager; }
		inline sf::RenderWindow& getWindow() { return window; }
};

#endif // GAME_H
