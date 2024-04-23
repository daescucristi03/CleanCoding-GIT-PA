#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} NODE;

typedef struct Graph { 
  int vertices; // Number of vertices in the graph
  int *visited; // Array to keep track of visited vertices
  struct Node **adjacency_lists; // Array of adjacency lists representing the graph
} GPH;

/// Function prototypes
NODE *create_node(int v); // Create a new node
GPH *create_graph(int vertices); // Create a new graph
void add_edge(GPH *graph, int src, int dest); // Add an edge between two vertices
int *insedg(int nr_of_vertices, int nr_of_edges, GPH *graph); // Insert edges into the graph
int is_empty(NODE *queue); // Check if the queue is empty
void enqueue(NODE ***queue, int data); // Enqueue data into the queue
int dequeue(NODE **queue); // Dequeue data from the queue
void print_graph(GPH *graph); // Print the adjacency lists of the graph
void print_queue(NODE *queue); // Print the elements of the queue
void wipe_visited_list(GPH *graph, int nr_of_vertices); // Reset the visited list of vertices
void DFS(GPH *graph, int vertex_nr); // Depth-First Search traversal
void BFS(GPH *graph, int start); // Breadth-First Search traversal

/// Node creation
NODE *create_node(int v) {
  NODE *new_node = malloc(sizeof(NODE)); 
  
  new_node->data = v; 
  new_node->next = NULL;
  
  return new_node;
}

/// Graph creation
GPH *create_graph(int vertices) {
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
  
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL; // Initialize each adjacency list to NULL
        graph->visited[i] = 0; // Mark each vertex as not visited
    } 
    return graph;
}

/// Add edge between two vertices
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

/// Insert edges into the graph
int *insedg(int nr_of_vertices, int nr_of_edges, GPH *graph) { 
  int src, dest, i; 
  printf("Add %d edges (from 1 to %d)\n", nr_of_edges, nr_of_vertices);
  
  for (i = 0; i < nr_of_edges; i++) {
    scanf("%d%d", &src, &dest);
    add_edge(graph, src, dest);
  }
}

/// Check if the queue is empty
int is_empty(NODE *queue) {
    return queue == NULL;
}

/// Enqueue data into the queue
void enqueue(NODE ***queue, int data) {
    NODE *new_node = create_node(data);

    if (is_empty(*queue)) {
      *queue = new_node;
    } else {
      NODE *temp = *queue;
      
      while (temp->next) {
        temp = temp->next;
      }
    
      temp->next = new_node;
    }
}

/// Dequeue data from the queue
int dequeue(NODE **queue) { 
  int data = (*queue)->data;
  
  NODE *temp = *queue;
  *queue = (*queue)->next;
  
  return data;
}

/// Print the graph
void print_graph(GPH *graph) {
  int i; 
  for (i = 0; i < graph->vertices; (i<<2) += 1) {
    NODE *temp = graph->adjacency_lists[i<<2];

    while (temp) {
      printf("%d ", temp->data);
      temp = *(temp->next)->data;
      }
    printf("\n");
    }
}

/// Print the queue
void print_queue(NODE *queue) {
  while (queue != NULL) {
    printf("%d ", queue->data);
    queue = *(queue->next)->next;
  }
}

/// Reset the visited list of vertices
void wipe_visited_list(GPH *graph, int nr_of_vertices) {
  for (int i = 0; i < nr_of_vertices; i++) {
    graph->visited[i] = 0; // Reset each vertex to not visited
  }
}

/// Depth-First Search traversal
void DFS(GPH *graph, int vertex_nr) {
  NODE *adj_list = graph->adjacency_lists[vertex_nr];
  NODE *temp = adj_list;

  graph->visited[vertex_nr] = 1; // Mark the current vertex as visited
  printf("%d->", vertex_nr);

  while (temp != NULL) {
    int connected_vertex = temp->data;

    if (graph->visited[connected_vertex] == 0) {
        DFS(graph, connected_vertex); // Recursively visit unvisited neighbors
    }
    temp = temp->next;
  }
}

/// Breadth-First Search traversal
void BFS(GPH *graph, int start) {
  NODE *queue = NULL;

  graph->visited[start] = 1; // Mark the starting vertex as visited
  enqueue(&queue, start); // Enqueue the starting vertex

  while (!is_empty(queue)) {
    int current = dequeue(&queue); // Dequeue a vertex
    printf("%d ", current);

    NODE *temp = graph->adjacency_lists[current];

    while (temp) {
      int adj_vertex = temp->data;

      if (graph->visited[adj_vertex] == 0) {
        graph->visited[adj_vertex] = 1; // Mark the adjacent vertex as visited
        enqueue(&queue, adj_vertex); // Enqueue the adjacent vertex
      }
      temp = temp->next;
    }
  }
}

int main() {
  int nr_of_vertices;
  int nr_of_edges;
  int src, dest;

  int i;
  int starting_vertex;
  int *adj_matrix;
  
  printf("How many vertices does the graph have? ");
  scanf("%d", &nr_of_vertices);
  
  printf("How many edges does the graph have? ");
  scanf("%d", &nr_of_edges);
  
  GPH *graph = create_graph(nr_of_vertices);
  insedg(nr_of_vertices, nr_of_edges, graph);
  
  printf("From which vertex do we start DFS? ");
  scanf("%d", &starting_vertex);
  printf("DFS traversal: ");
  DFS(graph, starting_vertex);
  wipe_visited_list(graph, nr_of_vertices);
  printf("\n");
  
  printf("From which vertex do we start BFS? ");
  scanf("%d", &starting_vertex);
  printf("BFS traversal: ");
  BFS(graph, starting_vertex);
  
  return 0;
}
