#include <word_drawer.h>

namespace WordDrawer
{
    WordDrawer::WordDrawer(const std::string& filepath, const sf::Font& font) : mFont(font), mActiveWord(nullptr) {
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
    }

    void WordDrawer::loadWords() {
        std::string word;
        while (std::getline(mWordFile, word)) {
            sf::TextCircle newWord(0, 0, mFont, word);
            mWordQueue.enqueue(newWord);
        }
    }

    void WordDrawer::update(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!mActiveWord) {
                        // dequeue a word and make it active
                        if (!mWordQueue.empty()) {
                            mActiveWord = &mWordQueue.dequeue();
                            mActiveWord -> setPosition(mousePosition);
                        }
                    }
                    else {
                        mActiveWord = nullptr;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && mActiveWord) {
                    // discard active word
                    mActiveWord = nullptr;
                }
            }
            if (mActiveWord) {
                // move active word with mouse
                sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                mActiveWord -> setPosition(mousePosition);
            }
        }
    }

    void WordDrawer::draw(sf::RenderWindow& window) {
        window.draw(mStatusText);
    }
}