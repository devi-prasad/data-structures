
STACK_DIR=../../stack/ref-stack-adaptive
GRAPH_DIR=../adj-matrix

cc -Wall -I $STACK_DIR -I $GRAPH_DIR -o scc \
   -D CONTENT_TYPE='VERTEX' $STACK_DIR/stack.c \
   $GRAPH_DIR/graph.c \
   scc.c \
   scc-spec.c
