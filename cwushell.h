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
    std::string exit1 = "exit";
    std::string exitAlternative;
    //----------- 2. change prompt
    std::string change_prompt = "prompt";
    std::string redirect;
    //----------- 3. cpuinfo -switch
    std::string cpuinfo_clock = "cpuinfo -c";
    std::string cpuinfo_type = "cpuinfo -t";
    std::string cpuinfo_cores = "cpuinfo -n";
    //----------- 4. meminfo -switch
    std::string meminfo_RAM_avail = "meminfo -t";
    std::string meminfo_RAM_used = "meminfo -u";
    std::string meminfo_L2cache = "meminfo -c";
    //----------- 5. other existing shell commands will be handled by execvp

    char* myParameters[];


public:
    cwushell();
    void mechanism();
    int execute(char **argv);//std::string , std::vector<std::string> aVector);
    int quit(std::string a, int code_content);
    int change(std::string b, int y);
    int cpuinfo(std::string c, char *string);
    int meminfo(std::string d, char *string);
    char* goodFormat(std::string str);
    bool is_number(const std::string&);
};


#endif //CWUSHELL_CWUSHELL_H
