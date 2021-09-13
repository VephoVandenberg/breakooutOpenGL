#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace gameModule
{
	class shaderHandler
	{
	public:
	    shaderHandler(const char *vertexPath, const char *fragmentPath);
	    void use(void);

	    inline void setBool (const std::string &name, bool value)  const;
	    inline void setInt  (const std::string &name, int value)   const;
	    inline void setFloat(const std::string &name, float value) const;
	    
	    void setMatrix(const std::string& name, glm::mat4 matrix) const;
	    void setVector(const std::string& name, glm::vec2 vector) const;

	private:
	    unsigned int shaderID;

	private:
		shaderHandler(const shaderHandler& shaderInstance);
		shaderHandler(shaderHandler&& shaderInstance);
	};
}

#endif
