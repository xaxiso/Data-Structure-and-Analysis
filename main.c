#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 500300

int height[SIZE];
int track[SIZE];

int day;

int tree_array_size = SIZE;
int heap_size = 0;

struct record{
	int ID;
	int height;
};

struct record* A;

void init(){
	A = malloc(SIZE * sizeof(struct record));
}

void swap( int *a, int *b ) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

//function to get right child of a node of a tree
int get_right_child(int index) {
  if((((2*index)+1) < tree_array_size) && (index >= 1))
    return (2*index)+1;
  return -1;
}

//function to get left child of a node of a tree
int get_left_child(int index) {
    if(((2*index) < tree_array_size) && (index >= 1))
        return 2*index;
    return -1;
}

//function to get the parent of a node of a tree
int get_parent(int index) {
  if ((index > 1) && (index < tree_array_size)) {
    return index/2;
  }
  return -1;
}

void min_heapify(int index) {
  int left_child_index = get_left_child(index);
  int right_child_index = get_right_child(index);

  // finding smallest among index, left child and right child
  int smallest = index;

  if ((left_child_index <= heap_size) && (left_child_index>0)) {
    if (A[left_child_index].height < A[smallest].height) {
      smallest = left_child_index;
    }
  }

  if ((right_child_index <= heap_size && (right_child_index>0))) {
    if (A[right_child_index].height < A[smallest].height) {
      smallest = right_child_index;
    }
  }

  // smallest is not the node, node is not a heap
  if (smallest != index) {
    swap(&A[index].height, &A[smallest].height);
    swap(&A[index].ID, &A[smallest].ID);
    min_heapify(smallest);
  }
}

void build_min_heap() {
  int i;
  for(i=heap_size/2; i>=1; i--) {
    min_heapify(i);
  }
}

int minimum() {
  return A[1].ID;
}

int extract_min() {
  int minm = A[1].ID;
  A[1].height = A[heap_size].height;
  A[1].ID = A[heap_size].ID;
  heap_size--;
  min_heapify(1);
  return minm;
}

void decrease_key(int index, int height, int key) {
  A[index].height = height;
  A[index].ID = key;
  while((index>1) && (A[get_parent(index)].height > A[index].height)) {
    swap(&A[index].height, &A[get_parent(index)].height);
    swap(&A[index].ID, &A[get_parent(index)].ID);
    index = get_parent(index);
  }
}

void insert(int key) {
  heap_size++;
  A[heap_size].height = INT_MAX;
  A[heap_size].ID = INT_MAX;
  decrease_key(heap_size, height[key], key);
}

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int v);

struct Graph {
  int numVertices;
  int* visited;

  // We need ull** to store a two dimensional array.
  // Similary, we need struct node** to store an array of Linked lists
  struct node** adjLists;
};

// DFS algo
void DFS(struct Graph* graph, int vertex, int n, int t) {
	struct node* adjList = graph->adjLists[vertex];

	graph->visited[vertex] = 1;
	//printbruh("Visited %d \n", vertex);

	while (adjList != NULL) {
		int connectedVertex = adjList->vertex;

		if(graph->visited[connectedVertex] == 0){
		    if (height[vertex] >= height[connectedVertex]){
		    	//printbruh("if DFS: height[%d]: %d >= height[%d]: %d\n", vertex, height[vertex], connectedVertex, height[connectedVertex]);
		    	// graph->visited[connectedVertex] = 1;
		    	DFS(graph, connectedVertex, n, t);
		    }
		    else{
		    	//printbruh("else DFS: height[%d]: %d >= height[%d]: %d\n", vertex, height[vertex], connectedVertex, height[connectedVertex]);
		    	insert(connectedVertex);
		    	track[connectedVertex] = 1;
		    	// graph->visited[connectedVertex] = 1;
		    }
		}
		adjList = adjList->next;
	}
}

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc((SIZE) * sizeof(struct node*));

  graph->visited = malloc((SIZE) * sizeof(int));

  int i;
  for (i = 1; i <= vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

int main(int argc, char const *argv[])
{
	init();
    int n, m, s, t, i, temp, temp2;
    scanf("%d%d", &n, &m);

    struct Graph* graph = createGraph(n);

    for(i=0;i<m;i++){
        scanf("%d%d", &temp, &temp2);
        addEdge(graph, temp, temp2);
    }

    for(i=1;i<=n;i++)
        scanf("%d", &height[i]);

    scanf("%d%d", &s, &t);

    DFS(graph, s, n, t);

    // for (int i = 1; i <= n; ++i)
    // 	//printbruh("track[%d]: %d\n", i, track[i]);

    int min = INT_MAX;
    while(graph->visited[t] != 1){
    	min = extract_min();
    	while(graph->visited[min] == 1)
    		min = extract_min();

    	graph->visited[min] = 1;
    	
    	if(min == t){
    		if(height[min] > day)
    			day = height[min];
    		break;
    	}

    	if(height[min] > day)
    		day = height[min];

    	

    	//printbruh("\nextract min: %d, height: %d, day: %d\n", min, height[min], day);


    	struct node* adjList = graph->adjLists[min];

    	while(adjList != NULL){
    		int connectedVertex = adjList->vertex;
    		//printbruh("minadj: %d, visited: %d, track: %d\n", connectedVertex, graph->visited[connectedVertex], track[connectedVertex]);

			if(track[connectedVertex] == 0){
				//printbruh("insert: %d, day: %d\n", connectedVertex, day);
				insert(connectedVertex);
				track[connectedVertex] = 1;
			}
			else if(height[connectedVertex] < day && track[connectedVertex]){
				//printbruh("heapify: %d, day: %d\n", connectedVertex, day);
				height[connectedVertex] = day;
				min_heapify(1);
			}

    		adjList = adjList->next;
    	}

    }

    printf("%d\n", day);

    return 0;
}