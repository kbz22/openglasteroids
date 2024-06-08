#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Game/Game.h>

#include <OpenGLEngine/Texture.h>
#include <OpenGLEngine/Sprite.h>
#include <OpenGLEngine/Shader.h>

int main() {

	Game::Game game{};

	using namespace OpenGLEngine;
	
	while (game.Loop());

	return 0;

}
