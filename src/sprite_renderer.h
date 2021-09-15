#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture_handler.h"
#include "shader_handler.h"

namespace gameModule
{
	class spriteRenderer
	{
	public:
	    // Constructor (inits shaders/shapes)
	    spriteRenderer(shaderHandler &shaderArg);
	    // Destructor
	    ~spriteRenderer();
	    // Renders a defined quad textured with given sprite
	    void drawSprite(textureHandler &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	private:
	    // Render state
	    shaderHandler shader; 
	    unsigned int  quadVAO;
	    // Initializes and configures the quad's buffer and vertex attributes
	    void initRenderData();
	};
}
#endif