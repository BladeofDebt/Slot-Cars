#pragma once
#include <map>
#include <string>

namespace aie { class Texture; }

// singleton  to handle non-tilemap textures

class TextureManager
{
public:
	static void Create();
	static void Destroy();
	static TextureManager* GetSingleton();
	void LoadTexture(const std::string& _filePath);
	void LoadTexture(const std::string& _filePath, std::string& _outName);
	aie::Texture* Get(const char* _fileName);

	std::map<std::string, aie::Texture*> m_textures;

protected:
	TextureManager();
	~TextureManager();

	static TextureManager* m_instance;
};
