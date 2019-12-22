#ifndef FRACTALS_ERRORHANDLER_H
#define FRACTALS_ERRORHANDLER_H

#include <string>

#define glCall(function) ErrorHandling::glClearError();\
    function;\
    ErrorHandling::glLogCall(#function, __FILE__, __LINE__);

namespace ErrorHandling {
    void glClearError();

    bool glLogCall(const std::string &function, const std::string &file_name, unsigned int line);
};


#endif //FRACTALS_ERRORHANDLER_H
