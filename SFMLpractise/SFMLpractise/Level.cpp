#include <iostream>
#include "Level.h"
#include "Character.h"
#include "Input.h"
#include "AStar.h"

//TileSize
static const int tileSize = 30;

Level::Level(int rows, int cols) :
	levelRows(rows),
	levelCols(cols)
{
	//Create matrix
	tiles = new Tile*[levelRows];
	for (int i = 0; i < levelCols; i++) {
		tiles[i] = new Tile[levelCols];
	}
	//Initialize matrix
	for (int i = 0; i < levelRows; i++) {
		for (int j = 0; j < levelCols; j++) {
			sf::Vector2f pos((float)tileSize * i, (float)tileSize * j);
			tiles[i][j] = Tile(sf::Color::Blue, sf::Color::White, pos, tileSize);
		}
	}

	//Initialize hover
	prevTileHoveredCoord = sf::Vector2i(0, 0);

	//Initialize character
	character = new Character(tiles[0][0]);

	//Selection
	tileSelected = false;
	destinationSelected = false;
}


Level::~Level()
{
	//Delete matrix
	for (int i = 0; i < levelRows; i++) {
		delete[] tiles[i];
	}
	delete[] tiles;

	//Delete character
	delete character;
}

void Level::Update(sf::RenderWindow &window, float deltaTime) {
	
	//Get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	//Convert it to world coordinates
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	
	if (HoveringValidTile(window, worldPos)) {
		Hover(worldPos);
	}

	//Character
	character->Update(deltaTime);
}

void Level::Draw(sf::RenderWindow &window, float alphaInterp) {
	
	//Draw each tile
	for (int i = 0; i < levelRows; i++) {
		for (int j = 0; j < levelCols; j++) {
			tiles[i][j].Draw(window);
		}
	}

	//Draw character
	character->Draw(window, alphaInterp);

}

bool Level::HoveringValidTile(sf::RenderWindow &window, sf::Vector2f worldPos) {

	//Up and Left world bounds
	if (worldPos.x < 0 || worldPos.y < 0) return false;
	//Down and Right world bound
	if (worldPos.x > levelRows*tileSize || worldPos.y > levelCols*tileSize) return false;

	return true;
}

void Level::Hover(sf::Vector2f worldPos) {	
	
	//Get tile from mouse position
	tileHoveredCoord = sf::Vector2i((int)(worldPos.x / tileSize), (int)(worldPos.y / tileSize));
	//printf("tileHoveredCoord:   x: %d , y: %d \n", tileHoveredCoord.x, tileHoveredCoord.y);
		
	//If hovering new one, unhover last
	if (prevTileHoveredCoord != tileHoveredCoord) {
		
		Tile &prevHoveredTile = tiles[prevTileHoveredCoord.x][prevTileHoveredCoord.y];
		prevHoveredTile.UnmarkHover();
		prevTileHoveredCoord = tileHoveredCoord;
	}

	//Mark hovering
	Tile &hoveredTile = tiles[tileHoveredCoord.x][tileHoveredCoord.y];
	hoveredTile.MarkHover();

	//Check selection
	Select(hoveredTile);
}

void Level::Select(Tile &hoveredTile) {
	
	//hoveredTile has been marked before in Level::Hover()
	
	//Clear previous Path


	//Click
	if (Input::IsKeyPressed(Input::KEY::KEY_LCLICK)) {
		
		if (tileSelected) { //If tile previously selected undo selection of previous tile
			tiles[selectedTileOrigin.x][selectedTileOrigin.y].UnmarkClick();
			tiles[selectedTileDestination.x][selectedTileDestination.y].UnmarkClick();
		}

		//Select hovered tile as origin
		selectedTileOrigin = tileHoveredCoord;
		SelectTileOrigin(hoveredTile);

		tileSelected = true;

	}

	if (Input::IsKeyPressed(Input::KEY::KEY_RCLICK)) {
				
		//select hovered tile as destination
		if (tileSelected) {

			//Unselect previous destination
			if (destinationSelected) {
				tiles[selectedTileDestination.x][selectedTileDestination.y].UnmarkClick();
				destinationSelected = false;
			}

			selectedTileDestination = tileHoveredCoord;
			SelectTileDestination(hoveredTile);

			destinationSelected = true;
		}
	}

}

void Level::SelectTileOrigin(Tile &tile) {
	
	tile.MarkLeftClick();

}

void Level::SelectTileDestination(Tile &tile) {

	tile.MarkRightClick();

	//Calculate Path
	CalculatePath();
}

void Level::CalculatePath() {
	
	AStar::Generator generator;
	
	//Set 2d map size
	generator.setWorldSize({ levelRows, levelCols });
	//Settings
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(false);
	
	//Path
	AStar::CoordinateList path = generator.findPath({ selectedTileOrigin.x, selectedTileOrigin.y }, { selectedTileDestination.x, selectedTileDestination.y });
	//Remove duplicates
	//sort(path.begin(), path.end());
	//path.erase(unique(path.begin(), path.end()), path.end());

	//Explore path
	for (auto& coordinate : path) {
		std::cout << coordinate.x << " " << coordinate.y << "\n";

		tiles[coordinate.x][coordinate.y].MarkPath();
	}


	
}