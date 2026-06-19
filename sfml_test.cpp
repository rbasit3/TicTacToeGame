#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({600, 600}),
        "Font Test - SFML"
    );

    sf::Font font;

    if (!font.openFromFile("assets/fonts/font.ttf"))
    {
        std::cout << "Font failed to load!" << std::endl;
        return -1;
    }

    sf::Text title(font);
    title.setString("TIC TAC TOE");
    title.setCharacterSize(55);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition({130.f, 80.f});

    sf::Text subtitle(font);
    subtitle.setString("Font loaded successfully");
    subtitle.setCharacterSize(25);
    subtitle.setFillColor(sf::Color::Yellow);
    subtitle.setPosition({155.f, 170.f});

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(title);
        window.draw(subtitle);

        window.display();
    }

    return 0;
}