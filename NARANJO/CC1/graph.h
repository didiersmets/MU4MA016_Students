#pragma once

/* An edge from vertex 'orig' to vertex 'dest' with weight 'cost'
 * Costs are assumed non negative.
 */
struct Edge {
	int orig;
	int dest;
	float cost;
};

/* An (unsorted) array of edges, where each edge is assumed to
 * satisfy 0 <= orig < nverts and 0 <= dest < nverts.
 */
struct EdgeList {
	int nverts;
	int nedges;
	struct Edge *edges;
};

/* An half-edge is an edge without the information about 'orig',
 * which should therefore be known from context.
 */
struct HEdge {
	int dest;
	double cost;
};

/* A (directed) graph. All edges starting at vertex
 * orig (0 <= orig < nverts) should be found at
 * edges[k] for all k s.t. offsets[orig] <= k < offsets[orig + 1].
 */
struct Graph {
	int nverts;
	int nedges;
	int* counts;
	int* offsets; /* of size nverts + 1 */
	struct HEdge *edges; /* of size nedges     */
};

/* Read a graph data file (formated as the provided .dta sample files)
 * and record the data in an edge list data structure, initialized
 * as needed and malloced.
 */
struct EdgeList *read_edge_list_from_file(const char *filename);

/* Transform the edge list into a graph (i.e. count sort the edges
 * depending on their orig value to be able to initialize and fill
 * the graph struct.
 */
struct Graph *build_graph_from_edge_list(const struct EdgeList *EL);

