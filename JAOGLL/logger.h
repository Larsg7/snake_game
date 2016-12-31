#ifndef SNAKE_LOGGING_H
#define SNAKE_LOGGING_H

#include <string>

namespace JOGL
{
    enum class LogLevel {
        LOG_ERROR
        , LOG_Warning
        , LOG_INFO
        , LOG_DEBUG
    };

    class Logger
    {
    public:
        static void log ( const std::string& msg, LogLevel logLevel )
        {
            if ( logLevel <= current_log_level )
            {
                printf( "LOG: %s\n", msg.c_str() );
            }
        }

        static LogLevel current_log_level;
    };
}

#endif //SNAKE_LOGGING_H
