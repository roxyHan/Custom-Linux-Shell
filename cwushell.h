#ifndef CWUSHELL_CWUSHELL_H
#define CWUSHELL_CWUSHELL_H

#include <vector>

class cwushell {

private:
    std::string prog_name;
    std::vector<std::string> params;

public:
    cwushell();
    void mechanism();
    int execute(std::vector<std::string> aVector);
};


#endif //CWUSHELL_CWUSHELL_H
