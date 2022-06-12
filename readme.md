# Minishell

## Setup
To build and run project, use following commands in project dir:
```shell
make all
./minishell
```
![example](https://i.ibb.co/BKc2gBy/Screenshot-2022-06-13-at-02-43-36.png=x250)


## Summary
The objective of this project is for you to create a simple shell. Yes, your
own little bash or zsh. You will learn a lot about processes and file descriptors.

## Constraints
* Show a prompt when waiting for a new command
* Search and launch the right executable (based on the PATH variable or by using
relative or absolute path) like in bash
* It must implement the builtins like in bash:
  - echo with option ’-n’ 
  - cd with only a relative or absolute path 
  - pwd without any options 
  - export without any options 
  - unset without any options 
  - env without any options and any arguments 
  - exit without any options
* ; in the command should separate commands like in bash
* ’ and " should work like in bash except for multiline commands
* Redirections < > “>>” should work like in bash except for file descriptor aggregation
* Show a prompt when waiting for a new command
* Search and launch the right executable (based on the PATH variable or by using
relative or absolute path) like in bash
* It must implement the builtins like in bash:
  - echo with option ’-n’ 
  - cd with only a relative or absolute path 
  - pwd without any options 
  - export without any options 
  - unset without any options 
  - env without any options and any arguments 
  - exit without any options
* ; in the command should separate commands like in bash
* ’ and " should work like in bash except for multiline commands
* Redirections < > “>>” should work like in bash except for file descriptor aggregation