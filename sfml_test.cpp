#include <SFML/Graphics.hpp>
#include "Game.h"

const int WINDOW_SIZE = 600;
const int GRID_SIZE = 3;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

void drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    // Vertical lines
    line.setSize({5.f, static_cast<float>(WINDOW_SIZE)});

    line.setPosition({static_cast<float>(CELL_SIZE), 0.f});
    window.draw(line);

    line.setPosition({static_cast<float>(CELL_SIZE * 2), 0.f});
    window.draw(line);

    // Horizontal lines
    line.setSize({static_cast<float>(WINDOW_SIZE), 5.f});

    line.setPosition({0.f, static_cast<float>(CELL_SIZE)});
    window.draw(line);

    line.setPosition({0.f, static_cast<float>(CELL_SIZE * 2)});
    window.draw(line);
}

int getPositionFromMouse(int mouseX, int mouseY)
{
    int col = mouseX / CELL_SIZE;
    int row = mouseY / CELL_SIZE;

    return row * 3 + col + 1;
}

void drawX(sf::RenderWindow& window, float x, float y)
{
    sf::RectangleShape line1({140.f, 8.f});
    sf::RectangleShape line2({140.f, 8.f});

    line1.setFillColor(sf::Color::Black);
    line2.setFillColor(sf::Color::Black);

    line1.setOrigin({70.f, 4.f});
    line2.setOrigin({70.f, 4.f});

    line1.setPosition({x + 100.f, y + 100.f});
    line2.setPosition({x + 100.f, y + 100.f});

    line1.setRotation(sf::degrees(45.f));
    line2.setRotation(sf::degrees(-45.f));

    window.draw(line1);
    window.draw(line2);
}

void drawO(sf::RenderWindow& window, float x, float y)
{
    sf::CircleShape circle(65.f);

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(8.f);

    circle.setPosition({x + 35.f, y + 35.f});

    window.draw(circle);
}

void drawMarks(sf::RenderWindow& window, Game& game)
{
    Board& board = game.getBoard();

    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            char cell = board.getCell(row, col);

            float x = static_cast<float>(col * CELL_SIZE);
            float y = static_cast<float>(row * CELL_SIZE);

            if(cell == 'X')
            {
                drawX(window, x, y);
            }
            else if(cell == 'O')
            {
                drawO(window, x, y);
            }
        }
    }
}

void updateWindowTitle(sf::RenderWindow& window, Game& game)
{
    if(game.getWinner() != nullptr)
    {
        std::string title = game.getWinner()->getName();
        title += " wins!";
        window.setTitle(title);
    }
    else if(game.checkDraw())
    {
        window.setTitle("Game Draw!");
    }
    else
    {
        std::string title = game.getCurrentPlayer()->getName();
        title += "'s turn";
        window.setTitle(title);
    }
}

int main()
{
    Player player1("Player 1", 'X');
    Player player2("Player 2", 'O');

    Game game(player1, player2);

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
        "Tic Tac Toe - SFML"
    );

    updateWindowTitle(window, game);

    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if(const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if(mouseButton->button == sf::Mouse::Button::Left)
                {
                    int position = getPositionFromMouse(
                        mouseButton->position.x,
                        mouseButton->position.y
                    );

                    game.handleMove(position);
                    updateWindowTitle(window, game);
                }
            }
        }

        window.clear(sf::Color::White);

        drawGrid(window);
        drawMarks(window, game);

        window.display();
    }

    return 0;
}