#include <stdint.h>

#define MAX_VERTS 12                   /* we deal with tiny graphs! */ 
#define MAX_WALK_LEN (MAX_VERTS * 3)   /* 3 edges per vertex is reasonable */
#define MAX_LABEL_LEN 16               /* length of a vertex label */

struct _graph_ {
    uint8_t  vc;                           /* actual # vertices in the graph */
    uint8_t  adj[MAX_VERTS][MAX_VERTS];    /* edges */
    char     *labels[MAX_VERTS];           /* for a labeled graph */
};
typedef struct _graph_ Graph;

struct _neighbors_ {
    uint8_t vc;
    uint8_t verts[MAX_VERTS];
};
typedef struct _neighbors_ Neighbors;

struct _walk_ {
    uint8_t  len;                     /* length of this walk */
    uint8_t  type;                    /* computed: WALK, TRAIL, PATH, CYCLE */
    uint8_t  visits[MAX_WALK_LEN];    /* vertices visited on this walk */
};
typedef struct _walk_ Walk;

/* Helpers */
#define NOT_A_VERTEX(v)        ((v) == 0)
#define IS_A_VERTEX(v)         ((v) & 0x1)
#define VISITED_VERTEX(v)      ((v) & 0x2)
#define DELETED_VERTEX(v)      ((v) & 0x4)
#define MARK_VISITED_VERTEX(v) ((v) | 0x2)
#define MARK_DELETED_VERTEX(v) ((v) | 0x4)

#define NOT_AN_EDGE(e)         ((e) == 0)
#define IS_AN_EDGE(e)          ((e) & 0x1)
#define VISITED_EDGE(e)        ((e) & 0x2)
#define DELETED_EDGE(E)        ((v) & 0x4)
#define MARK_VISITED_EDGE(e)   ((e) | 0x2)
#define MARK_DELETED_EDGE(E)   ((v) | 0x4)

/*
 * The Public Interface
 */
int isa_walk(const Graph g, const Walk w);
int isa_trail(const Graph g, const Walk w);
int isa_path(const Graph g, const Walk w);
int isa_cycle(const Graph g, const Walk w);

