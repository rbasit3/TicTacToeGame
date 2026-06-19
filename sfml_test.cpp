#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;

// This tells the program which screen to show
enum class ScreenState
{
    MainMenu,
    Rules,
    PlayerSetup,
    ExitScreen
};

// Reusable button class
struct Button
{
    sf::RectangleShape box;
    sf::Text text;
    sf::Color normalColor;
    sf::Color hoverColor;

    Button(
        const sf::Font& font,
        const std::string& label,
        sf::Vector2f size,
        sf::Vector2f position,
        sf::Color buttonColor,
        sf::Color buttonHoverColor,
        sf::Color textColor
    )
        : box(size),
          text(font),
          normalColor(buttonColor),
          hoverColor(buttonHoverColor)
    {
        box.setPosition(position);
        box.setFillColor(normalColor);
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2.f);

        text.setString(label);
        text.setCharacterSize(30);
        text.setFillColor(textColor);

        // Center text inside button
        sf::FloatRect textBounds = text.getLocalBounds();

        text.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.f,
            textBounds.position.y + textBounds.size.y / 2.f
        });

        text.setPosition({
            position.x + size.x / 2.f,
            position.y + size.y / 2.f
        });
    }

    void update(sf::Vector2f mousePosition)
    {
        if (isMouseOver(mousePosition))
        {
            box.setFillColor(hoverColor);
        }
        else
        {
            box.setFillColor(normalColor);
        }
    }

    bool isMouseOver(sf::Vector2f mousePosition) const
    {
        return box.getGlobalBounds().contains(mousePosition);
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(box);
        window.draw(text);
    }
};

void drawMainMenu(
    sf::RenderWindow& window,
    sf::Text& title,
    Button& rulesButton,
    Button& startButton,
    Button& exitButton
)
{
    window.clear(sf::Color::Black);

    window.draw(title);

    rulesButton.draw(window);
    startButton.draw(window);
    exitButton.draw(window);

    window.display();
}

void drawRulesScreen(
    sf::RenderWindow& window,
    sf::Text& rulesTitle,
    sf::Text& rulesText,
    Button& backButton
)
{
    window.clear(sf::Color::Black);

    window.draw(rulesTitle);
    window.draw(rulesText);
    backButton.draw(window);

    window.display();
}

void drawPlayerSetupScreen(
    sf::RenderWindow& window,
    sf::Text& setupTitle,
    sf::Text& setupText,
    Button& backButton
)
{
    window.clear(sf::Color::Black);

    window.draw(setupTitle);
    window.draw(setupText);
    backButton.draw(window);

    window.display();
}

void drawExitScreen(
    sf::RenderWindow& window,
    sf::Text& exitTitle,
    sf::Text& exitText,
    Button& closeButton
)
{
    window.clear(sf::Color::Black);

    window.draw(exitTitle);
    window.draw(exitText);
    closeButton.draw(window);

    window.display();
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Tic Tac Toe - Menu"
    );

    sf::Font font;

    if (!font.openFromFile("assets/fonts/font.ttf"))
    {
        std::cout << "Font failed to load!" << std::endl;
        return -1;
    }

    ScreenState currentScreen = ScreenState::MainMenu;

    // ---------------- MAIN MENU TEXT ----------------

    sf::Text title(font);
    title.setString("TIC TAC TOE");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition({250.f, 90.f});

    // ---------------- MAIN MENU BUTTONS ----------------

    Button rulesButton(
        font,
        "View Rules",
        {300.f, 70.f},
        {300.f, 240.f},
        sf::Color(40, 120, 180),
        sf::Color(70, 160, 220),
        sf::Color::White
    );

    Button startButton(
        font,
        "Start Game",
        {300.f, 70.f},
        {300.f, 340.f},
        sf::Color(40, 160, 90),
        sf::Color(70, 210, 130),
        sf::Color::White
    );

    Button exitButton(
        font,
        "Exit",
        {300.f, 70.f},
        {300.f, 440.f},
        sf::Color(180, 50, 70),
        sf::Color(230, 80, 100),
        sf::Color::White
    );

    // ---------------- RULES SCREEN TEXT ----------------

    sf::Text rulesTitle(font);
    rulesTitle.setString("RULES");
    rulesTitle.setCharacterSize(60);
    rulesTitle.setFillColor(sf::Color::Cyan);
    rulesTitle.setPosition({360.f, 60.f});

    sf::Text rulesText(font);
    rulesText.setString(
        "1. Players take turns placing their symbols.\n\n"
        "2. Click an empty cell to place your symbol.\n\n"
        "3. First player to get 3 in a row wins.\n\n"
        "4. You can win horizontally, vertically, or diagonally.\n\n"
        "5. If all 9 cells are filled and nobody wins,\n"
        "   the game is a draw."
    );
    rulesText.setCharacterSize(28);
    rulesText.setFillColor(sf::Color::Yellow);
    rulesText.setPosition({130.f, 160.f});

    Button backFromRulesButton(
        font,
        "Back",
        {220.f, 60.f},
        {340.f, 570.f},
        sf::Color(90, 90, 90),
        sf::Color(130, 130, 130),
        sf::Color::White
    );

    // ---------------- PLAYER SETUP SCREEN TEXT ----------------

    sf::Text setupTitle(font);
    setupTitle.setString("PLAYER SETUP");
    setupTitle.setCharacterSize(55);
    setupTitle.setFillColor(sf::Color::Cyan);
    setupTitle.setPosition({250.f, 80.f});

    sf::Text setupText(font);
    setupText.setString(
        "This is where we will ask for:\n\n"
        "Player 1 name\n"
        "Player 1 symbol\n\n"
        "Player 2 name\n"
        "Player 2 symbol\n\n"
        "We will build this in the next step."
    );
    setupText.setCharacterSize(30);
    setupText.setFillColor(sf::Color(255, 180, 80));
    setupText.setPosition({230.f, 190.f});

    Button backFromSetupButton(
        font,
        "Back",
        {220.f, 60.f},
        {340.f, 570.f},
        sf::Color(90, 90, 90),
        sf::Color(130, 130, 130),
        sf::Color::White
    );

    // ---------------- EXIT SCREEN TEXT ----------------

    sf::Text exitTitle(font);
    exitTitle.setString("GOODBYE!");
    exitTitle.setCharacterSize(65);
    exitTitle.setFillColor(sf::Color::Cyan);
    exitTitle.setPosition({300.f, 160.f});

    sf::Text exitText(font);
    exitText.setString("Thanks for playing Tic Tac Toe.");
    exitText.setCharacterSize(32);
    exitText.setFillColor(sf::Color::Yellow);
    exitText.setPosition({250.f, 270.f});

    Button closeButton(
        font,
        "Close Window",
        {300.f, 70.f},
        {300.f, 400.f},
        sf::Color(180, 50, 70),
        sf::Color(230, 80, 100),
        sf::Color::White
    );

    // ---------------- MAIN LOOP ----------------

    while (window.isOpen())
    {
        sf::Vector2f mousePosition =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Update hover effect depending on current screen
        if (currentScreen == ScreenState::MainMenu)
        {
            rulesButton.update(mousePosition);
            startButton.update(mousePosition);
            exitButton.update(mousePosition);
        }
        else if (currentScreen == ScreenState::Rules)
        {
            backFromRulesButton.update(mousePosition);
        }
        else if (currentScreen == ScreenState::PlayerSetup)
        {
            backFromSetupButton.update(mousePosition);
        }
        else if (currentScreen == ScreenState::ExitScreen)
        {
            closeButton.update(mousePosition);
        }

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f clickPosition =
                        window.mapPixelToCoords(mouseButton->position);

                    if (currentScreen == ScreenState::MainMenu)
                    {
                        if (rulesButton.isMouseOver(clickPosition))
                        {
                            currentScreen = ScreenState::Rules;
                        }
                        else if (startButton.isMouseOver(clickPosition))
                        {
                            currentScreen = ScreenState::PlayerSetup;
                        }
                        else if (exitButton.isMouseOver(clickPosition))
                        {
                            currentScreen = ScreenState::ExitScreen;
                        }
                    }
                    else if (currentScreen == ScreenState::Rules)
                    {
                        if (backFromRulesButton.isMouseOver(clickPosition))
                        {
                            currentScreen = ScreenState::MainMenu;
                        }
                    }
                    else if (currentScreen == ScreenState::PlayerSetup)
                    {
                        if (backFromSetupButton.isMouseOver(clickPosition))
                        {
                            currentScreen = ScreenState::MainMenu;
                        }
                    }
                    else if (currentScreen == ScreenState::ExitScreen)
                    {
                        if (closeButton.isMouseOver(clickPosition))
                        {
                            window.close();
                        }
                    }
                }
            }
        }

        if (currentScreen == ScreenState::MainMenu)
        {
            drawMainMenu(
                window,
                title,
                rulesButton,
                startButton,
                exitButton
            );
        }
        else if (currentScreen == ScreenState::Rules)
        {
            drawRulesScreen(
                window,
                rulesTitle,
                rulesText,
                backFromRulesButton
            );
        }
        else if (currentScreen == ScreenState::PlayerSetup)
        {
            drawPlayerSetupScreen(
                window,
                setupTitle,
                setupText,
                backFromSetupButton
            );
        }
        else if (currentScreen == ScreenState::ExitScreen)
        {
            drawExitScreen(
                window,
                exitTitle,
                exitText,
                closeButton
            );
        }
    }

    return 0;
}