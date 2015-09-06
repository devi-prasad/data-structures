#ifndef _INCLUDED_DFS_
#define _INCLUDED_DFS_

struct _vertex_ {
    uint8_t id;
    uint8_t parent;
    char label[MAX_LABEL_LEN];
};

typedef struct _vertex_ Vertex;

Vertex vertex_new(uint32_t id, const char *label);

typedef void (Visitor) (Vertex v);

void graph_dfs(Graph g, Visitor visit);

#endif