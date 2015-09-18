
rm -f a.out *.o 
cc -Wall -D STACK_CONTENT_TYPE='void *' -c ../../stack/ref-stack-adaptive/stack.c
cc -Wall -I ../../stack/ref-stack-adaptive bst.c bst-spec.c stack.o

