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

				if (word == "Bullet")
				{
					int value;
					while (ss >> value)
					{
						word_count++;
						switch (word_count)
						{
						case 1:
							m_bullet_config.SR = value;
							break;
						case 2:
							m_bullet_config.CR = value;
							break;
						case 3:
							m_bullet_config.S = value;
							break;
						case 4:
							m_bullet_config.FR = value;
							break;
						case 5:
							m_bullet_config.FG = value;
							break;
						case 6:
							m_bullet_config.FB = value;
							break;
						case 7:
							m_bullet_config.OR = value;
							break;
						case 8:
							m_bullet_config.OG = value;
							break;
						case 9:
							m_bullet_config.OB = value;
							break;
						case 10:
							m_bullet_config.OT = value;
							break;
						case 11:
							m_bullet_config.V = value;
							break;
						case 12:
							m_bullet_config.L = value;
							break;
						default:
							break;
						}
					}
				}
			}
			if (line_count == 5)
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

	//spawn_enemy();
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
		if(m_movement)
			s_movement();
		s_collision();
		s_render();

		m_current_frame++;
	}

	ImGui::SFML::Shutdown();
}

void Game::s_user_input()
{
	if (!player()->is_alive())
		return;

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		auto& player_input = player()->get<CInput>();
		

		if ((event.type == sf::Event::KeyPressed))
		{
			if (event.key.code == sf::Keyboard::D)
				player_input.right = true;
			
			if(event.key.code == sf::Keyboard::A)
				player_input.left = true;

			if (event.key.code == sf::Keyboard::W)
				player_input.up = true;

			if (event.key.code == sf::Keyboard::S)
				player_input.down = true;

		}
		else if((event.type == sf::Event::KeyReleased))
		{
			if (event.key.code == sf::Keyboard::D)
				player_input.right = false;

			if (event.key.code == sf::Keyboard::A)
				player_input.left = false;

			if (event.key.code == sf::Keyboard::W)
				player_input.up = false;

			if (event.key.code == sf::Keyboard::S)
				player_input.down = false;
		}


		Vec2i mouse_position = sf::Mouse::getPosition(m_window);
		if ((event.type == sf::Event::MouseButtonPressed) && event.mouseButton.button == sf::Mouse::Right)
		{
			//TO DO: if input is shoot, spawn bullet
			spawn_bullet(player(), Vec2f(mouse_position.x, mouse_position.y));
		}
		else if ((event.type == sf::Event::MouseButtonReleased) && event.mouseButton.button == sf::Mouse::Right)
		{
			//stop shooting
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

	if (ImGui::Button("Spawn Bullet"))
	{
		spawn_bullet(player(), Vec2f(1.f, 1.f));
	}

	ImGui::BeginGroup();
	ImGui::Checkbox("Movement", &m_movement);
	ImGui::EndGroup();

	auto& player_pos = player()->get<CTransform>().pos;
	ImGui::Text("Player Position: %.0f , %.0f", player_pos.x, player_pos.y);

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
	//Sets the position of all entities
	for (auto& e : m_entities.get_entities())
	{
		e->get<CShape>().get_shape().setPosition(e->get<CTransform>().pos);
	}

	if (!player()->is_alive())
		return;

	auto& player_input = player()->get<CInput>();
	auto& player_transform = player()->get<CTransform>();

	//Restrict player's movement to the window screen
	if (player_transform.pos.x - m_player_config.SR <= 0)
		player_input.left = false;
	if (player_transform.pos.x + m_player_config.SR >= m_window_config.X)
		player_input.right = false;
	if (player_transform.pos.y - m_player_config.SR <= 0)
		player_input.up = false;
	if (player_transform.pos.y + m_player_config.SR >= m_window_config.Y)
		player_input.down = false;

	//Move player
	int x_axis, y_axis = 0;
	if (player_input.left)
		x_axis = -1;
	else if (player_input.right)
		x_axis = 1;
	else if (!player_input.left || !player_input.right)
		x_axis = 0;

	if (player_input.up)
		y_axis = -1;
	else if (player_input.down)
		y_axis = 1;
	else if(!player_input.up || !player_input.down)
		y_axis = 0;

	Vec2f velocity = Vec2f(x_axis, y_axis);
	Vec2f norm_velocity = Vec2f(0.f, 0.f);

	//Normalize movement to make it the velocity uniform diagonally
	if (velocity.x != 0 || velocity.y != 0)
		norm_velocity = velocity.normalize();
	else
		norm_velocity = Vec2f(0.f, 0.f);

	player_transform.vel = norm_velocity;

	player_transform.pos.x += player_transform.vel.x * m_player_config.s;
	player_transform.pos.y += player_transform.vel.y * m_player_config.s;
		
	// Move bullets towards mouse position, mouse position being the velocity
	for (auto& b : m_entities.get_entities("bullet"))
	{
		auto& transform = b->get<CTransform>();
		//move towards mouse position
		Vec2f target_position = transform.vel - player_transform.pos;
		if (target_position.x != 0 || target_position.y != 0)
			norm_velocity = target_position.normalize();
		transform.pos.x += norm_velocity.x * m_bullet_config.S;
		transform.pos.y += norm_velocity.y * m_bullet_config.S;

	}
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
			Vec2f enemy_pos = e->get<CTransform>().pos;
			Vec2f enemy_radii{ enemy_pos.x + m_enemy_config.CR, enemy_pos.y + m_enemy_config.CR };
			Vec2f bullet_pos = b->get<CTransform>().pos;
			Vec2f bullet_radii{ bullet_pos.x + m_bullet_config.CR, bullet_pos.y + m_bullet_config.CR };
			float distance = enemy_radii.dist(bullet_radii);
			if (distance < m_enemy_config.CR + m_bullet_config.CR)
			{
				//spawn small enemies
			}
		}

		for (auto s : m_entities.get_entities("small enemy"))
		{
			// do collision logic
			Vec2f small_enemy_pos = s->get<CTransform>().pos;
			Vec2f enemy_radii{ small_enemy_pos.x + m_enemy_config.CR, small_enemy_pos.y + m_enemy_config.CR };
			Vec2f bullet_pos = b->get<CTransform>().pos;
			Vec2f bullet_radii{ bullet_pos.x + m_bullet_config.CR, bullet_pos.y + m_bullet_config.CR };
			float distance = enemy_radii.dist(bullet_radii);
			if (distance < m_enemy_config.CR + m_bullet_config.CR)
			{
				//spawn small enemies
			}
		}
	}

	if (!player()->is_alive())
		return;

	Vec2f& player_pos = player()->get<CTransform>().pos;
	for (auto e : m_entities.get_entities("enemy"))
	{
		//collision between player and enemies
		Vec2f enemy_pos = e->get<CTransform>().pos;
		Vec2f enemy_radii{ enemy_pos.x + m_enemy_config.CR, enemy_pos.y + m_enemy_config.CR };
		Vec2f player_radii = Vec2f(player_pos.x + m_player_config.CR, player_pos.y + m_player_config.CR);
		float distance = enemy_radii.dist(player_radii);
		if (distance < m_player_config.CR + m_enemy_config.CR)
		{
			//collided
			std::cout << "player collides with: " << e->tag() << e->id() << '\n';
			Vec2f screen_middle_pos{ m_window_config.X / 2, m_window_config.Y / 2 };
			player_pos = screen_middle_pos;
		}

	}
}

void Game::s_life_span()
{
	//TO DO: Implement all life span functionality
	for (auto& e : m_entities.get_entities("bullet"))
	{
		auto& lifespan = e->get<CLifespan>();
		
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
	e->add<CTransform>(screen_middle_pos, Vec2f(0.f, 0.f));

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

	//spawn bullet at entity pos
	Vec2f entity_pos = entity->get<CTransform>().pos;
	e->add<CTransform>(entity_pos, mouse_pos);

	//add Shape to entity
	e->add<CShape>(
		m_bullet_config.SR,
		m_bullet_config.V,
		sf::Color{ (sf::Uint8)m_bullet_config.FR, (sf::Uint8)m_bullet_config.FG,(sf::Uint8)m_bullet_config.FB },
		sf::Color{ (sf::Uint8)m_bullet_config.OR, (sf::Uint8)m_bullet_config.OG,(sf::Uint8)m_bullet_config.OB },
		m_bullet_config.OT
	);

	//add lifespan to entity
	e->add<CLifespan>();
}

void Game::spawn_special_weapon(std::shared_ptr<Entity> entity)
{
	// TO DO: Implement your own special weapon
}

std::shared_ptr<Entity> Game::player()
{
	return m_entities.get_entities("player").back();
}








