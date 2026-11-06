#include "MapMaker.h"

TileMap::TileMap() {
    loadTextures();

    Map.resize(Map_Height, std::vector<Tile>(Map_Width));

    for (int y = 0; y < Map_Height; ++y) {
        for (int x = 0; x < Map_Width; ++x) {
            Tile& Tile = Map[y][x];
            
            Tile.colour = ColorGrass;
            Tile.updateTexture(getTileTexture(Tile.colour)); 
            
            Tile.tile->setPosition({ x * Tile_Size.x, y * Tile_Size.y });
        }
    }

}

TileMap::TileMap(std::vector<std::vector<Tile>> NewMap) {
    Map = std::move(NewMap);
}
void TileMap::loadTextures() {
    
    sf::Texture Grass;
    sf::Texture Water;
    sf::Texture Error;
    sf::Texture Void;
    sf::Texture Road;
    if (!Grass.loadFromFile("assets/TileTextures/Grass.png")) {
        std::cerr << "Failed to load Grass texture\n";
    }
    textures[ColorGrass] = std::move(Grass);

    if (!Water.loadFromFile("assets/TileTextures/Water.png")) {
        std::cerr << "Failed to load Water texture\n";
    }
    textures[ColorWater] = std::move(Water);

    if (!Void.loadFromFile("assets/TileTextures/Void.png")) {
        std::cerr << "Failed to load Void texture\n";
    }
    textures[ColorNone] = std::move(Void);
    if (!Road.loadFromFile("assets/TileTextures/Road.png")) {
        std::cerr << "Failed to load Road texture\n";
    }
    textures[ColorRoad] = std::move(Road);

    if (!Error.loadFromFile("assets/TileTextures/Error.png")) {
        std::cerr << "HOW? WHERE THE ONE THAT IS NEEDED EVERYTIME?\n";
    }
    textures[-1] = std::move(Error);
}
sf::Texture& TileMap::getTileTexture(int Colour) {
    auto Texture = textures.find(Colour);
    if (Texture != textures.end()) {
        return Texture->second;
    }
    return textures[-1];
    
}
void TileMap::openMapFile() {
    NFD_Init();

    nfdu8char_t* outPath;
    nfdu8filteritem_t filters[1] = { { "Map", "txt" }};
    nfdopendialogu8args_t args = { 0 };
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {   
        puts("Success!");
        puts(outPath);
    
        loadMap(outPath);
        NFD_FreePathU8(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    return ;
}
void TileMap::loadMap(const std::string& path) {
    Map.clear();
    std::ifstream LoadFile(path);
    if (!LoadFile.is_open()) {
        std::cerr << "Cannot open for Loading\n";
        return;
    }
    Map.resize(Map_Height);
    for (int y = 0; y < Map_Height; y++) {
        Map[y].resize(Map_Width); 

        std::string line;
        if (!std::getline(LoadFile, line)) {
            std::cerr << "Not enough lines in map file\n";
            return;
        }

        std::istringstream converter(line);
        for (int x = 0; x < Map_Width; x++) {
            if (!(converter >> Map[y][x].colour)) {
                std::cerr << "Invalid data at row " << y << ", col " << x << "\n";
                return;
            }
        }
    }

}

void TileMap::saveMapFile() {
    NFD_Init();

    nfdu8char_t* outPath;
    nfdu8filteritem_t filters[1] = { { "Map", "txt" } };
    nfdsavedialogu8args_t args = { 0 };
    args.filterList = filters;
    args.filterCount = 1;

    nfdresult_t result = NFD_SaveDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {

        saveMap(outPath);  
        NFD_FreePathU8(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
}
void TileMap::saveMap(const std::string& path) {
    std::ofstream SaveFile(path);
    if (!SaveFile.is_open()) {
        std::cerr << "Cannot open for Saving\n";
        return;
    }

    for (const auto& row : Map) {
        for (size_t i = 0; i < row.size(); ++i) {
            SaveFile << row[i].colour;
            if (i + 1 < row.size()) SaveFile << ' ';
        }
        SaveFile << '\n';
    }

    std::cout << "Map saved to: " << path << "\n";
}

void TileMap::handlePressKey(sf::Keyboard::Key Key) {

    if (Key == sf::Keyboard::Key::F) {
        for (int y = 0; y < Map_Height; y++) {
            for (int x = 0; x < Map_Width; x++) {
                std::cout << Map[y][x].colour << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    if (Key == sf::Keyboard::Key::Num1) {
        NewColor = ColorGrass;
    }
    if (Key == sf::Keyboard::Key::Num2) {
        NewColor = ColorWater;
    }
    if (Key == sf::Keyboard::Key::Num3) {
        NewColor = ColorNone;
    }
    if (Key == sf::Keyboard::Key::Num4) {
        NewColor = ColorRoad;
    }
    if (Key == sf::Keyboard::Key::K) {
        saveMapFile();
        
    }
    if (Key == sf::Keyboard::Key::L) {
        openMapFile();
    }
    if (Key == sf::Keyboard::Key::Tab) {
        debugMode = !debugMode;
    }
}
void TileMap::handleClick(sf::RenderWindow& window) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) {

            sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window); // позиция мышки на экране
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos);


            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int mouseX = (int)worldPos.x;
            int mouseY = (int)worldPos.y;

                int tileX = mouseX / Tile_Size.x;   
                int tileY = mouseY / Tile_Size.y;

            if (tileX >= 0 && tileX < Map_Width &&
                tileY >= 0 && tileY < Map_Height)
            {


                if (Map[tileY][tileX].colour != NewColor) {
                    Map[tileY][tileX].isNeedUpdate = true;
                   
                    Map[tileY][tileX].colour = NewColor;
                    
                    std::cout << "helo ";
                }
                
            
                }
            }
        
 }
bool TileMap::isWalkable(sf::FloatRect playerBound) {
   
    if (playerBound.position.x < 0 || playerBound.position.y < 0 || playerBound.position.y + playerBound.size.x >= (int)Map.size()*32 || playerBound.position.x+playerBound.size.x >= (int)Map[0].size()*32) {
        isRoad = false;
        return false;
    }
    int startX = std::max(0, (int)(playerBound.position.x / Tile_Size.x));
    int endX = std::min((int)Map[0].size(), (int)((playerBound.position.x + playerBound.size.x) / Tile_Size.x));
    int startY = std::max(0, (int)(playerBound.position.y / Tile_Size.y));
    int endY = std::min((int)Map.size(), (int)((playerBound.position.y + playerBound.size.y) / Tile_Size.y));
    bool roadTouch = false;

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            sf::FloatRect tileBounds = Map[y][x].tile->getGlobalBounds();

           
            if (intersects(playerBound, tileBounds)) {
                if (Map[y][x].colour == ColorRoad) {
                    isRoad = true;
                    roadTouch = true;
					
                }
                else if (Map[y][x].colour == ColorNone || Map[y][x].colour == ColorWater) {
                    
                    return false;
                }
            }
        }
    }
    if (roadTouch) {
        isRoad = true;

    }else{
        isRoad = false;
	}
  
    return true;
   
}
void TileMap::drawAll(sf::RenderWindow& window, sf::View view) {
    
    sf::Vector2i pos = (sf::Vector2i)view.getSize();
    sf::Vector2i minCoord = (sf::Vector2i)view.getCenter();
    minCoord.x = (minCoord.x - pos.x / 2) / (int)Tile_Size.x;
    minCoord.y = (minCoord.y - pos.y / 2) / (int)Tile_Size.y;
    pos.x = pos.x / Tile_Size.x+2;
    pos.y = pos.y / Tile_Size.y+2;
    
    int startX = std::max(0, minCoord.x) ;
    int startY = std::max(0, minCoord.y);
    int endX = std::min(Map_Width, minCoord.x+pos.x);
    int endY = std::min(Map_Height, minCoord.y+pos.y);

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            sf::Texture& tex = getTileTexture(Map[y][x].colour);

            if (Map[y][x].isNeedUpdate) {
                Map[y][x].updateTexture(tex);
                std::cout << y <<' ' << x;
            }

            if (Map[y][x].tile) {
                Map[y][x].tile->setPosition({ x * Tile_Size.x, y * Tile_Size.y });
                window.draw(*Map[y][x].tile);
            }
            Map[y][x].isNeedUpdate = false;
        }
    }
}
bool TileMap::intersects(const sf::FloatRect& a, const sf::FloatRect& b) {
    return !(a.position.x > b.position.x + b.size.x ||
        a.position.x + a.size.x < b.position.x ||
        a.position.y  > b.position.y + b.size.y ||
        a.position.y + a.size.y < b.position.y);
}
sf::Vector2f TileMap::CanMove(sf::Sprite& sprite, sf::Vector2f& moveDir) {
    sf::Vector2f finalPos = {0,0};
    sf::FloatRect nextX = sprite.getGlobalBounds();
    nextX.position.x += moveDir.x;
    if (isWalkable(nextX)) {
        finalPos.x = moveDir.x;
    }

    sf::FloatRect nextY = sprite.getGlobalBounds();
    nextY.position.y += moveDir.y;
    if (isWalkable(nextY)) {
        finalPos.y = moveDir.y;
    }
	return finalPos;
}

