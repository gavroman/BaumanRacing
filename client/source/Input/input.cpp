#include "input.hpp"

input::input(sf::RenderWindow *win) {
    window = win;
}

void input::game() {
    game_start = true;
}

void input::end_game() {
    game_start = false;
}

struct keys_pressed_variants input::get_pressed_keys() {
    if (!game_start)
        keys = { };

    sf::Event event = sf::Event();
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                keys.closing = true;
                break;
            }
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        keys.keys.up = true;
                        break;
                    case sf::Keyboard::Down:
                        keys.keys.down = true;
                        break;
                    case sf::Keyboard::Left:
                        keys.keys.left = true;
                        break;
                    case sf::Keyboard::Right:
                        keys.keys.right = true;
                        break;
                    case sf::Keyboard::Return:
                        keys.keys.enter = true;
                        break;
                    case sf::Keyboard::Escape:
                        keys.keys.esc = true;
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        keys.keys.up = false;
                        break;
                    case sf::Keyboard::Down:
                        keys.keys.down = false;
                        break;
                    case sf::Keyboard::Left:
                        keys.keys.left = false;
                        break;
                    case sf::Keyboard::Right:
                        keys.keys.right = false;
                        break;
                    case sf::Keyboard::Return:
                        keys.keys.enter = false;
                        break;
                    case sf::Keyboard::Escape:
                        keys.keys.esc = false;
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::TextEntered: {
                if (event.text.unicode < 128)
                    keys.player_input += event.text.unicode;
                   //std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                break;
            }
            default:
                break;
        }
    }

    return keys;
}

void input::start_control() {
}

void input::end_control() {
}
