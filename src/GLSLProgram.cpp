//
// Created by lars on 12/4/16.
//

#include <fstream>
#include <vector>
#include "../inc/GLSLProgram.h"
#include "../inc/Snake_Error.h"

GLSLProgram::GLSLProgram ()
    : _programID ( 0 )
      , _vertexShaderID ( 0 )
      , _fragmentShaderID ( 0 )
{

}

void GLSLProgram::compileShaders ( const std::string& vertexShaderFilePath
                                 , const std::string& fragmentShaderFilePath )
{
    _vertexShaderID = glCreateShader( GL_VERTEX_SHADER );

    if ( _vertexShaderID == 0 )
    {
        throw Snake_Error ( "Could not create vertex shader!" );
    }

    _fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

    if ( _fragmentShaderID == 0 )
    {
        throw Snake_Error ( "Could not create fragment shader!" );
    }

    compileShader( vertexShaderFilePath, _vertexShaderID );
    compileShader( fragmentShaderFilePath, _fragmentShaderID );
}

void GLSLProgram::linkShaders ()
{

}

GLSLProgram::~GLSLProgram ()
{

}

void GLSLProgram::compileShader ( const std::string& compilePath, const GLuint id )
{
    std::ifstream vertexFile ( compilePath );

    if ( vertexFile.fail() )
    {
        throw Snake_Error ( "Failed to open " + compilePath + "!" );
    }

    std::string fileContents = "";
    std::string line;

    while ( std::getline( vertexFile, line ) )
    {
        fileContents += line + "\n";
    }

    vertexFile.close();

    const char* contentsPtr = fileContents.c_str();
    glShaderSource( id, 1, &contentsPtr, nullptr );
    glCompileShader( id );

    GLint success;
    glGetShaderiv( id, GL_COMPILE_STATUS, &success );
    if ( success == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv( id, GL_INFO_LOG_LENGTH, &maxLength );

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog ( maxLength );
        glGetShaderInfoLog( id, maxLength, &maxLength, &errorLog[0] );

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader( id ); // Don't leak the shader.

        throw Snake_Error ( "Compilation of shader " + compilePath + "was unsuccessful: "
                            + std::string( &(errorLog[0]) ) );
    }
}
