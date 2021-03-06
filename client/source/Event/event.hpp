#ifndef EVENT_H_
#define EVENT_H_

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

#include "config.hpp"

const size_t MAX_USERS = 4;

enum event_type {
    application_run,
    main_menu,
    connect_to_open,
    create_room,
    connect_to_room,
    connect_join,
    new_game,
    name_choose,
    name_chosen,
    waiting,
    settings_menu,
    show_car,
    car_chosen,
    connection_done,
    send_car_info,
    new_player_connected,
    update_lobby_timer,
    game_start,
    update_timer,
    race_start,
    update_lap,
    update_rating,
    update_position,
    game_end,
    key_pressed,
    closing,
    nothing_keys,
    nothing_recieve,
    mouse_click,
    textures_loaded, // throw it to get all textures
    key_pressed_menu,
    input_ev,
    connect_create,
    users,
    bad_name
};

struct player_id {
    int id;
};

struct player_info {
    size_t player_id;
    size_t car_id;
};

struct players_info {
    std::array<player_info, MAX_USERS> player;
};

struct lobby_timer_event {
    int time;
};

struct start_game_timer_event {
    size_t time;
};

struct player_position_info {
    double x;
    double y;
    double angle;
};

struct players_positions_info {
    std::array<player_position_info, MAX_USERS> player;
};

struct keys_pressed {
    bool up;
    bool down;
    bool left;
    bool right;
    bool enter;
    bool esc;
};

struct keys_pressed_variants {
    struct keys_pressed keys;
    bool closing;
    std::string player_input;
};

struct input_data {
    char str[256];
};

struct input_data2 {
    char str[256];
    int box;
};

struct lap_event {
    size_t lap;
};

struct players_rating_event {
    size_t player_1;
    size_t player_2;
    size_t player_3;
    size_t player_4;
};

struct game_results_event {
    bool win;
};

struct empty_event {};

struct textures_loaded_event {
    std::array<sf::Texture*, CARS_TEXTURES_NUMBER> players;
    std::array<sf::Music*, 2> soundtracks;
    sf::Texture* map;
    sf::Texture* logo;
    sf::Texture* box;
    sf::Texture* arrow;
    sf::Font* main_font;
};

struct game_end_event {
    int position;
};

struct info_select {
    size_t select;
};

union event_data {
    player_id                id;
    players_info             players;
    player_info              player;
    lobby_timer_event        lobby_timer;
    start_game_timer_event   start_game_timer;
    players_positions_info   players_positions;
    player_position_info     player_position;
    keys_pressed             keys;
    lap_event                lap;
    players_rating_event     players_rating;
    game_results_event       game_results;
    empty_event              empty;
    textures_loaded_event    textures;
    info_select              box;
    input_data               input_ev;
    input_data2               input_ev2;
    game_end_event           game_end;
};

class event {
 public:
    event() = default;
    event(event_type, event_data);
    event_type type;
    event_data data;
};

#endif  //  EVENT_H_
