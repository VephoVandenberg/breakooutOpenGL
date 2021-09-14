#include "shader_handler.h"

using namespace gameModule;

shaderHandler::shaderHandler(void)
{
    
}

shaderHandler::shaderHandler(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    std::string vertexShader;
    std::string fragmentShader;
    std::string geometryShader;

    try
    {
        std::ifstream vertexFile;
        std::ifstream fragmentFile;
    	
        vertexFile.open(vertexPath);
    	fragmentFile.open(fragmentPath);

    	std::stringstream vertex_stream, fragment_stream;

    	vertex_stream << vertexFile.rdbuf();
    	fragment_stream << fragmentFile.rdbuf();

    	vertexFile.close();
    	fragmentFile.close();

    	vertexShader = vertex_stream.str();
    	fragmentShader = fragment_stream.str();

        if (geometryPath)
        {
            std::ifstream geometryFile(geometryPath);
            std::stringstream geomrtry_stream;
            geomrtry_stream << geometryFile.rdbuf();
            geometryFile.close();
            geometryShader = geomrtry_stream.str();
        }
    }
    catch (std::exception e)
    {
	   std::cout << "file or files weren't read succesfully." << std::endl;
    }

    const char *vertexShaderSrc = vertexShader.c_str();
    const char *fragmentShaderSrc = fragmentShader.c_str();
    const char *geometryShaderSrc = geometryShader.c_str();

    char infolog[512];
    int success;

    unsigned int vertexID, fragmentID, geometryID;

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexShaderSrc, 0);
    glCompileShader(vertexID);
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	   glGetShaderInfoLog(vertexID, 512, 0, infolog);
	   std::cout << "VERTEX:" << infolog;
    }

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentShaderSrc, 0);
    glCompileShader(fragmentID);
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	   glGetShaderInfoLog(fragmentID, 512, 0, infolog);
	   std::cout << "FRAGMENT:" << infolog;
    }

    geometryID = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryID, 1, &geometryShaderSrc, 0);
    glCompileShader(geometryID);
    glGetShaderiv(geometryID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometryID, 512, 0, infolog);
        std::cout << "GEOMTRY:" << infolog; 
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);
    glAttachShader(shaderID, geometryID);
    glLinkProgram(shaderID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteShader(geometryID);
}

void shaderHandler::compile(const char *vShaderCode, const char *fShaderCode, const char *gShaderCode)
{
    char infolog[512];
    int success;

    unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vShaderCode, 0);
    glCompileShader(vertexID);
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
       glGetShaderInfoLog(vertexID, 512, 0, infolog);
       std::cout << "VERTEX:" << infolog;
    }

    unsigned int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fShaderCode, 0);
    glCompileShader(fragmentID);
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
       glGetShaderInfoLog(fragmentID, 512, 0, infolog);
       std::cout << "FRAGMENT:" << infolog;
    }

    unsigned int geometryID = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryID, 1, &gShaderCode, 0);
    glCompileShader(geometryID);
    glGetShaderiv(geometryID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometryID, 512, 0, infolog);
        std::cout << "GEOMTRY:" << infolog; 
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);
    glAttachShader(shaderID, geometryID);
    glLinkProgram(shaderID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteShader(geometryID);
}

void shaderHandler::use(void)
{
    glUseProgram(shaderID);
}

inline void shaderHandler::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

inline void shaderHandler::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

inline void shaderHandler::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void shaderHandler::setMatrix(const std::string& name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void shaderHandler::setVector2f(const std::string& name, glm::vec2 vector) const
{
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), vector[0], vector[1]);
}

void shaderHandler::setVector3f(const std::string& name, glm::vec3 vector) const
{
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), vector[0], vector[1], vector[2]);
}

unsigned int shaderHandler::getID(void)
{
    return shaderID;
}