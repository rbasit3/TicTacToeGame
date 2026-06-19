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
    Playing,
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

// Reusable text input box
struct TextBox
{
    sf::RectangleShape box;
    sf::Text label;
    sf::Text valueText;
    std::string value;
    bool isActive;
    int characterLimit;

    TextBox(
        const sf::Font& font,
        const std::string& labelText,
        sf::Vector2f size,
        sf::Vector2f position,
        int limit
    )
        : box(size),
          label(font),
          valueText(font),
          isActive(false),
          characterLimit(limit)
    {
        box.setPosition(position);
        box.setFillColor(sf::Color(20, 20, 20));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2.f);

        label.setString(labelText);
        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Cyan);
        label.setPosition({position.x, position.y - 35.f});

        valueText.setString("");
        valueText.setCharacterSize(26);
        valueText.setFillColor(sf::Color::White);
        valueText.setPosition({position.x + 12.f, position.y + 12.f});
    }

    void setActive(bool active)
    {
        isActive = active;

        if (isActive)
        {
            box.setOutlineColor(sf::Color::Yellow);
            box.setOutlineThickness(3.f);
        }
        else
        {
            box.setOutlineColor(sf::Color::White);
            box.setOutlineThickness(2.f);
        }
    }

    bool isMouseOver(sf::Vector2f mousePosition) const
    {
        return box.getGlobalBounds().contains(mousePosition);
    }

    void handleTextEntered(char32_t unicode)
    {
        if (!isActive)
        {
            return;
        }

        // Backspace
        if (unicode == 8)
        {
            if (!value.empty())
            {
                value.pop_back();
            }
        }
        // Normal printable characters
        else if (unicode >= 32 && unicode < 127)
        {
            if (static_cast<int>(value.size()) < characterLimit)
            {
                value += static_cast<char>(unicode);
            }
        }

        valueText.setString(value);
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(label);
        window.draw(box);
        window.draw(valueText);
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

    // These will store the final player setup data
    std::string player1Name = "";
    std::string player2Name = "";
    char player1Symbol = 'X';
    char player2Symbol = 'O';

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

    // ---------------- PLAYER SETUP SCREEN ----------------

    sf::Text setupTitle(font);
    setupTitle.setString("PLAYER SETUP");
    setupTitle.setCharacterSize(55);
    setupTitle.setFillColor(sf::Color::Cyan);
    setupTitle.setPosition({250.f, 70.f});

    TextBox player1NameBox(
        font,
        "Player 1 Name",
        {280.f, 55.f},
        {150.f, 190.f},
        12
    );

    TextBox player1SymbolBox(
        font,
        "Player 1 Symbol",
        {120.f, 55.f},
        {520.f, 190.f},
        1
    );

    TextBox player2NameBox(
        font,
        "Player 2 Name",
        {280.f, 55.f},
        {150.f, 330.f},
        12
    );

    TextBox player2SymbolBox(
        font,
        "Player 2 Symbol",
        {120.f, 55.f},
        {520.f, 330.f},
        1
    );

    sf::Text setupMessage(font);
    setupMessage.setString("");
    setupMessage.setCharacterSize(24);
    setupMessage.setFillColor(sf::Color(255, 100, 100));
    setupMessage.setPosition({150.f, 460.f});

    Button continueButton(
        font,
        "Continue",
        {220.f, 60.f},
        {220.f, 560.f},
        sf::Color(40, 160, 90),
        sf::Color(70, 210, 130),
        sf::Color::White
    );

    Button backFromSetupButton(
        font,
        "Back",
        {220.f, 60.f},
        {460.f, 560.f},
        sf::Color(90, 90, 90),
        sf::Color(130, 130, 130),
        sf::Color::White
    );

    // ---------------- TEMPORARY PLAYING SCREEN ----------------

    sf::Text playingTitle(font);
    playingTitle.setString("GAME READY");
    playingTitle.setCharacterSize(55);
    playingTitle.setFillColor(sf::Color::Cyan);
    playingTitle.setPosition({270.f, 120.f});

    sf::Text playerInfo(font);
    playerInfo.setString("");
    playerInfo.setCharacterSize(32);
    playerInfo.setFillColor(sf::Color::Yellow);
    playerInfo.setPosition({210.f, 250.f});

    Button backFromPlayingButton(
        font,
        "Back to Menu",
        {260.f, 60.f},
        {320.f, 520.f},
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
            continueButton.update(mousePosition);
            backFromSetupButton.update(mousePosition);
        }
        else if (currentScreen == ScreenState::Playing)
        {
            backFromPlayingButton.update(mousePosition);
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
                        // Select active text box
                        player1NameBox.setActive(player1NameBox.isMouseOver(clickPosition));
                        player1SymbolBox.setActive(player1SymbolBox.isMouseOver(clickPosition));
                        player2NameBox.setActive(player2NameBox.isMouseOver(clickPosition));
                        player2SymbolBox.setActive(player2SymbolBox.isMouseOver(clickPosition));

                        if (backFromSetupButton.isMouseOver(clickPosition))
                        {
                            setupMessage.setString("");
                            currentScreen = ScreenState::MainMenu;
                        }

                        if (continueButton.isMouseOver(clickPosition))
                        {
                            if (player1NameBox.value.empty() || player2NameBox.value.empty())
                            {
                                setupMessage.setString("Names cannot be empty.");
                            }
                            else if (player1SymbolBox.value.empty() || player2SymbolBox.value.empty())
                            {
                                setupMessage.setString("Symbols cannot be empty.");
                            }
                            else if (player1SymbolBox.value[0] == player2SymbolBox.value[0])
                            {
                                setupMessage.setString("Both players cannot use the same symbol.");
                            }
                            else
                            {
                                player1Name = player1NameBox.value;
                                player2Name = player2NameBox.value;
                                player1Symbol = player1SymbolBox.value[0];
                                player2Symbol = player2SymbolBox.value[0];

                                setupMessage.setString("");

                                playerInfo.setString(
                                    player1Name + " will use symbol: " + std::string(1, player1Symbol) +
                                    "\n\n" +
                                    player2Name + " will use symbol: " + std::string(1, player2Symbol)
                                );

                                currentScreen = ScreenState::Playing;
                            }
                        }
                    }
                    else if (currentScreen == ScreenState::Playing)
                    {
                        if (backFromPlayingButton.isMouseOver(clickPosition))
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

            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (currentScreen == ScreenState::PlayerSetup)
                {
                    player1NameBox.handleTextEntered(textEntered->unicode);
                    player1SymbolBox.handleTextEntered(textEntered->unicode);
                    player2NameBox.handleTextEntered(textEntered->unicode);
                    player2SymbolBox.handleTextEntered(textEntered->unicode);
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
            window.clear(sf::Color::Black);

            window.draw(setupTitle);

            player1NameBox.draw(window);
            player1SymbolBox.draw(window);
            player2NameBox.draw(window);
            player2SymbolBox.draw(window);

            window.draw(setupMessage);

            continueButton.draw(window);
            backFromSetupButton.draw(window);

            window.display();
        }
        else if (currentScreen == ScreenState::Playing)
        {
            window.clear(sf::Color::Black);

            window.draw(playingTitle);
            window.draw(playerInfo);
            backFromPlayingButton.draw(window);

            window.display();
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