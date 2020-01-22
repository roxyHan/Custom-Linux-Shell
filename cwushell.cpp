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

        /**cout << prog_name << endl;
        cout << "Now the command to be executed" << endl;
        for (vector<string>::iterator it = params.begin(); it != params.end(); ++it) {
            cout << *it << " ";
        }*/


        // 4. Use the fork() system call to spawn a new child process
            //---- Check if the user input matches one predefined command

            if (prog_name.find(exit1) != string::npos) {
                quit(prog_name, allParams.size());
            } else if (prog_name.find(change_prompt) != string::npos) {
                change(prog_name, allParams.size());
            } else if (prog_name.find("distro") != string::npos) {
                distro(prog_name, myParameters[1]);
            } else if (prog_name.find("info") != string::npos) {
                info(prog_name, myParameters[1]);
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

    // using fork() to create a parallel process
    pid_t  pid = fork();

    //char* arguments[] = const_cast<char*>(vec.);
    if (pid == 0) {         // child process
        execvp(reinterpret_cast<const char *>(argv[0]), reinterpret_cast<char *const *>(argv));
        printf("***************\n");
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
   // int sizeArr = sizeof(myParameters)/sizeof(myParameters[0]);
    if (a == exit1 && x == 1) {
        exit(0);
    } else if ((a.find(exit1) != string::npos) && x == 2) {
        char* code_e = myParameters[1];
        int code_exit = atoi(code_e);
        exit(code_exit);
    } else{
        printf("Wrong command. Visit help\n");
    }
}

int cwushell::change(string b, int y) {
    if (b == change_prompt && y == 1) {
        default_prompt = "cwushell > ";
        return 1;
    } else if ((b.find(change_prompt) != string::npos) && y > 1) {
        default_prompt = myParameters[1];
        for (int i = 2; i < y; i++) {
            default_prompt.append(" ");
            default_prompt.append(myParameters[i]);
        }
        default_prompt.append(" > ");
        return 1;
    } else{
        cout << "Invalid prompt" << endl;
        return 0;
    }
}

int cwushell::distro(std::string c, char* ext) {
    c.append(" ");
    c.append(ext);
    string c1 = "lsb_release";
    if (c == distro_version) {
        string c2 = "-r";
        char* vers[3]= {const_cast<char *>(c1.c_str()), const_cast<char *>(c2.c_str()), NULL} ;
        execute(vers);
    } else if (c == distro_name) {
        string c3 = "-i";
        char* nameD[3] = {const_cast<char *>(c1.c_str()), const_cast<char *>(c3.c_str()), NULL} ;
        execute(nameD);
    } else if (c == distro_code) {
        string c4 = "-c";
        char* codeN[3] = {const_cast<char *>(c1.c_str()), const_cast<char *>(c4.c_str()), NULL} ;
        execute(codeN);
    }
    else {
        cout << "Invalid" ;
        exit(3);
    }
}

int cwushell::info(std::string d, char* str) {
    d.append(" ");
    d.append(str);
    string a1 = "getconf";
    if (d == info_size) {
        // getconfig PAGESIZE
        string a2 = "PAGE_SIZE";
        char* arr[3] = {const_cast<char *>(a1.c_str()), const_cast<char *>(a2.c_str()), NULL} ;
        execute(arr);
    } else if (d == info_numbers) {
        // getconf _AVPHYS_PAGES
        string a3 = "_AVPHYS_PAGES";
        char* pagesCount[3] = {const_cast<char *>(a1.c_str()), const_cast<char *>(a3.c_str()), NULL} ;
        execute(pagesCount);
    } else if (d == info_processors) {
        // nproc
        string aT = "nproc";
        char* arr2[2] = {const_cast<char *>(aT.c_str()), NULL} ;
        execute(arr2);
    }
}

char * cwushell::goodFormat(std::string str) {
    char * line_in_chars = const_cast<char*>(str.c_str());
    char* args = strtok(line_in_chars," ");
    return args;
}