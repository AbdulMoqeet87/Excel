#include<iostream>
#include"Excel.h"
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main()
{
	Excel* excl = new Excel();
	
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

int main89() {
    sf::RenderWindow window(sf::VideoMode(1375, 696), "Scrollable Rectangles");

    // Create the scroll bars
    sf::RectangleShape verticalScrollBar(sf::Vector2f(22, 1200));
    verticalScrollBar.setPosition(1350, 0);
    verticalScrollBar.setFillColor(sf::Color::Blue);

    sf::RectangleShape horizontalScrollBar(sf::Vector2f(1200, 22));
    horizontalScrollBar.setPosition(0, 674);
    horizontalScrollBar.setFillColor(sf::Color::Blue);

    // Create the scroll thumbs
    sf::RectangleShape verticalThumb(sf::Vector2f(22, 40));
    verticalThumb.setPosition(1350, 0);
    verticalThumb.setFillColor(sf::Color::Red);

    sf::RectangleShape horizontalThumb(sf::Vector2f(40, 22));
    horizontalThumb.setPosition(0, 670);
    horizontalThumb.setFillColor(sf::Color::Red);

    // Create some rectangles
    sf::RectangleShape rectangles[30]; // 3 rows of 10 rectangles each
    for (int i = 0; i < 30; i++) {
        rectangles[i] = sf::RectangleShape(sf::Vector2f(80, 25));
        rectangles[i].setFillColor(sf::Color::Green);
        rectangles[i].setPosition(80 + (i % 10) * 85, 80 + (i / 10) * 30);
    }

    bool isVerticalDragging = false;
    bool isHorizontalDragging = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == event.MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (verticalThumb.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        isVerticalDragging = true;
                    }
                    else if (horizontalThumb.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        isHorizontalDragging = true;
                    }
                }
            }
            else if (event.type == event.MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isVerticalDragging = false;
                    isHorizontalDragging = false;
                }
            }
            else if (event.type == event.MouseMoved) {
                if (isVerticalDragging) {
                    // Move the vertical thumb along the y-axis
                    verticalThumb.setPosition(1350, event.mouseMove.y - verticalThumb.getSize().y / 2);
                }
                if (isHorizontalDragging) {
                    // Move the horizontal thumb along the x-axis
                    horizontalThumb.setPosition(event.mouseMove.x - horizontalThumb.getSize().x / 2, 674);
                }
            }
        }

        // Calculate the vertical offset for scrolling
        float verticalOffset = (verticalThumb.getPosition().y - 0) / (verticalScrollBar.getSize().y - verticalThumb.getSize().y);
        // Calculate the horizontal offset for scrolling
        float horizontalOffset = (horizontalThumb.getPosition().x - 0) / (horizontalScrollBar.getSize().x - horizontalThumb.getSize().x);

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the scroll bars and thumbs
        window.draw(verticalScrollBar);
        window.draw(horizontalScrollBar);
        window.draw(verticalThumb);
        window.draw(horizontalThumb);

        // Draw the rectangles, adjusting their positions based on the offsets
        for (int i = 0; i < 30; i++) {
            sf::RectangleShape rect = rectangles[i];
            rect.move(-horizontalOffset * 85, -verticalOffset * 30);
            window.draw(rect);
        }

        // Display the contents
        window.display();
    }

    return 0;
}

//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//int main3()
//{
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Context Menu");
//    window.setFramerateLimit(60);
//
//    // Create a font for the menu items
//    sf::Font font;
//    if (!font.loadFromFile(("TimesRoman.ttf"))) {
//        return -1; // Font loading failed
//    }
//
//    // Create a boolean to track if the context menu is visible
//    bool isContextMenuVisible = false;
//
//    // Create the context menu items
//    sf::Text refreshText("Refresh", font, 24);
//    refreshText.setFillColor(sf::Color::Black);
//    refreshText.setPosition(10, 10);
//
//    sf::Text displayText("Display", font, 24);
//    displayText.setFillColor(sf::Color::Black);
//    displayText.setPosition(10, 40);
//
//    sf::Text helloText("Hello", font, 24);
//    helloText.setFillColor(sf::Color::Black);
//    helloText.setPosition(10, 70);
//
//    // Variables to store the position where the context menu is triggered
//    sf::Vector2f contextMenuPosition;
//
//    while (window.isOpen()) 
//    {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            if (event.type == event.MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Right) {
//                    isContextMenuVisible = true;
//                    contextMenuPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
//                }
//            }
//
//            if (event.type == event.MouseButtonReleased) {
//                if (event.mouseButton.button == sf::Mouse::Right) {
//                    isContextMenuVisible = true;
//                }
//            }
//
//            // Check if an option was selected
//            if (event.type == event.MouseButtonPressed)
//            {
//                if (event.mouseButton.button == sf::Mouse::Left)
//                {
//                    {
//
//                        if (refreshText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
//                            std::cout << "Refresh option selected." << std::endl;
//                        }
//                        else if (displayText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
//                            std::cout << "Display option selected." << std::endl;
//                        }
//                        else if (helloText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
//                            std::cout << "Hello option selected." << std::endl;
//                        }
//                    }
//                }
//
//            }
//
//            window.clear(sf::Color::White);
//
//            // Draw your application content here
//
//            if (isContextMenuVisible) {
//                // Draw the context menu
//                sf::RectangleShape contextMenuBackground(sf::Vector2f(120, 100));
//                contextMenuBackground.setPosition(contextMenuPosition);
//                contextMenuBackground.setFillColor(sf::Color::Blue);
//                refreshText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 5);
//                displayText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 35);
//                helloText.setPosition(contextMenuPosition.x + 4, contextMenuPosition.y + 55);
//                window.draw(contextMenuBackground);
//                window.draw(refreshText);
//                window.draw(displayText);
//                window.draw(helloText);
//            }
//
//            window.display();
//        }
//
//    }
//        return 0;
//}
