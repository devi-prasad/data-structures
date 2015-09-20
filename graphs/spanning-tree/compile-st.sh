
## clean up - remove stray binaries.
rm -f a.out spantree *.o

## which stack version to use? Choose adaptive version.
GRAPH_DIR=../adj-matrix

##
## NOTE: we "adapt" or customize the stack content type and stack size
##       by preprocessor hacks. :-)
##       Take a look at stack.h for the preprocessor directives.
##

#cc -Wall -c ${GRAPH_DIR}/graph.c

##
## NOTE: since we include stack.h in our sources, we need these hacks too. :)
##       The output binary is named 'bst'.
# 
cc -ansi -Wall -I ${GRAPH_DIR} \
         prim.c st-spec.c \
         -o spantree

## remove the object files.
rm -f *.o

