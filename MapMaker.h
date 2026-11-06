#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>


//#include <nfd.h>
class TileMap
{
public:
	class Tile {
	public:
		std::optional<sf::Sprite> tile; // спрайт создаётся позже
		int colour = 0;
		bool isNeedUpdate = true;

		Tile() noexcept = default;

		// Создать/обновить sprite из текстуры и поставить позицию
		void updateTexture(const sf::Texture& tex) {
			if (!tile) tile.emplace(tex);      // emplace вызывает Sprite(const Texture&)
			else         tile->setTexture(tex); // обновляем существующий
			tile->setTextureRect({ {0,0},{32,32} });
			
			isNeedUpdate = false;
		}

	};

	enum TileColor : int {
		ColorNone = 0,
		ColorGrass = 1,
		ColorWater = 2,
		ColorRoad = 3,

	};
	short unsigned int NewColor = 1;
	static constexpr sf::Vector2f Tile_Size{ 32.f,32.f };
	static constexpr int m = 1;
	static constexpr int Map_Width = 60 * m;
	static constexpr int Map_Height = 38 * m;
	bool intersects(const sf::FloatRect& a, const sf::FloatRect& b);
	using MapGrid = std::vector<std::vector<Tile>>;
	MapGrid Map;

	bool isSaving = false;
	bool debugMode = false;
	bool isRoad = false;
	

public:

	TileMap();
	TileMap(std::vector<std::vector<Tile>> NewMap);
	void saveMapFile();
	void saveMap(const std::string& path);
	bool isWalkable(sf::FloatRect player);
	void openMapFile();
	sf::Texture& getTileTexture(int colour);
	void loadMap(const std::string& path);
	
	void loadTextures();
	void handleClick(sf::RenderWindow& window);
	void handlePressKey(sf::Keyboard::Key Key);
	sf::Vector2f CanMove(sf::Sprite& sprite, sf::Vector2f& moveDir);



	void drawAll(sf::RenderWindow& window, sf::View view);
private:
	std::unordered_map<int, sf::Texture> textures;
};