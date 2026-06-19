#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>
#include <memory>
#include <cctype>

#include "Game.h"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;

const int BOARD_SIZE = 540;
const int CELL_SIZE = BOARD_SIZE / 3;
const int BOARD_LEFT = (WINDOW_WIDTH - BOARD_SIZE) / 2;
const int BOARD_TOP = 105;

enum class ScreenState
{
    MainMenu,
    Rules,
    PlayerSetup,
    Playing,
    ExitScreen
};

bool isBlank(const std::string& text)
{
    for (char ch : text)
    {
        if (!std::isspace(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    return true;
}

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

        if (unicode == 8)
        {
            if (!value.empty())
            {
                value.pop_back();
            }
        }
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

void drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::White);

    line.setSize({5.f, static_cast<float>(BOARD_SIZE)});

    line.setPosition({static_cast<float>(BOARD_LEFT + CELL_SIZE), static_cast<float>(BOARD_TOP)});
    window.draw(line);

    line.setPosition({static_cast<float>(BOARD_LEFT + CELL_SIZE * 2), static_cast<float>(BOARD_TOP)});
    window.draw(line);

    line.setSize({static_cast<float>(BOARD_SIZE), 5.f});

    line.setPosition({static_cast<float>(BOARD_LEFT), static_cast<float>(BOARD_TOP + CELL_SIZE)});
    window.draw(line);

    line.setPosition({static_cast<float>(BOARD_LEFT), static_cast<float>(BOARD_TOP + CELL_SIZE * 2)});
    window.draw(line);

    sf::RectangleShape border;
    border.setSize({static_cast<float>(BOARD_SIZE), static_cast<float>(BOARD_SIZE)});
    border.setPosition({static_cast<float>(BOARD_LEFT), static_cast<float>(BOARD_TOP)});
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(4.f);
    window.draw(border);
}

int getPositionFromMouse(int mouseX, int mouseY)
{
    if (
        mouseX < BOARD_LEFT ||
        mouseX >= BOARD_LEFT + BOARD_SIZE ||
        mouseY < BOARD_TOP ||
        mouseY >= BOARD_TOP + BOARD_SIZE
    )
    {
        return -1;
    }

    int col = (mouseX - BOARD_LEFT) / CELL_SIZE;
    int row = (mouseY - BOARD_TOP) / CELL_SIZE;

    return row * 3 + col + 1;
}

void drawMarks(
    sf::RenderWindow& window,
    Game& game,
    const sf::Font& font,
    char player1Symbol,
    char player2Symbol
)
{
    Board& board = game.getBoard();

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            char cell = board.getCell(row, col);

            if (cell == ' ')
            {
                continue;
            }

            sf::Text mark(font);
            mark.setString(std::string(1, cell));
            mark.setCharacterSize(135);

            if (cell == player1Symbol)
            {
                mark.setFillColor(sf::Color::Red);
            }
            else if (cell == player2Symbol)
            {
                mark.setFillColor(sf::Color::Blue);
            }
            else
            {
                mark.setFillColor(sf::Color::White);
            }

            sf::FloatRect bounds = mark.getLocalBounds();

            mark.setOrigin({
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            });

            float centerX = static_cast<float>(BOARD_LEFT + col * CELL_SIZE + CELL_SIZE / 2);
            float centerY = static_cast<float>(BOARD_TOP + row * CELL_SIZE + CELL_SIZE / 2);

            mark.setPosition({centerX, centerY - 8.f});

            window.draw(mark);
        }
    }
}

void updateStatusText(sf::Text& statusText, Game& game)
{
    if (game.getWinner() != nullptr)
    {
        statusText.setString(game.getWinner()->getName() + " wins!");
        statusText.setFillColor(sf::Color::Green);
    }
    else if (game.checkDraw())
    {
        statusText.setString("It is a draw!");
        statusText.setFillColor(sf::Color::Yellow);
    }
    else
    {
        statusText.setString(
            game.getCurrentPlayer()->getName() +
            "'s turn (" +
            std::string(1, game.getCurrentPlayer()->getSymbol()) +
            ")"
        );
        statusText.setFillColor(sf::Color::Cyan);
    }
}

void drawInstructionPopup(
    sf::RenderWindow& window,
    sf::Text& popupTitle,
    sf::Text& popupText,
    Button& okButton
)
{
    sf::RectangleShape overlay;
    overlay.setSize({static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)});
    overlay.setPosition({0.f, 0.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    sf::RectangleShape popup;
    popup.setSize({620.f, 420.f});
    popup.setPosition({140.f, 140.f});
    popup.setFillColor(sf::Color(25, 25, 25));
    popup.setOutlineColor(sf::Color::Cyan);
    popup.setOutlineThickness(3.f);
    window.draw(popup);

    window.draw(popupTitle);
    window.draw(popupText);
    okButton.draw(window);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Tic Tac Toe"
    );

    sf::Font font;

    if (!font.openFromFile("assets/fonts/font.ttf"))
    {
        std::cout << "Font failed to load!" << std::endl;
        return -1;
    }

    ScreenState currentScreen = ScreenState::MainMenu;

    std::string player1Name = "";
    std::string player2Name = "";
    char player1Symbol = 'X';
    char player2Symbol = 'O';

    std::unique_ptr<Game> game = nullptr;
    bool showInstructions = true;

    sf::Text title(font);
    title.setString("TIC TAC TOE");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition({250.f, 90.f});

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

    sf::Text statusText(font);
    statusText.setString("");
    statusText.setCharacterSize(34);
    statusText.setFillColor(sf::Color::Cyan);
    statusText.setPosition({260.f, 35.f});

    Button backFromPlayingButton(
        font,
        "Menu",
        {150.f, 50.f},
        {25.f, 25.f},
        sf::Color(90, 90, 90),
        sf::Color(130, 130, 130),
        sf::Color::White
    );

    sf::Text popupTitle(font);
popupTitle.setString("INSTRUCTIONS");
popupTitle.setCharacterSize(42);
popupTitle.setFillColor(sf::Color::Cyan);
popupTitle.setPosition({285.f, 170.f});

sf::Text popupText(font);
popupText.setString(
    "Click any empty cell to place your symbol.\n\n"
    "Player 1 symbol will appear in red.\n"
    "Player 2 symbol will appear in blue.\n\n"
    "First player to make 3 in a row wins."
);
popupText.setCharacterSize(24);
popupText.setFillColor(sf::Color::White);
popupText.setPosition({190.f, 250.f});

Button okInstructionButton(
    font,
    "OK",
    {160.f, 55.f},
    {370.f, 485.f},
    sf::Color(40, 160, 90),
    sf::Color(70, 210, 130),
    sf::Color::White
);

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

    while (window.isOpen())
    {
        sf::Vector2f mousePosition =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));

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

            if (showInstructions)
            {
                okInstructionButton.update(mousePosition);
            }
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
                            if (isBlank(player1NameBox.value) || isBlank(player2NameBox.value))
                            {
                                setupMessage.setString("Names cannot be empty.");
                            }
                            else if (player1SymbolBox.value.empty() || player2SymbolBox.value.empty())
                            {
                                setupMessage.setString("Symbols cannot be empty.");
                            }
                            else if (
                                std::isspace(static_cast<unsigned char>(player1SymbolBox.value[0])) ||
                                std::isspace(static_cast<unsigned char>(player2SymbolBox.value[0]))
                            )
                            {
                                setupMessage.setString("Symbols cannot be spaces.");
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

                                Player p1(player1Name, player1Symbol);
                                Player p2(player2Name, player2Symbol);

                                game = std::make_unique<Game>(p1, p2);

                                setupMessage.setString("");
                                showInstructions = true;
                                updateStatusText(statusText, *game);

                                currentScreen = ScreenState::Playing;
                            }
                        }
                    }
                    else if (currentScreen == ScreenState::Playing)
                    {
                        if (backFromPlayingButton.isMouseOver(clickPosition))
                        {
                            game.reset();
                            currentScreen = ScreenState::MainMenu;
                        }
                        else if (showInstructions)
                        {
                            if (okInstructionButton.isMouseOver(clickPosition))
                            {
                                showInstructions = false;
                            }
                        }
                        else if (game != nullptr && !game->isGameOver())
                        {
                            int position = getPositionFromMouse(
                                mouseButton->position.x,
                                mouseButton->position.y
                            );

                            if (position != -1)
                            {
                                game->handleMove(position);
                                updateStatusText(statusText, *game);
                            }
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

            if (game != nullptr)
            {
                window.draw(statusText);
                backFromPlayingButton.draw(window);

                drawGrid(window);
                drawMarks(window, *game, font, player1Symbol, player2Symbol);

                if (showInstructions)
                {
                    drawInstructionPopup(
                        window,
                        popupTitle,
                        popupText,
                        okInstructionButton
                    );
                }
            }

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