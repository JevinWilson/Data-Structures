#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <text_circle.h>
#include <Graph.h>

// Load graph from a file
void loadGraphFromFile(const std::string& filename, ssuds::Graph<int, float>& graph, std::unordered_map<int, sf::Vector2f>& positions, std::unordered_map<int, sf::Color>& colors) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        iss >> type;
        if (type != 'n' && type != 'e') {
            std::cerr << "Unknown line type: " << line << std::endl;
            continue;
        }

        iss.ignore(1); // Ignore colon after 'n' or 'e'

        if (type == 'n') {
            int id, r, g, b, x, y;
            std::string label;
            char colon;
            iss >> id >> colon;
            if (!std::getline(iss, label, ':')) {
                std::cerr << "Failed to parse label in node line: " << line << std::endl;
                continue;
            }
            iss >> r >> colon >> g >> colon >> b >> colon >> x >> colon >> y;
            if (iss.fail()) {
                std::cerr << "Failed to parse node line: " << line << std::endl;
                continue;
            }
            graph.add_node(id);
            positions[id] = sf::Vector2f(x, y);
            colors[id] = sf::Color(r, g, b);
            std::cout << "Loaded node " << id << " at (" << x << ", " << y << ") with color (" << r << ", " << g << ", " << b << ")" << std::endl;
        } else if (type == 'e') {
            int start, end;
            float weight;
            char colon;
            iss >> start >> colon >> end >> colon >> weight;
            if (iss.fail()) {
                std::cerr << "Failed to parse edge line: " << line << std::endl;
                continue;
            }
            graph.add_edge(start, end, weight);
            std::cout << "Loaded edge from " << start << " to " << end << " with weight " << weight << std::endl;
        }
    }
    std::cout << "Total nodes loaded: " << graph.get_all_nodes().size() << std::endl;
    std::cout << "Total edges loaded: " << graph.get_all_edges().size() << std::endl;
}


// Display the graph using SFML and TextCircle 
void displayGraph(const ssuds::Graph<int, float>& graph, const std::unordered_map<int, sf::Vector2f>& positions, const std::unordered_map<int, sf::Color>& colors) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Display");
    sf::Font font;
    if (!font.loadFromFile("../../../media/fonts/Lato/Lato-Bold.ttf")) { 
        std::cerr << "Could not load font\n";
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); 

        // Draw edges
        for (const auto& edge : graph.get_all_edges()) {
            auto start_pos = positions.at(std::get<0>(edge));
            auto end_pos = positions.at(std::get<1>(edge));
            sf::Vertex line[] = {
                sf::Vertex(start_pos, sf::Color::White),
                sf::Vertex(end_pos, sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw nodes
        for (const auto& node : graph.get_all_nodes()) {
            if (positions.find(node) == positions.end() || colors.find(node) == colors.end()) {
                std::cerr << "Missing position or color for node " << node << std::endl;
                continue;
            }
            sf::TextCircle circle(positions.at(node).x, positions.at(node).y, font, std::to_string(node));
            circle.setCircleColor(colors.at(node));
            window.draw(circle);
        }

        window.display();
    }
}