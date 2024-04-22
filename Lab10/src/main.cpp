#define DO_UNIT_TEST 0
#if DO_UNIT_TEST
#include <gtest/gtest.h>
#else
#include <SFML/Graphics.hpp>
#include <visual_graph.h>
#endif

#if !DO_UNIT_TEST
// some helper functions used in main

#endif

int main()
{
#if DO_UNIT_TEST
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Graph Creator");
    
    sf::Font status_font, circle_font;
    if (!status_font.loadFromFile("../../../media/fonts/Courier_Prime/CourierPrime-Regular.ttf") ||
        !circle_font.loadFromFile("../../../media/fonts/Open_Sans/static/OpenSans-Regular.ttf"))
        std::cout << "Error loading fonts\n";

    misc::VisualGraph GC(circle_font, "../../../media/output.txt");

<<<<<<< HEAD
<<<<<<< HEAD
    int selectedNode = -1;
=======
>>>>>>> parent of c22a569 (sort of working 2c)
=======
>>>>>>> parent of c22a569 (sort of working 2c)


     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

<<<<<<< HEAD
<<<<<<< HEAD
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                selectedNode = GC.handle_mouse_click(mousePos.x, mousePos.y);
                if (selectedNode != -1)
                {
                    GC.highlight_node(selectedNode, sf::TextCircleHighlightMode::WHITE);  // Highlight the selected node
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
            {
                if (selectedNode != -1) // Make sure there is a selected node
                {
                    ssuds::ArrayList<std::pair<int, int>> bfsTraversal;
                    GC.bfs(bfsTraversal);  // Perform BFS and store the result

                    std::cout << "BFS Traversal from Node " << selectedNode << ":\n";
                    for (auto& pair : bfsTraversal)
                    {
                        std::cout << "Node: " << pair.first << " to Node: " << pair.second << std::endl;
                    }
                    GC.clear_highlights();  // Optionally clear highlights after processing
                    selectedNode = -1;  // Reset selected node
=======
=======
>>>>>>> parent of c22a569 (sort of working 2c)
            // Handle mouse click for node selection
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    GC.handle_mouse_click(mousePos.x, mousePos.y);
<<<<<<< HEAD
>>>>>>> parent of c22a569 (sort of working 2c)
=======
>>>>>>> parent of c22a569 (sort of working 2c)
                }
            }
        }

        window.clear();
<<<<<<< HEAD
<<<<<<< HEAD
        GC.draw(window);
        window.display();
    }

=======
        GC.draw(window); 
        window.display();
    }
=======
        GC.draw(window); 
        window.display();
    }
>>>>>>> parent of c22a569 (sort of working 2c)
   
>>>>>>> parent of c22a569 (sort of working 2c)
    return 0;
#endif
}