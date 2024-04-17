#define DO_UNIT_TEST 0
#if DO_UNIT_TEST
#include <gtest/gtest.h>
#else
#include <SFML/Graphics.hpp>
#include <graph_creator.h>
#endif

int main()
{
#if DO_UNIT_TEST
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Graph Creator");
    
    // Note the trick I did with static's requires this
    misc::GraphCreator::create_keycode_to_name_dbase();

    sf::Font status_font, circle_font;
    if (!status_font.loadFromFile("../../../media/fonts/Courier_Prime/CourierPrime-Regular.ttf") ||
        !circle_font.loadFromFile("../../../media/fonts/Open_Sans/static/OpenSans-Regular.ttf"))
        std::cout << "Error loading fonts\n";

    misc::GraphCreator GC(circle_font, status_font);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || GC.handle_event(event))
                window.close();
        }

        window.clear();
        GC.draw(window);
        window.display();
    }
   
    return 0;
#endif
}