#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>


class DialogueBox
{
    friend class UserInterface;

    public:
        DialogueBox();
        virtual ~DialogueBox();
        bool openScript(const std::string& filePath);
        void nextLine();
        void draw(sf::RenderWindow *window);

    private:
        std::ifstream openFile; // The filestream needed to open the file
        sf::Text name;          // The name of the character that is currently talking
        sf::Text dialogue;      // The dialogue being displayed
        sf::Sprite sprite;
		bool active;			// Wether or not the dialogue box should be drawn
};

#endif // DIALOGUEBOX_H
