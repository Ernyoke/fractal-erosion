//
// Created by ervin on 22.12.2019.
//

#ifndef FRACTALS_ERRORHANDLING_H
#define FRACTALS_ERRORHANDLING_H

#include <string>

#define glCall(function) ErrorHandling::glClearError();\
    function;\
    ErrorHandling::glLogCall(#function, __FILE__, __LINE__);

namespace ErrorHandling {
    void glClearError();

    bool glLogCall(std::string function, std::string file_name, unsigned int line);
};


#endif //FRACTALS_ERRORHANDLING_H
