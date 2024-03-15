// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define DO_UNIT_TESTING 0
#include <iostream>
#if DO_UNIT_TESTING 0
#include <gtest/gtest.h>
#else
#include <linked_list.h>
#include <SFML/Graphics.hpp>
#include <word_drawer.h>
#include <text_circle.h>
#include <iostream>
#endif

#include <fstream> 
int main()
{
#if DO_UNIT_TESTING 
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    sf::RenderWindow window(sf::VideoMode(800, 600), "Word Drawer");

    sf::Font font;
    if (!font.loadFromFile("../../../media/fonts/Radiant_kingdom/RadiantKingdom-mL5eV.ttf"))
        throw std::runtime_error("failed to load font");

    WordDrawer::WordDrawer WordDrawer("../../../media/SCOWL/final/american-words.80", font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            WordDrawer.update(window);
        }
        window.clear();
        WordDrawer.draw(window);
        window.display();
    }

    return 0;
    


#endif
}
