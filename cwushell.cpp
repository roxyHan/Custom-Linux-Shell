//
// Created by hanifa on 1/21/20.
//

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
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
        printf("cwushell > ");

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
        vector<string>::iterator it = allParams.begin();
        for (it; it != allParams.end(); ++it) {
            if (progName_end) {
                prog_name = *it;
                progName_end = false;
            }
            else{
                params.push_back(*it);
            }
        }
        allParams.clear();
        free(args);

        cout << prog_name << endl;
        cout << "Now the command to be executed" << endl;
        for (vector<string>::iterator it = params.begin(); it != params.end(); ++it) {
            cout << *it << " ";
        }

        // 4. Use the fork() system call to spawn a new child process
            codeFlag = execute(params);

        // 5. Repeats the loop or exit

    } while (codeFlag);
}


/**
 *
 * @return
 */
int cwushell::execute(vector<string> vec)  {

    // using fork() to create a parallel process
    pid_t  pid = fork();






    return 0;
}