#include <fstream>
#include <vector>
#include "../inc/GLSLCompiler.h"
#include "../inc/Snake_Error.h"

GLSLCompiler::GLSLCompiler ()
    : _programID ( 0 )
      , _vertexShaderID ( 0 )
      , _fragmentShaderID ( 0 )
      , _numAttributes ( 0 )
{

}

void GLSLCompiler::compileShaders ( const std::string& vertexShaderFilePath
                                 , const std::string& fragmentShaderFilePath )
{
    _vertexShaderID = glCreateShader( GL_VERTEX_SHADER );

    if ( _vertexShaderID == 0 )
    {
        throw Snake_Error ( "Could not create vertex shader!"
                , __LINE__, __FILE__ );
    }

    _fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

    if ( _fragmentShaderID == 0 )
    {
        throw Snake_Error ( "Could not create fragment shader!"
                , __LINE__, __FILE__ );
    }

    compileShader( vertexShaderFilePath, _vertexShaderID );
    compileShader( fragmentShaderFilePath, _fragmentShaderID );

    printf( "LOG: Shaders were compiled successfully.\n" );
}

void GLSLCompiler::linkShaders ()
{
    //Attach our shaders to our program
    glAttachShader( _programID, _vertexShaderID );
    glAttachShader( _programID, _fragmentShaderID );

    //Link our program
    glLinkProgram( _programID );

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv( _programID, GL_LINK_STATUS, &isLinked );
    if( isLinked == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetProgramiv( _programID, GL_INFO_LOG_LENGTH, &maxLength );

        //The maxLength includes the NULL character
        std::vector<char> errorLog( (unsigned)maxLength );
        glGetProgramInfoLog( _programID, maxLength, &maxLength, &errorLog[0] );

        //We don't need the program anymore.
        glDeleteProgram( _programID) ;
        //Don't leak shaders either.
        glDeleteShader( _vertexShaderID );
        glDeleteShader( _fragmentShaderID );

        //Use the infoLog as you see fit.

        //In this simple program, we'll just leave
        throw Snake_Error ( "Linking of shaders was unsuccessful: "
                            + std::string( &(errorLog[0]) ), __LINE__, __FILE__ );
    }

    //Always detach shaders after a successful link.
    glDetachShader( _programID, _vertexShaderID );
    glDetachShader( _programID, _fragmentShaderID );
    glDeleteShader( _vertexShaderID );
    glDeleteShader( _fragmentShaderID );

    printf( "LOG: Shaders were linked successfully.\n" );
}

void GLSLCompiler::addAttribute ( const std::string& attributeName )
{
    //glBindFragDataLocation( _programID, _numAttributes++, attributeName.c_str() );
    glBindAttribLocation( _programID, _numAttributes++, attributeName.c_str() );
}

GLint GLSLCompiler::get_attrLocation ( const std::string& attributeName ) const
{
    return glGetAttribLocation( _programID, attributeName.c_str() );
}

void GLSLCompiler::use ()
{
    glUseProgram( _programID );
    for ( GLuint i = 0; i < _numAttributes; ++i )
    {
        glEnableVertexAttribArray( i );
    }
}

void GLSLCompiler::unuse ()
{
    glUseProgram( 0 );
    for ( GLuint i = 0; i < _numAttributes; ++i )
    {
        glDisableVertexAttribArray( i );
    }
}

GLSLCompiler::~GLSLCompiler ()
{
    glDeleteProgram( _programID );
}

void GLSLCompiler::compileShader ( const std::string& compilePath, const GLuint id )
{
    //Now time to link them together into a program.
    //Get a program object.
    _programID = glCreateProgram();

    std::ifstream file ( compilePath );

    if ( file.fail() )
    {
        throw Snake_Error ( "Failed to open '" + compilePath + "'!"
                , __LINE__, __FILE__ );
    }

    std::string fileContents = "";
    std::string line;

    // read file into fileContents
    while ( std::getline( file, line ) )
    {
        fileContents += line + "\n";
    }

    file.close();

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
        std::vector<GLchar> errorLog ( (unsigned)maxLength );
        glGetShaderInfoLog( id, maxLength, &maxLength, &errorLog[0] );

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader( id ); // Don't leak the shader.

        throw Snake_Error ( "Compilation of shader " + compilePath + "was unsuccessful: "
                            + std::string( &(errorLog[0]) ), __LINE__, __FILE__ );
    }
}
