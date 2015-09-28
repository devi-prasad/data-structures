#ifndef _INCLUDED_SCC_
#define _INCLUDED_SCC_


struct _vertex_ {
    uint8_t id;
    uint8_t index;
    uint8_t low_link;
    uint8_t on_stack;
};

typedef struct _vertex_ Vertex;

int32_t find_stronly_connected_components_tarjan(Graph *graph);

#endif
