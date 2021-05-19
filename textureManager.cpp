#include "textureManager.h"

//redeclaring the static class variable
map<string, sf::Texture> textureManager::textures;

//takes in only the name of the file(no extension nor directory) and loads that file's data and adds it to a map
void textureManager::LoadTexture(const char* filename) {

	//concatonates the file path while keeping the basic name separate
	string filePath = "images/";
	filePath += filename;
	filePath += ".png";

	//uses the simple name as the key while still adding the loaded file path as the texture value
	textures[filename].loadFromFile(filePath);
}

//creates the digit textures of the digit display so displaying changing numbers is easier
//uses IntRect to parse out the particular and desired part of the texture
void textureManager::MakeDigitTextures() {
	int digitLength = 21;
	string filePath = "images/digits.png";
	string tempKey = "digit-";
	textures[tempKey].loadFromFile(filePath, sf::IntRect((digitLength * 10), 0, 21, 32));
	
	for (int i = 0; i < 10; i++) {

		string keyToCall = "digit";
		string digitNumber = std::to_string(i);
		keyToCall += digitNumber;
		textures[keyToCall].loadFromFile(filePath, sf::IntRect((i * digitLength), 0, 21, 32));
	}
}

//static function that allows for direct access of the map that contains all of the texture information
sf::Texture& textureManager::GetTexture(const char* textureKey) {
	//key doesn't exist, load it then return it
	if (textures.find(textureKey) == textures.end()) {
		LoadTexture(textureKey);
		return textures[textureKey];
	}
	//if the key does exist, just return it
	else {
		return textures[textureKey];
	}
}

void textureManager::Clear() {
	textures.clear();
}
