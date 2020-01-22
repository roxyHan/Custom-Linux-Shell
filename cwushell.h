#ifndef CWUSHELL_CWUSHELL_H
#define CWUSHELL_CWUSHELL_H

#include <vector>

class cwushell {

private:
    std::string prog_name;
    std::vector<std::string> params;
    std::string default_prompt = "cwushell > ";

    // predefined commands
    //----------- 1. quit [n]
    std::string exit1 = "quit";
    std::string exitAlternative;
    //----------- 2. change prompt
    std::string change_prompt = "change_prompt";
    std::string redirect;
    //----------- 3. distro -switch
    std::string distro_version = "distro -v";
    std::string distro_name = "distro -n";
    std::string distro_code = "distro -c";
    //----------- 4. info -switch
    std::string info_size = "info -s";
    std::string info_numbers = "info -n";
    std::string info_processors = "info -p";
    //----------- 5. other existing shell commands will be handled by execvp

    char* myParameters[];


public:
    cwushell();
    void mechanism();
    int execute(char **argv);//std::string , std::vector<std::string> aVector);
    int quit(std::string a, int code_content);
    int change(std::string b, int y);
    int distro(std::string c, char *string);
    int info(std::string d, char *string);
    char* goodFormat(std::string str);
};


#endif //CWUSHELL_CWUSHELL_H
