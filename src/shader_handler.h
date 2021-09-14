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
	    shaderHandler(const char *vertexPath, 
	    	const char *fragmentPath, 
	    	const char *geometryPath = nullptr);
	    shaderHandler(void);

	    void compile(const char *vShaderCode,
	     	const char *fShaderCode, 
	     	const char *gShaderCode = nullptr);
	    void use(void);

	    inline void setBool (const std::string &name, bool value)  const;
	    inline void setInt  (const std::string &name, int value)   const;
	    inline void setFloat(const std::string &name, float value) const;
	    
	    void setMatrix  (const std::string& name, glm::mat4 matrix) const;
	    void setVector2f(const std::string& name, glm::vec2 vector) const;
	    void setVector3f(const std::string& name, glm::vec3 vector) const;

	    unsigned int getID(void);

	private:
	    unsigned int shaderID;
	};
}

#endif
