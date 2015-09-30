#include <stdint.h>
#include <assert.h>
#include "graph.h"
#include "scc.h"

#define STACK_CONTENT_TYPE Vertex
#include "stack.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* state variables */
static Stack    _vstk_;
static uint8_t  _index_;
static uint8_t _scc_count_;

static void _scc_tarjan_(Graph *graph, Vertex verts[], uint8_t i)
{
	StackResult r;
    int j;

    verts[i].index = _index_;
    verts[i].low_link = _index_;
    ++_index_;

    stack_push(_vstk_, verts[i], &r); assert(r.status == STACK_OK);
    verts[i].on_stack = 1;

    for (j = 0; j < graph->vc; ++j) {
    	if (graph->adj[verts[i].id][j]) {
            if (verts[j].index == 0xFF) {
                /* successor w it not yet visited */
                _scc_tarjan_(graph, verts, verts[j].id);
                verts[i].low_link = MIN(verts[i].low_link, verts[j].low_link);
            } else {
            	/* successor w is in stack, and therefore, in the current SCC */
                verts[i].low_link = MIN(verts[i].low_link, verts[j].index);
            }
        }
    }
    
    if (verts[i].low_link == verts[i].index) {
    	Vertex w;
    	/* start a new strongly connected component */
    	++_scc_count_;
        do {
            stack_pop(_vstk_, &r);
            assert(r.status == STACK_OK);
            w = r.data;
            verts[w.id].on_stack = 0;
        } while (w.id != verts[i].id);
    }
}

int32_t find_stronly_connected_components_tarjan(Graph *graph)
{
	uint8_t i;
	Vertex verts[graph->vc];

    for (i = 0; i < graph->vc; ++i) {
        verts[i].id = i;
        verts[i].index = verts[i].low_link = 0xFF;
        verts[i].on_stack = 0;
    }

    _vstk_ = stack_new(0);
    _index_ = 0;
    _scc_count_ = 0;

    for (i = 0; i < graph->vc; ++i) {
        if (verts[i].index == 0xFF) {
            _scc_tarjan_(graph, verts, i);
        }
    }

   _index_ = 0xFF;
   stack_delete(_vstk_);

   return _scc_count_;
}
