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

void Game::read_window_data(std::stringstream& ss)
{
	int value;
	int word_count = 0;
	while (ss >> value)
	{
		word_count++;
		switch (word_count)
		{
		case 1:
			m_window_config.X = value;
			break;
		case 2:
			m_window_config.Y = value;
			break;
		case 3:
			m_window_config.FR = value;
			break;
		case 4:
			m_window_config.S = value;
			break;
		}
	}
}

void Game::init(const std::string& config)
{
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
					read_window_data(ss);
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

				//read player data
				if (word == "Enemy")
				{
					int value;
					while (ss >> value)
					{
						word_count++;
						switch (word_count)
						{
						case 1:
							m_enemy_config.SR = value;
							break;
						case 2:
							m_enemy_config.CR = value;
							break;
						case 3:
							m_enemy_config.S_MIN = value;
							break;
						case 4:
							m_enemy_config.S_MAX = value;
							break;
						case 5:
							m_enemy_config.OR = value;
							break;
						case 6:
							m_enemy_config.OG = value;
							break;
						case 7:
							m_enemy_config.OB = value;
							break;
						case 8:
							m_enemy_config.OT = value;
							break;
						case 9:
							m_enemy_config.V_MIN = value;
							break;
						case 10:
							m_enemy_config.V_MAX = value;
							break;
						case 11:
							m_enemy_config.L = value;
							break;
						case 12:
							m_enemy_config.SI = value;
							break;
						default:
							break;
						}
					}
				}
			}
			if (line_count == 4)
				break;
		}

		config.close();
	}

	ImGui::CreateContext();
	//set up default window parameters
	m_window.create(sf::VideoMode({ (sf::Uint16)m_window_config.X, (sf::Uint16)m_window_config.Y }), "Geometry Wars", m_window_config.S ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(m_window_config.FR);

	if (!ImGui::SFML::Init(m_window))
	{
	}

	//scales the font and ui by a multiple of 2
	//ImGui::GetStyle().ScaleAllSizes(2.0f);
	//ImGui::GetIO().FontGlobalScale = 2.0f;

	spawn_player();

	spawn_enemy();
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

		if ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::W)
		{
			std::cout << "W key pressed\n";
		}


		Vec2i mouse_position = sf::Mouse::getPosition(m_window);
		if ((event.type == sf::Event::MouseButtonPressed) && event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Left mouse key pressed\n";
			std::cout << "at location: " << mouse_position.x << ", " << mouse_position.y << '\n';
		}
	}
}

void Game::s_gui()
{
	ImGui::Begin("Geometry Wars");
	if (ImGui::Button("Spawn Enemy"))
	{
		spawn_enemy();
	};
	ImGui::End();
	ImGui::EndFrame();
}

void Game::s_render()
{
	if (!m_window.isOpen()) { return; }

	m_window.clear();

	for (auto& e : m_entities.get_entities())
	{
		m_window.draw(e->get<CShape>().get_shape());
	}

	ImGui::SFML::Render(m_window);

	m_window.display();
}

void Game::s_movement()
{
	// TO DO: implement all entity movement in this function
	for (auto& e : m_entities.get_entities())
	{
		e->get<CShape>().get_shape().setPosition(e->get<CTransform>().pos);
	}

	//auto& transform = player()->get<CTransform>();
	//transform.pos.x += transform.vel.x;
	//transform.pos.y += transform.vel.y;

}

void Game::s_collision()
{
	// TO DO: Implement all proper collisions between entities
	// be sure to use collision radius and not shape radius

	for (auto b : m_entities.get_entities("bullet"))
	{
		for (auto e : m_entities.get_entities("enemy"))
		{
			// do collision logic
		}

		for (auto s : m_entities.get_entities("small enemy"))
		{
			// do collision logic
		}
	}
}

void Game::s_enemy_spawner()
{

}

void Game::spawn_player()
{
	// TO DO: Finish adding all properties of the player with the correct values from the config file

	//create entity
	auto e = m_entities.add_entity("player");

	//give this entity a transform so it spawns at middle of the screen
	Vec2f screen_middle_pos{ m_window_config.X / 2, m_window_config.Y / 2 };
	e->add<CTransform>(screen_middle_pos, Vec2f(1.f, 1.f));

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
	// TO DO: make sure the enemy is spawned properly with its config variables and within bounds of the screen window

	//create entity
	auto e = m_entities.add_entity("enemy");

	//give entity a transform
	std::uniform_int_distribution<int> posX(0, m_window_config.X);
	std::uniform_int_distribution<int> posY(0, m_window_config.Y);

	Vec2f random_pos{ static_cast<float>(posX(rd)), static_cast<float>(posY(rd)) };
	e->add<CTransform>(random_pos, Vec2f(1.f, 1.f));
	// - provide a random range of position within the bounds of the window

	//give entity a shape
	// pick a number between VMIN and VMAX
	std::uniform_int_distribution<int> dist(m_enemy_config.V_MIN, m_enemy_config.V_MAX);
	int vertices = dist(rd);
	e->add<CShape>(static_cast<float>(
		m_enemy_config.SR),
		vertices,
		sf::Color{0,0,0},
		sf::Color{ (sf::Uint8)m_enemy_config.OR, (sf::Uint8)m_enemy_config.OG,(sf::Uint8)m_enemy_config.OB },
		m_enemy_config.OT
	);


	/// \TO DO: give entity life span component

	m_last_enemy_spawn_time = m_current_frame;
}

void Game::spawn_small_enemies(std::shared_ptr<Entity> entity)
{
	// TO DO: spawn small enemies at the location of the input enemy e

	// When we create the smaller enemy, we have to read the values of the original enemy
	// - spawn a number of small enemies equal to the vertices of the enemy
	//  - set each small enemy to the same color as the original, and half the size
	// - small enemies are worth double the score of original enemies
}

void Game::spawn_bullet(std::shared_ptr<Entity> entity, const Vec2f& mouse_pos)
{
	//create entity
	auto e = m_entities.add_entity("bullet");
}

void Game::spawn_special_weapon(std::shared_ptr<Entity> entity)
{
	// TO DO: Implement your own special weapon
}

void Game::s_life_span()
{
	//TO DO: Implement all life span functionality
}

std::shared_ptr<Entity> Game::player()
{
	return m_entities.get_entities("player").back();
}






