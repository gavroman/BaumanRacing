#include "map.hpp"
#include "tinyxml2.hpp"

side_object::side_object() 
    : mass{1} 
{
    pos.fill(0);
    size[0] = 0.5;
    size[1] = 0.5;
}

car::car(): car(car_type::medium) {}

car::car(car_type type) {
    pos.fill(0);
    switch (type) {
        case car_type::small: {
            size[0] = 100;
            size[1] = 40;
            mass = 1;
            num_side_objects = 1;
            num_accelerations = 1;
            
            speed = 0;
            max_speed = 30;
            break;
        }
        case car_type::big: {
            size[0] = 100;
            size[1] = 40;
            mass = 3;
            num_side_objects = 3;
            num_accelerations = 3;
            
            speed = 0;
            max_speed = 30;
            break;
        }
        default: { // medium
            size[0] = 100;
            size[1] = 40;
            mass = 2;
            num_side_objects = 2;
            num_accelerations = 2;
            
            speed = 0;
            max_speed = 30;
        }
    }
}

game_map::game_map() {
    num_circle.fill(-1);
    //prev_pos.fill({0, 0});
    // TODO: стартовая позиция
    load_map(STANDARD_MAP);
}

bool game_map::load_map(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        std::cout << "not found map" << std::endl;
        return false;
    }
    
    tinyxml2::XMLElement* map_xml = doc.FirstChildElement("map");
    if (!map_xml) {
        return false;
    }
    size_t map_width = map_xml->IntAttribute("width", 0);
    size_t map_height = map_xml->IntAttribute("height", 0);
    size_t block_width = map_xml->IntAttribute("tilewidth", 0);
    size_t block_height = map_xml->IntAttribute("tileheight", 0);
    
    std::cout << "map_width " << map_width << " map_height " << map_height << std::endl;

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    for (size_t col = 0; col < map_height; ++col) {
        std::vector<map_block> block_line(map_width);
        for (size_t row = 0; row <  map_width; ++row) {
            map_block& block = block_line[row];
            block.type = static_cast<map_block::block_type>(tile_xml->IntAttribute("gid", 1));
            block.coord[0] = row * block_width;
            block.coord[1] = col * block_height;
            tile_xml = tile_xml->NextSiblingElement("tile");
        }
        map_info.emplace_back(std::move(block_line));
    }
    
    return true;
}

players_position game_map::get_players_pos() const {
    players_position pos;
    for (size_t idx = 0; idx < pos.size(); ++idx) {
        pos[idx] = players[idx].pos;
    }
    return pos;
}

// TODO:
players_rating game_map::get_rating() const {
    return players_rating();   
}

std::vector<position> game_map::get_side_objects_pos() const {
    std::vector<position> pos(side_objects.size());
    for (size_t idx = 0; idx < side_objects.size(); ++idx) {
        pos[idx] = side_objects[idx].pos;
    }
    return pos;
}

int8_t game_map::get_num_circle(size_t id) const {
    return num_circle[id];
}
    
void game_map::set_car(size_t id, car_type type) {
    players[id] = car(type);
}

void game_map::set_command(size_t id, const move_command& comm) {
    command[id] = comm;
}

game_map::map_block::block_type game_map::get_pos_type(/*const position& pos*/) {
    return map_block::block_type::road; 
}

/*game_map::map_block::block_type game_map::pos_type(const position& pos) { 
    return map_block::block_type::road; 
}*/

void game_map::make_move() {
    //double h = 0.1;
    double a = 1;
    double angle = 4;
    
    //std::array<position, MAX_USERS> curr_pos = get_players_pos();
    //std::array<position, MAX_USERS> next_pos = curr_pos;
    
    // (y_{i+1} - 2 * y_{i} + y_{i-1}) / h^2 ~= a''
    
    for (size_t idx = 0; idx < MAX_USERS; ++idx) {
        car& player = players[idx];
        move_command& comm = command[idx];
        
        if (comm.back) {
            double next_speed = player.speed + a;
            player.speed = next_speed < player.max_speed ? next_speed : player.max_speed;
        } else if (comm.forward) {
            double next_speed = player.speed - a;
            player.speed = -next_speed < player.max_speed ? next_speed : -player.max_speed;
        } else {
            int8_t sign = player.speed > 1e-7 ? 1 : -1;
            player.speed -= sign * a / 2.;
        }
        
        player.pos[0] += player.speed * cos(M_PI * player.pos[2] / 180.);
        player.pos[1] += player.speed * sin(M_PI * player.pos[2] / 180.);
        
        //double v_prev_x = (curr_pos[idx][0] - prev_pos[idx][0]) / h;
        //double v_prev_y = (curr_pos[idx][1] - prev_pos[idx][1]) / h;
        
        //if (command[idx].forward) {
        //    // player.mass
       //     v_prev_x += h * a * cos(M_PI * curr_pos[idx][2] / 180.);
       //     v_prev_y += h * a * sin(M_PI * curr_pos[idx][2] / 180.);
       // }
       // if (command[idx].back) {
       //     v_prev_x -= h * a * cos(M_PI * curr_pos[idx][2] / 180.);
       //     v_prev_y -= h * a * sin(M_PI * curr_pos[idx][2] / 180.);
       // }
        //else if (v_prev < 1e-5 && command[idx].forward) || (v_prev > 1e-5 && command[idx].back) {
        //    next_pos[idx][0] = 2 * curr_pos[idx][0] - prev_pos[idx][0] - h * h * a * cos(M_PI * curr_pos[idx][2] / 180.);
        //    next_pos[idx][1] = 2 * curr_pos[idx][1] - prev_pos[idx][1] - h * h * a * sin(M_PI * curr_pos[idx][2] / 180.);
        //}
        //next_pos[idx][0] += h * v_prev_x;
        //next_pos[idx][1] += h * v_prev_y;
        
        //if (v > player.max_speed) {
        //    next_pos[idx][0] = curr_pos[idx][0] + player.max_speed * cos(M_PI * curr_pos[idx][2] / 180.);
        //    next_pos[idx][1] = curr_pos[idx][1] + player.max_speed * sin(M_PI * curr_pos[idx][2] / 180.);
        //}

        // TODO: занос
        if (command[idx].right_turn) {
            player.pos[2] += angle;
        }
        if (command[idx].left_turn) {
            player.pos[2] -= angle;
        }
        
        
        
        //player.pos = next_pos[idx];
    }
    
    //prev_pos = curr_pos;
}
