//
// Created by hanifa on 1/21/20.
//

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <wait.h>
#include <algorithm>
#include "cwushell.h"

using namespace std;

/**
 * Constructor
 */
cwushell::cwushell() {

};

/**
 *
 */
void cwushell::mechanism() {
    int codeFlag;
    string line;
    vector<string> allParams;

    do {
        // 1. Print a prompt
        cout << default_prompt;

        // 2. Read a line of input from the user
        getline(cin, line);
        char * line_in_chars = const_cast<char*>(line.c_str());

        // 3. Parse the line into the program name and the array of parameters
        char* args = strtok(line_in_chars," ");
        while (args != NULL) {
            allParams.push_back(args);
            args = strtok(NULL, " ");
        }

        //--- iterate through the vector
        bool progName_end = true;
        myParameters[allParams.size()];
        int i = 0;
        vector<string>::iterator it = allParams.begin();
        for (it; it != allParams.end(); ++it) {
            if (progName_end) {
                prog_name = *it;
                progName_end = false;
                myParameters[0] = const_cast<char *>((*it).c_str());
                i++;
            }
            else{
                params.push_back(*it);
                myParameters[i] = const_cast<char*>((*it).c_str());
                i++;
            }
        }


        // 4. Use the fork() system call to spawn a new child process
            //---- Check if the user input matches one predefined command

            if (prog_name.find(exit1) != string::npos) {
                quit(prog_name, allParams.size());
            } else if (prog_name.find(change_prompt) != string::npos) {
                prompt(prog_name, allParams.size());
            } else if (prog_name.find("cpuinfo") != string::npos) {
                cpuinfo(prog_name, myParameters[1]);
            } else if (prog_name.find("meminfo") != string::npos) {
                meminfo(prog_name, myParameters[1]);
            } else {
                codeFlag = execute(myParameters);
            }


        // 5. Repeats the loop or exit
        allParams.clear();
        free(args);

    } while (codeFlag);
}


/**
 *
 * @return
 */
int cwushell::execute( char* argv[])  {

    char* cmd_args[4];
    cmd_args[0] = "sh";
    cmd_args[1] = "-c";
    cmd_args[2] = *argv;
    cmd_args[3] = NULL;


    // using fork() to create a parallel process
    pid_t  pid = fork();

    if (pid == 0) {         // child process
        execvp("sh", cmd_args);
        printf("*************** ERROR ***************\n");
    } else if (pid < 0) {
        cout << "Error in forking attempt!" << endl;
    }
    else {
        int sts;
        waitpid(pid, &sts, 0);
    }
    return 1;
}

/** -----------------------------------------------
        Helper functions for predefined commands
    ----------------------------------------------- */

int cwushell::quit(string a, int x) {
    if (a == exit1 && x == 1) {
        exit(0);
    }
    else if ((a.find(exit1) != string::npos) && x == 2) {
        char* code_e = myParameters[1];
        string code_ex(code_e);
        if (code_ex == "--help") {
            cout << "Usage: exit [n]\n"
                    "terminates the shell with argument given as exit value\n"
                    "   No space is allowed for inside the argument.\n"
                    "typing exit (alone with no argument) terminates the shell with 0 as exit value\n"
                 << endl;
            return 0;
        }
        else if ((code_ex[0] == '[' && code_ex[code_ex.length() -1] == ']') || (code_ex[0] == '(' || code_ex[code_ex.length() -1] == ')') ) {
            code_ex.erase(0, 1);
            code_ex.erase(code_ex.length() - 1, 1);
        }
        if (code_ex.empty()) {
            exit(0);
        }
        bool tr = is_number(code_ex);
        if (tr) {
            int code_exit = stoi(code_ex);
            exit(code_exit);
        } else {
            printf("Wrong command. Please type -help for more information\n");
        }
    } else if ((a.find(exit1) != string::npos) && x > 2) {
        printf("Space is only allowed between the command and argument.\n"
               "Remove any space in between arguments. \n");
    }
    else {
        printf("Wrong command. Please type exit --help for more information\n");
    }
}

int cwushell::prompt(string b, int y) {
    if (b == change_prompt && y == 1) {
        default_prompt = "cwushell> ";
        return 1;
    } else if ((b.find(change_prompt) != string::npos) && y > 1) {
        if (myParameters[1] == prompt_help) {
            cout << "Usage: prompt [new_prompt]\n"
                    "changes the current shell prompt to the new_prompt\n"
                    "   No space is allowed for the new prompt.\n"
                    "   The [new_prompt] should be lowercase\n"
                    "typing prompt alone restores the default shell prompt\n"
                 << endl;
        }
        else {
            default_prompt = myParameters[1];
            for (int i = 2; i < y; i++) {
                default_prompt.append(" ");
                default_prompt.append(myParameters[i]);
            }
            default_prompt.append("> ");
        }
        return 0;
    }
    else{
        cout << "Invalid prompt.\n"
                "Type prompt --help for more information.\n" << endl;
        return 0;
    }
}

int cwushell:: cpuinfo(std::string c, char* ext) {
    c.append(" ");
    c.append(ext);
    if (c == cpuinfo_clock) {
        string c2 = "cat /proc/cpuinfo | grep 'model name' | head -n 1 | cut -d' ' -f8";
        char* clock[2]= {const_cast<char *>(c2.c_str()), NULL};
        execute(clock);
    } else if (c == cpuinfo_type) {
        string c3 = "cat /proc/cpuinfo | grep 'model name' | head -n 1 | cut -d' ' -f3";
        char* type[2] = {const_cast<char *>(c3.c_str()), NULL} ;
        execute(type);
    } else if (c == cpuinfo_cores) {
        string c4 = "cat /proc/cpuinfo | grep processor | wc -l";
        char* cores[2] = {const_cast<char *>(c4.c_str()), NULL} ;
        execute(cores);
    } else if (c == cpuinfo_help) {
        cout << "Usage: cpuinfo [-switch]\n"
                "Switches that can be used for CPU information : \n"
                " -c: displays the cpu clock\n"
                " -t: displays the cpu type\n"
                " -n: displays the number of cores\n"
                " -h: displays this help message\n"
             << endl;
    }
    else {
        cout << "Invalid switch.\n"
                "Type cpuinfo -h for more information regarding the switches.\n" ;
    }
}

int cwushell::meminfo(std::string d, char* str) {
    d.append(" ");
    d.append(str);
    if (d == meminfo_RAM_avail) {
        string availability = "vmstat -s | grep 'total memory' | uniq";
        char* avail_RAM[2] = {const_cast<char *>(availability.c_str()), NULL} ;
        execute(avail_RAM);
    } else if (d == meminfo_RAM_used) {
        string used = "vmstat -s | grep 'used memory' | uniq";
        char* used_RAM[2] = {const_cast<char *>(used.c_str()), NULL} ;
        execute(used_RAM);
    } else if (d == meminfo_L2cache) {
        string cache = "cat /sys/devices/system/cpu/cpu0/cache/index2/size";
        char* cache_L2[2] = {const_cast<char *>(cache.c_str()), NULL} ;
        execute(cache_L2);
    } else if (d == meminfo_help) {
       cout << "Usage: meminfo [-switch]\n"
               "Switches that can be used for memory information : \n"
               " -t: displays the total RAM memory\n"
               " -u: displays the used RAM memory\n"
               " -c: displays the size of the L2 cache\n"
               " -h: displays this help message\n"
       << endl;
    }
    else {
        cout << "Invalid switch.\n"
                "Type meminfo -h for more information regarding the switches.\n" ;
    }
}

char * cwushell::goodFormat(std::string str) {
    char * line_in_chars = const_cast<char*>(str.c_str());
    char* args = strtok(line_in_chars," ");
    return args;
}

bool cwushell::is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}