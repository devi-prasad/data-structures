
## clean up - remove stray binaries.
rm -f a.out spantree *.o

## which graph version to use?
GRAPH_DIR=../adj-matrix
 
cc  -Wall -I ${GRAPH_DIR} \
         setop.c prim.c kruskal.c st-spec.c \
         -o spantree

## remove the object files.
rm -f *.o
