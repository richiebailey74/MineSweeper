#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
using std::map;
using std::string;

//don't use using std namespcace in header files so people don't imort the entire namespace

class textureManager {

	static map<string, sf::Texture> textures;
public:
	
	static void LoadTexture(const char* filename);
	static void MakeDigitTextures();
	static sf::Texture& GetTexture(const char* textureKey);
	static void Clear();


};

