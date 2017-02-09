#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "Level.h"
#include "TextureManager.h"


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");

	TextureManager::Create();
	m_level = new Level();

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {

	delete m_level;
	TextureManager::Destroy();
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();
		
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_level->Update(deltaTime);
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_level->Draw(m_2dRenderer);
	m_2dRenderer->drawSprite(TextureManager::GetSingleton()->Get("ship.png"), 200, 200, 100, 100);

	char fpsString[16];

	itoa(m_fps, fpsString, 10);

	m_2dRenderer->drawText(m_font, fpsString, 0.0f, getWindowHeight() - 30.0f);

	// done drawing sprites
	m_2dRenderer->end();
}