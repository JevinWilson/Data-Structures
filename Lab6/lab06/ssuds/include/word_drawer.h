#pragma once
#include <SFML/Graphics.hpp>
#include <linked_list.h>
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
        sf::Vector2f prevPostition;

        Undo(ActionType t, sf::TextCircle* c, sf::Vector2f pos = sf::Vector2f()) : type(t), circle(c), prevPostition(pos) {}
    };

    class WordDrawer {
    protected:
        ssuds::queue<sf::TextCircle> mWordQueue;
        ssuds::stack<Undo> UndoStack;
        std::ifstream mWordFile;
        sf::TextCircle* mActiveWord = nullptr;
        std::vector<sf::TextCircle*> mPlacedWords;
        sf::Font mFont;
        sf::Text mStatusText;
    
    public:
        WordDrawer(const std::string& filepath, const sf::Font& font);
        ~WordDrawer();
        void loadWords();
        void update(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
    };
}