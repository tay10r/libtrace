#Don't run this makefile, it's only here to be included into others
#I recommend that you add a "-march=<xxx>" to reflect your own machine.

compiler = g++
flags = -Wall -Wextra -Werror -Wfatal-errors
compile = -D_REENTRANT -O3 -c -g -ggdb
link = -o
library = ar rcs
