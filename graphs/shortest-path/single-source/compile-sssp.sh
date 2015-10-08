
GRAPH_DIR=../../adj-matrix

cc -Wall -I $GRAPH_DIR \
   $GRAPH_DIR/graph.c heap.c shortest_path.c sssp_spec.c
