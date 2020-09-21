# Custom-Linux-Shell

This program written in C++ under Linux simulates the mechanism behind shells like bash, the default shell in several flavors of Linux. <br />
Most commands are built without using the system() library.

Below is the list of some of the commands that can be used: <br /> 
  ### * Linux Shell commands
  Some Examples of commands: <br/>
  ls    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ==> see the content of the directory <br />
  pwd   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ==> find out the path of the current working directory <br />
  echo [TEXT] ==> display a text/string(s) on the standard output <br />
  
  
  ### * Exit command
  exit [n] : terminates the shell with argument as exit value <br />
  exit : terminates the shell with 0 as exit value when no argument is provided
  
  ### * Prompt command
  prompt [new_prompt]: changes the current shell prompt to the new_prompt <br />
  prompt : restores the shell to the default prompt when given no argument
  
  ### * CPU info
  cpuinfo [-switch]: for CPU related information<br />
  &nbsp;&nbsp;&nbsp;&nbsp; -c: the CPU clock <br />
  &nbsp;&nbsp;&nbsp;&nbsp; -t: the CPU type  <br />
  &nbsp;&nbsp;&nbsp;&nbsp; -n: the number of cores <br />
          
  ### * Memory info
  meminfo [-switch]: for memory related information <br />
  &nbsp;&nbsp;&nbsp;&nbsp; -t: total RAM available <br />
  &nbsp;&nbsp;&nbsp;&nbsp; -u: total RAM used <br />
  &nbsp;&nbsp;&nbsp;&nbsp; -c: L2 cache size <br />
  
  ### * Manual command: 
  Display of the commands available
  
  <br/> <br/>
  ## Compile
  g++ driver.cpp cwushell.cpp

  ## Run
  ./a.out
