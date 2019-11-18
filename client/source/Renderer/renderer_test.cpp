#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "event.hpp"
#include "renderer_abst.hpp"
#include "renderer_manager.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_renderer : public renderer_abst {
 public:
    MOCK_METHOD1(build_game_scene, int(const game_render_data data));
    MOCK_METHOD0(car_choose_menu, int());
    MOCK_METHOD0(end_game_menu, int());
    MOCK_METHOD0(lobby_scene, int());
    MOCK_METHOD0(main_menu, int());
    MOCK_METHOD0(settings_menu, int());
    MOCK_METHOD0(wait_scene, int());
};

bool operator==(const game_render_data left, const game_render_data right) {
    if (&left != &right) {
        return false;
    }
    return true;
}

TEST(renderer_manager_test, build_game_scene) {
    mock_renderer m_renderer;
    game_render_data data;

    EXPECT_CALL(m_renderer, build_game_scene(data)).Times(5);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(update_position, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(update_lap, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(race_start, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(game_start, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(update_timer, { .empty = {} })), 0);
}

TEST(renderer_manager_test, car_choose_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, car_choose_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(new_game, { .empty = {} })), 0);
}

TEST(renderer_manager_test, end_game_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, end_game_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(game_end, { .empty = {} })), 0);
}

TEST(renderer_manager_test, lobby_scene) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, lobby_scene()).Times(3);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(update_lobby_timer, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(connection_done, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(new_player_connected, { .empty = {} })), 0);
}

TEST(renderer_manager_test, main_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, main_menu()).Times(2);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(application_run, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.on_event(event(main_menu, { .empty = {} })), 0);
}

TEST(renderer_manager_test, settings_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, settings_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);

    EXPECT_EQ(renderer_mngr.on_event(event(settings_menu, { .empty = {} })), 0);
}

TEST(renderer_manager_test, wait_scene) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, wait_scene()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.on_event(event(car_chosen, { .empty = {} })), 0);
}