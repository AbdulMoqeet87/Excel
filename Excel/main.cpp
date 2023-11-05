#include<iostream>
#include"Excel.h"
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main()
{
	Excel* excl = new Excel();
    excl->Starting();
	try
	{

	excl->LaunchExcel();

	}
	catch (...)
	{
		cout << "error Agyaaa";
	}
    return 0;


}



//#include <SFML/Graphics.hpp>
//#include <iostream>
//
int main111()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Context Menu");
    window.setFramerateLimit(60);

    // Create a font for the menu items
    sf::Font font;
    if (!font.loadFromFile(("TimesRoman.ttf"))) {
        return -1; // Font loading failed
    }

    // Create a boolean to track if the context menu is visible
    bool isContextMenuVisible = false;

    // Create the context menu items
    sf::Text refreshText("Refresh", font, 24);
    refreshText.setFillColor(sf::Color::Black);
    refreshText.setPosition(10, 10);

    sf::Text displayText("Display", font, 24);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(10, 40);

    sf::Text helloText("Hello", font, 24);
    helloText.setFillColor(sf::Color::Black);
    helloText.setPosition(10, 70);

    // Variables to store the position where the context menu is triggered
    sf::Vector2f contextMenuPosition;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == event.MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isContextMenuVisible = true;
                    contextMenuPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                }
            }

            
            // Check if an option was selected
            if (event.type == event.MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    

                        if (refreshText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            std::cout << "Refresh option selected." << std::endl;
                        }
                        else if (displayText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            std::cout << "Display option selected." << std::endl;
                        }
                        else if (helloText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            std::cout << "Hello option selected." << std::endl;
                        }
                      
                        isContextMenuVisible = false;
                    
                }

            }

            window.clear(sf::Color::White);

            // Draw your application content here

            if (isContextMenuVisible) {
                // Draw the context menu
                sf::RectangleShape contextMenuBackground(sf::Vector2f(120, 100));
                contextMenuBackground.setPosition(contextMenuPosition);
                contextMenuBackground.setFillColor(sf::Color::Blue);
                refreshText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 5);
                displayText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 35);
                helloText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 55);
                window.draw(contextMenuBackground);
                window.draw(refreshText);
                window.draw(displayText);
                window.draw(helloText);
            }
            

            window.display();
        }

    }
        return 0;
}
