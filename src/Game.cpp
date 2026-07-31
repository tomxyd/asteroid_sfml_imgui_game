#include "Game.h"

Game::Game(const std::string& config)
	: m_text("Default", m_font, 24)
{
	init(config);
}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

void Game::init(const std::string& config)
{
	// TO DO: read in config file here
	//	use the premade player_config, enemy_config and bullet_config variables

	ImGui::CreateContext();
	//set up default window parameters
	m_window.create(sf::VideoMode({ 1280, 720 }), "Geometry Wars");
	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(60);

	if (!ImGui::SFML::Init(m_window))
	{
	}

	//scales the font and ui by a multiple of 2
	//ImGui::GetStyle().ScaleAllSizes(2.0f);
	//ImGui::GetIO().FontGlobalScale = 2.0f;

	spawn_player();
}


void Game::run()
{
	// TO DO: add pause functionality here

	while (true)
	{
		m_entities.update();

		ImGui::SFML::Update(m_window, m_delta_clock.restart());

		s_user_input();
		s_gui();
		s_render();

		m_current_frame++;
	}

	ImGui::SFML::Shutdown();

}

void Game::s_user_input()
{
	//TO DO: handle user input here
	// 

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::s_gui()
{
	ImGui::Begin("Geometry Wars");
	ImGui::Button("Look at this pretty button");
	ImGui::End();
}

void Game::s_render()
{
	if (!m_window.isOpen()) { return; }

	//TO DO: change the code below to draw ALL of the entities
	m_window.clear();

	ImGui::SFML::Render(m_window);

	m_window.display();
}


void Game::spawn_player()
{
	// TO DO: Finish adding all properties of the player with the correct values from the config file

	//create entity
	auto e = m_entities.add_entity("player");

	//give this entity a transform so it spawns at (200, 200)
	e->add<CTransform>(Vec2f(200.f, 200.f), Vec2f(1.f, 1.f));

	//give this entity a shape

	//give the entity an input
	e->add<CInput>();
}

void Game::spawn_enemy()
{
	// TO DO: make sure the enemy is spawned properly with its config variables

	m_last_enemy_spawn_time = m_current_frame;
}

std::shared_ptr<Entity> Game::player()
{
	return m_entities.get_entities("player").back();
}

void Game::s_movement()
{
	// TO DO: implement all entity movement in this function

	auto& transform = player()->get<CTransform>();
	transform.pos.x += transform.vel.x;
	transform.pos.y += transform.vel.y;

}





