
## clean up - remove stray binaries.
rm -f a.out bst stack.o

## which stack version to use? Choose adaptive version.
STACK_DIR=../../stack/ref-stack-adaptive

##
## NOTE: we "adapt" or customize the stack content type and stack size
##       by preprocessor hacks. :-)
##       Take a look at stack.h for the preprocessor directives.
##
cc -Wall -D STACK_CONTENT_TYPE='void *' \
         -D STACK_MAX_DEPTH=64 \
         -c ${STACK_DIR}/stack.c

##
## NOTE: since we include stack.h in our sources, we need these hacks too. :)
##       The output binary is named 'bst'.
# 
cc -Wall -D STACK_CONTENT_TYPE='void *' \
         -D STACK_MAX_DEPTH=64 \
         -I ${STACK_DIR} \
         bst.c bst-spec.c stack.o \
         -o bst

## remove the object files.
rm stack.o

