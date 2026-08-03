#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <fstream>
#include <sstream>
#include <string>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float s; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, V_MIN, V_MAX, L, SI; float S_MIN, S_MAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };


class Game
{
private:
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text; //the score text will be drawn to the screen
	PlayerConfig m_player_config;
	EnemyConfig m_enemy_config;
	BulletConfig m_bullet_config;
	sf::Clock m_delta_clock;
	int m_score = 0;
	int m_current_frame = 0;
	int m_last_enemy_spawn_time = 0;
	bool m_paused;
	bool m_running;

	void init(const std::string& config); // initialize the game state with a config file
public:
	Game(const std::string& config);
	~Game();
	void run();
	void set_paused(bool paused); // pause the game

	void s_movement();
	void s_user_input();
	void s_life_span();
	void s_render();
	void s_gui();
	void s_enemy_spawner();
	void s_collision();


	void spawn_player();
	void spawn_enemy();
	void spawn_small_enemies(std::shared_ptr<Entity> entity);
	void spawn_bullet(std::shared_ptr<Entity> entity, const Vec2f& mouse_pos);
	void spawn_special_weapon();

	std::shared_ptr<Entity> player();

};