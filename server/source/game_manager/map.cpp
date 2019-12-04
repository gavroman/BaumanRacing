#include "map.hpp"
#include "tinyxml2.hpp"

side_object::side_object() 
    : weight{1} 
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
            weight = 1;
            num_side_objects = 1;
            num_accelerations = 1;
            break;
        }
        case car_type::big: {
            size[0] = 3;
            size[1] = 3;
            weight = 3;
            num_side_objects = 3;
            num_accelerations = 3;
            break;
        }
        default: { // medium
            size[0] = 2;
            size[1] = 2;
            weight = 2;
            num_side_objects = 2;
            num_accelerations = 2; 
        }
    }
}

game_map::game_map(/*size_t map_id*/)
    : started{false}
{
    // finished.fill(false);
    load_map(STANDARD_MAP_PATH);
}

bool game_map::load_map(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        std::cout << "not found" << std::endl;
        return false;
    }
    tinyxml2::XMLElement* map_xml = doc.FirstChildElement("map");
    if (!map_xml) {
        return false;
    }
    size_t map_width = map_xml->IntAttribute("width", 0);
    size_t map_height = map_xml->IntAttribute("height", 0);
    --map_height; ++map_height; // for werror
    size_t block_width = map_xml->IntAttribute("tilewidth", 0);
    size_t block_height = map_xml->IntAttribute("tileheight", 0);

    tinyxml2::XMLElement* tile_xml = map_xml->FirstChildElement("layer")->FirstChildElement("data");
    std::vector<map_block> block_stripes(map_width);
    // можно ли до map_height?
    for (size_t col = 0; col < map_height; ++col) {
        for (size_t row = 0; row <  map_width; ++row) {
            tile_xml = tile_xml->NextSiblingElement("tile");
            /*if ( !() ) {
                return true;
            }*/
            map_block& block = block_stripes[row];
            block.type = static_cast<map_block::block_type>(tile_xml->IntAttribute("gid", 1));
            block.coord[0] = row * block_width;
            block.coord[1] = col * block_height;
        }
        map_info.push_back(block_stripes);
    }
    
    return true;
}

players_coord game_map::get_players_coord() {
    players_coord coord;
    for (size_t idx = 0; idx < coord.size(); ++idx) {
        coord[idx] = players[idx].coord;
    }
    return coord;
}

// TODO:
players_rating game_map::get_rating() {
    return  players_rating();   
}

std::vector<point> game_map::get_side_objects_coord() {
    std::vector<point> side_objects_coord(side_objects.size());
    for (size_t idx = 0; idx < side_objects.size(); ++idx) {
        side_objects_coord[idx] = side_objects[idx].coord;
    }
    return side_objects_coord;
}
    
void game_map::set_car(size_t id, car_type type) {
    if (started) {
        return;
    }
    players[id] = car(type);
}

void game_map::set_command(size_t id, const move_command& comm) {
    if (!started) {
        return;
    }
    command[id] = comm;
}

void game_map::make_move() {
    if (!started) {
        started = true;
    }
}
