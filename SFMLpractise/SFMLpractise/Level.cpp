#include "Level.h"
#include "Character.h"

//TileSize
static const int tileSize = 30;

Level::Level(int rows, int cols) :
	levelRows(rows),
	levelCols(cols)
{
	//Initialize matrix
	InitMatrix();

	//Initialize hover
	prevTileHoveredCoord = sf::Vector2i(0, 0);

	//Initialize character
	character = new Character(tiles[0][0]);

	//Selection
	tileSelected = false;
	destinationSelected = false;
}

void Level::InitMatrix() {
	
	//Create matrix
	tiles = new Tile*[levelRows];
	for (int i = 0; i < levelRows; i++) {
		tiles[i] = new Tile[levelCols];
	}
	
	//Initialize matrix
	for (int i = 0; i < levelRows; i++) {
		for (int j = 0; j < levelCols; j++) {
			CreateTile(i, j);
		}
	}
}

void Level::CreateTile(int i, int j) {
	sf::Vector2f pos((float)tileSize * i, (float)tileSize * j);
	tiles[i][j] = Tile(sf::Color::Blue, sf::Color::White, pos, tileSize);

	//Random float between 0.0 and 1.0
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//if (r < waterChance) {
	//	tiles[i][j] = Tile(sf::Color::Blue, sf::Color::White, pos, tileSize);
	//	//tiles[i][j] = WaterTile();
	//}
	//else {
	//	if (r < waterChance + rockChance) {
	//		tiles[i][j] = Tile(sf::Color::Blue, sf::Color::White, pos, tileSize);
	//		//tiles[i][j] = RockTile();
	//	}
	//	else {
	//		tiles[i][j] = GroundTile(sf::Color::Blue, sf::Color::White, pos, tileSize);
	//	}
	//}

}

Level::~Level()
{
	hoveredTile = nullptr;
	delete hoveredTile;

	//Delete matrix
	for (int i = 0; i < levelRows; i++) {
		delete[] tiles[i];
	}
	delete[] tiles;

	//Delete character
	delete character;
}


void Level::HandleEvent(sf::Event &event) {

	//Mouse events
	if (event.type == sf::Event::MouseButtonPressed) {

		if (hoveredTile != nullptr) {

			//Left click
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (tileSelected) { //If tile previously selected undo selection of previous tile
					tiles[selectedTileOrigin.x][selectedTileOrigin.y].UnmarkClick();
					tiles[selectedTileDestination.x][selectedTileDestination.y].UnmarkClick();

					CleanPath();
				}

				//Select hovered tile as origin
				selectedTileOrigin = tileHoveredCoord;
				SelectTileOrigin(hoveredTile);

				tileSelected = true;

			}

			//Right click
			else if (event.mouseButton.button == sf::Mouse::Right) {
				//select hovered tile as destination
				if (tileSelected) {

					//Unselect previous destination
					if (destinationSelected) {
						tiles[selectedTileDestination.x][selectedTileDestination.y].UnmarkClick();
						destinationSelected = false;

						CleanPath(); //Clean previous path
					}

					selectedTileDestination = tileHoveredCoord;
					SelectTileDestination(hoveredTile);

					destinationSelected = true;
				}
			}

		}
	}

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
	hoveredTile = &tiles[tileHoveredCoord.x][tileHoveredCoord.y];
	hoveredTile->MarkHover();

}


void Level::SelectTileOrigin(Tile *tile) {

	tile->MarkLeftClick();

}

void Level::SelectTileDestination(Tile *tile) {

	tile->MarkRightClick();

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
	path = generator.findPath({ selectedTileOrigin.x, selectedTileOrigin.y }, { selectedTileDestination.x, selectedTileDestination.y });
	
	//Mark Path
	for (auto& coordinate : path) {
		//std::cout << "MARKING: " << coordinate.x << " " << coordinate.y << "\n";
		tiles[coordinate.x][coordinate.y].MarkPath();
	}
	
}

void Level::CleanPath() {
	
	if (!path.empty()) {
		for (auto& coordinate : path) {
			//std::cout << "CLEANING: " << coordinate.x << " " << coordinate.y << "\n";
			tiles[coordinate.x][coordinate.y].UnmarkPath();
		}
		path.clear();
	}

}

float Level::GetWorldLimit(bool horizontal) {
	if (horizontal) return levelRows * tileSize; //Horizontal limit
	else return levelCols * tileSize; //Vertical limit
}