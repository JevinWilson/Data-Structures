#include <word_drawer.h>

namespace WordDrawer
{
    WordDrawer::WordDrawer(const std::string& filepath, const sf::Font& font) : mFont(font), mActiveWord(nullptr) {
        /*std::random_device rd;
        rndm = std::mt19937(rd());*/

        mWordFile.open(filepath, std::ios::binary);
        if (!mWordFile.is_open())
            throw std::runtime_error("failed to open file");
        
        mStatusText.setFont(mFont);
        mStatusText.setString("Click to place word, right click to discard");
        mStatusText.setCharacterSize(24);
        mStatusText.setFillColor(sf::Color::White);
        mStatusText.setPosition(10, 10);

        loadWords();
    }

    WordDrawer::~WordDrawer() {
        if (mWordFile.is_open()) 
            mWordFile.close();
        for (auto& word : mPlacedWords)
            delete word;
        if (mActiveWord)
            delete mActiveWord;
    }

    void WordDrawer::loadWords() {
        std::string word;
        while (std::getline(mWordFile, word) && mWordQueue.size() < 10) {
            sf::TextCircle* newWord = new sf::TextCircle(100, 100, mFont, word); 
            mWordQueue.enqueue(newWord);
        }
    }

    void WordDrawer::update(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // CTRL+Z Undo
            if (event.type == sf::Event::KeyPressed && event.key.control && event.key.code == sf::Keyboard::Z && !UndoStack.empty()) {
                Undo lastAction = UndoStack.top();
                UndoStack.pop();
                if (lastAction.type == Undo::Place) {
                    auto it = std::find(mPlacedWords.begin(), mPlacedWords.end(), lastAction.circle);
                    if (it != mPlacedWords.end()) {
                        delete* it; 
                        mPlacedWords.erase(it);
                    }
                }
                else if (lastAction.type == Undo::Move) {
                    lastAction.circle->setPosition(lastAction.prevPosition);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    //std::cout << "Left-click at: " << mousePosition.x << ", " << mousePosition.y << std::endl;

                    // Ensure there's a word to spawn
                    if (!mWordQueue.empty()) {
                        sf::TextCircle* newCircle = mWordQueue.dequeue();
                        newCircle->setPosition(mousePosition); 
                        mPlacedWords.push_back(newCircle); 
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right && mActiveWord) {
                    delete mActiveWord;
                    mActiveWord = nullptr;
                }
            }

        }
    }


    void WordDrawer::draw(sf::RenderWindow& window) {
        for (auto& word : mPlacedWords) {
            window.draw(*word);
        }
        if (mActiveWord) {
            window.draw(*mActiveWord);
        }
        window.draw(mStatusText);
    }
}