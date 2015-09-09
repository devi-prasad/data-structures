#ifndef _INCLUDED_BFS_
#define _INCLUDED_BFS_

struct _vertex_ {
    uint8_t id;
    uint8_t parent;
    char label[MAX_LABEL_LEN];
};

typedef struct _vertex_ Vertex;

Vertex vertex_new(uint8_t id, const char *label, uint8_t parent);

typedef void (Visitor) (Vertex v);

void graph_bfs(Graph g, Visitor visit);

#endif