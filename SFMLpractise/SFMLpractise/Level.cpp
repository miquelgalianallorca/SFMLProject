#include "Level.h"
#include "Character.h"
#include "Input.h"
#include "Path.h"

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
			selectedTileDestination = tileHoveredCoord;
			SelectTileDestination(hoveredTile);
		}
	}

}

void Level::SelectTileOrigin(Tile &tile) {
	
	tile.MarkLeftClick();

}

void Level::SelectTileDestination(Tile &tile) {

	tile.MarkRightClick();

	if (path != nullptr) delete path;
	path = new Path(tiles, selectedTileOrigin, selectedTileDestination);
}