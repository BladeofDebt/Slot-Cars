#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "TextureManager.h"
#include <Texture.h>

TextureManager* TextureManager::m_instance = nullptr;

void TextureManager::Create()
{
	m_instance = new TextureManager();
}

void TextureManager::Destroy()
{
	delete m_instance;
}

TextureManager * TextureManager::GetSingleton()
{
	return m_instance;
}

void TextureManager::LoadTexture(const std::string & _filePath)
{
	int lastIndex = _filePath.find_last_of('/', _filePath.length());
	std::string name = _filePath.substr(lastIndex + 1);

	aie::Texture* tex = new aie::Texture(_filePath.c_str());

	m_textures[name] = tex;
}

/// <summary>Returns key (AKA fileName).</summary>
void TextureManager::LoadTexture(const std::string& _filePath, std::string& _outName)
{
	int lastIndex = _filePath.find_last_of('/', _filePath.length());
	std::string name = _filePath.substr(lastIndex + 1);

	aie::Texture* tex = new aie::Texture(_filePath.c_str());

	m_textures[name] = tex;

	_outName = name;
}

aie::Texture * TextureManager::Get(const char* _fileName)
{
	return m_textures[_fileName];
}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (auto i = m_textures.begin(); i != m_textures.end(); i++)
		delete i->second;
}
