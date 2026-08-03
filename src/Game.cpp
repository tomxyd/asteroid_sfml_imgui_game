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
	unsigned int size_x, size_y, frame_rate, state;
	// TO DO: read in config file here
	//	use the premade player_config, enemy_config and bullet_config variables
	{
		//open file for reading
		std::ifstream config(config);

		if (!config.is_open())
		{
			std::cout << "Failed to load file.\n";
		}

		std::string line;
		int line_count = 0;
		while (std::getline(config, line)) // read each line
		{
			++line_count;
			std::string word;
			std::stringstream ss(line);
			int word_count = 0;
			while (ss >> word)
			{
				//read window data
				if (word == "Window")
				{
					int value;
					while (ss >> value)
					{
						word_count++;
						switch (word_count)
						{
						case 1:
							size_x = value;
							break;
						case 2:
							size_y = value;
							break;
						case 3:
							frame_rate = value;
							break;
						case 4:
							state = value;
							break;
						}
					}
				}

				if (word == "Font")
				{
					//TO DO:
					// read font data
					break;
				}

				//read player data
				if (word == "Player")
				{
					int value;
					while (ss >> value)
					{
						word_count++;
						switch (word_count)
						{
						case 1:
							m_player_config.SR = value;
							break;
						case 2:
							m_player_config.CR = value;
							break;
						case 3:
							m_player_config.s = value;
							break;
						case 4:
							m_player_config.FR = value;
						case 5:
							m_player_config.FG = value;
						case 6:
							m_player_config.FB = value;
						case 7:
							m_player_config.OR = value;
						case 8:
							m_player_config.OG = value;
						case 9:
							m_player_config.OB = value;
						case 10:
							m_player_config.OT = value;
						case 11:
							m_player_config.V = value;
						default:
							break;
						}
					}
				}
			}
			if (line_count == 3)
				break;
		}

		config.close();
	}

	ImGui::CreateContext();
	//set up default window parameters
	m_window.create(sf::VideoMode({ size_x, size_y}), "Geometry Wars", state ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(frame_rate);

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

		// System Functionality
		s_user_input();
		s_gui();
		s_movement();
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
	ImGui::EndFrame();
}

void Game::s_render()
{
	if (!m_window.isOpen()) { return; }

	m_window.clear();

	for (auto e : m_entities.get_entities())
	{
		m_window.draw(e->get<CShape>().get_shape());
	}

	ImGui::SFML::Render(m_window);

	m_window.display();
}

void Game::s_movement()
{
	// TO DO: implement all entity movement in this function
	for (auto e : m_entities.get_entities())
	{
		e->get<CShape>().get_shape().setPosition(e->get<CTransform>().pos);
	}

	//auto& transform = player()->get<CTransform>();
	//transform.pos.x += transform.vel.x;
	//transform.pos.y += transform.vel.y;

}

void Game::spawn_player()
{
	// TO DO: Finish adding all properties of the player with the correct values from the config file

	//create entity
	auto e = m_entities.add_entity("player");

	//give this entity a transform so it spawns at (200, 200)
	e->add<CTransform>(Vec2f(200.f, 200.f), Vec2f(1.f, 1.f));

	//give this entity a shape
	e->add<CShape>(static_cast<float>(
		m_player_config.SR), 
		m_player_config.V,
		sf::Color{(sf::Uint8)m_player_config.FR, (sf::Uint8)m_player_config.FG,(sf::Uint8)m_player_config.FB },
		sf::Color{(sf::Uint8)m_player_config.OR, (sf::Uint8)m_player_config.OG,(sf::Uint8)m_player_config.OB },
		m_player_config.OT
		);
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






