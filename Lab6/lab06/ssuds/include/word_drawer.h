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
    class WordDrawer {
    protected:
        ssuds::queue<sf::TextCircle> mWordQueue;
        std::ifstream mWordFile;
        sf::TextCircle* mActiveWord;
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