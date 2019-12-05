#include "map.hpp"
#include "tinyxml2.hpp"

side_object::side_object() 
    : mass{1} 
{
    /*coord.fill(0);*/
    size[0] = 0.5;
    size[1] = 0.5;
}

car::car(): car(car_type::medium) {}

car::car(car_type type) {
    /*coord.fill(0);
    speed.fill(0);
    direction.fill(0);*/
    switch (type) {
        case car_type::small: {
            size[0] = 1;
            size[1] = 1;
            mass = 1;
            num_side_objects = 1;
            num_accelerations = 1;
            break;
        }
        case car_type::big: {
            size[0] = 3;
            size[1] = 3;
            mass = 3;
            num_side_objects = 3;
            num_accelerations = 3;
            break;
        }
        default: { // medium
            size[0] = 2;
            size[1] = 2;
            mass = 2;
            num_side_objects = 2;
            num_accelerations = 2; 
        }
    }
}

game_map::game_map() {
    num_circle.fill(-1);
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

void game_map::make_move() {
}
