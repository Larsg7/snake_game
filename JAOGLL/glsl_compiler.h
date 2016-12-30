#ifndef SNAKE_GLSLPROGRAM_H
#define SNAKE_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

namespace JOGL
{
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

        void addAttribute ( const std::string& attributeName );

        GLint get_attrLocation ( const std::string& attributeName ) const;

        GLint get_uniformLocation ( const std::string& uniformName );

        void use ();

        void unuse ();

    private:
        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

        GLuint _numAttributes;

        /**
         * \brief Method to compile one shader
         * \param compilePath
         * \param id
         */
        void compileShader ( const std::string& compilePath, const GLuint id );
    };
}

#endif //SNAKE_GLSLPROGRAM_H
