#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(NULL));  // Making sure it will always be random

    // Initializing the random canvas
    int canvas[200][150];
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 150; j++) {
            canvas[i][j] = rand()%2;
        }
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game of Life");  // Setting the window up

    window.setFramerateLimit(5);  // Limiting the framerate

    while (window.isOpen()) {
        // Catching the quitting event
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);  // Filling the screen black

        int new_grid[200][150];  // Initializing the next generation grid
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 150; j++) {
                // Drawing the cell
                sf::RectangleShape rect(sf::Vector2f(4.f, 4.f));
                rect.setPosition(i*4, j*4);
                if (canvas[i][j] == 0) {
                    rect.setFillColor(sf::Color(21, 21, 21));
                } else {
                    rect.setFillColor(sf::Color(26, 72, 34));
                }
                window.draw(rect);

                // Making sure an IndexError don't occur, by making the canvas borderless
                int widthLeft, widthRight, heightTop, heightBottom;
                if (i == 0) {
                    widthLeft = 199;
                } else {
                    widthLeft = i - 1;
                }
                if (i == 199) {
                    widthRight = 0;
                } else {
                    widthRight = i + 1;
                }
                if (j == 0) {
                    heightTop = 149;
                } else {
                    heightTop = j - 1;
                }
                if (j == 149) {
                    heightBottom = 0;
                } else {
                    heightBottom = j + 1;
                }

                // Defining the neighbours
                int neighbours[8] = {
                        canvas[widthLeft][j],
                        canvas[widthLeft][heightTop],
                        canvas[widthLeft][heightBottom],
                        canvas[i][heightTop],
                        canvas[i][heightBottom],
                        canvas[widthRight][j],
                        canvas[widthRight][heightTop],
                        canvas[widthRight][heightBottom]
                };

                // Counting the alive neighbours
                int neighboursAlive = 0;
                for (int k = 0; k < 8; k++) {
                    neighboursAlive += neighbours[k];
                }

                // The main rules of the game of life
                int state = canvas[i][j];
                if (state == 0 and neighboursAlive == 3) {
                    new_grid[i][j] = 1;
                } else if (state == 1 and (neighboursAlive < 2 or neighboursAlive > 3)){
                    new_grid[i][j] = 0;
                } else {
                    new_grid[i][j] = state;
                }
            }
        }

        // Updating the canvas
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 150; j++) {
                canvas[i][j] = new_grid[i][j];
            }
        }

        window.display();  // Showing the window
    }

    return 0;
}
