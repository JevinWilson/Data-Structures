#pragma once
#include <SFML/Graphics.hpp>
#include <stack.h>
#include <queue.h>
#include <text_circle.h>
#include <fstream>
#include <string>
#include <random>

namespace WordDrawer
{
    struct Undo {
        enum ActionType {Place, Move} type;
        sf::TextCircle* circle;
        sf::Vector2f prevPosition;

        Undo(ActionType t, sf::TextCircle* c, sf::Vector2f pos = sf::Vector2f()) : type(t), circle(c), prevPosition(pos) {}
    };

    class WordDrawer {
    protected:
        ssuds::queue<sf::TextCircle*> mWordQueue;
        ssuds::stack<Undo> UndoStack;
        std::ifstream mWordFile;
        sf::TextCircle* mActiveWord = nullptr;
        std::vector<sf::TextCircle*> mPlacedWords;
        sf::Font mFont;
        sf::Text mStatusText;
        
        // rand text not working
        /*std::vector<std::string> words;
        std::mt19937 rndm;*/
        
    
    public:
        WordDrawer(const std::string& filepath, const sf::Font& font);
        ~WordDrawer();
        void loadWords();
        void update(sf::RenderWindow& window);
        bool mouseWasPressed = false;
        void draw(sf::RenderWindow& window);
    };
}