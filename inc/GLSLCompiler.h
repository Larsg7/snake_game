#ifndef SNAKE_GLSLPROGRAM_H
#define SNAKE_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>


/**
 * \brief Class to Compile and Link GLSL code
 * Supports vertex and fragment shaders.
 */
class GLSLCompiler
{
public:
    GLSLCompiler ();

    virtual ~GLSLCompiler ();

    /**
     * \brief Method to compile a vertex and a fragment shader
     * \param vertexShaderFilePath
     * \param fragmentShaderFilePath
     */
    void compileShaders ( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );

    void linkShaders ();

private:
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    /**
     * \brief Method to compile one shader
     * \param compilePath
     * \param id
     */
    void compileShader ( const std::string& compilePath, const GLuint id );
};


#endif //SNAKE_GLSLPROGRAM_H
