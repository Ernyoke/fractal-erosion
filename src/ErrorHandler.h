//
// Created by ervin on 22.12.2019.
//

#ifndef FRACTALS_ERRORHANDLER_H
#define FRACTALS_ERRORHANDLER_H

#include <string>

#define glCall(function) ErrorHandling::glClearError();\
    function;\
    ErrorHandling::glLogCall(#function, __FILE__, __LINE__);

namespace ErrorHandling {
    void glClearError();

    bool glLogCall(std::string function, std::string file_name, unsigned int line);
};


#endif //FRACTALS_ERRORHANDLER_H
