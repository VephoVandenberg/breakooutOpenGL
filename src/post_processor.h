#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture_handler.h"
#include "sprite_renderer.h"
#include "shader_handler.h"

namespace gameModule
{
	class postProcessor
	{
	public:
		shaderHandler 	postProcessingShader;
		textureHandler  texture;

		unsigned int width;
		unsigned int height;

		bool confuse;
		bool chaos;
		bool shake;

	public:
		postProcessor(shaderHandler shader, unsigned int widthArg, unsigned int heightArg);
		void beginRender(void);
		void endRender(void);
		void render(float time);

	private:
		unsigned int MSFBO, FBO;
		unsigned int RBO;
		unsigned int VAO;

		void initRenderData(void);
	};
}

#endif