#ifndef SNAKE_GLSLPROGRAM_H
#define SNAKE_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
    GLSLProgram ();

    virtual ~GLSLProgram ();

    void compileShaders ( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );

    void linkShaders ();

private:
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    void compileShader ( const std::string& compilePath, const GLuint id );
};


#endif //SNAKE_GLSLPROGRAM_H
