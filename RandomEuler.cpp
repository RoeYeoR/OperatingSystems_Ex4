#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <list>

// Define a structure for the linked list nodes
struct ListNode {
    int vertex;
    ListNode* next;
    ListNode(int v) : vertex(v), next(nullptr) {}
};

// Define a structure for the adjacency list
struct AdjList {
    ListNode* head;
    int degree; // Store the degree of the vertex
    AdjList() : head(nullptr), degree(0) {}
};

// Function to add an edge to the adjacency list
void addEdge(AdjList* adj, int u, int v) {
    ListNode* newNode = new ListNode(v);
    newNode->next = adj[u].head;
    adj[u].head = newNode;
    adj[u].degree++;

    // Since it's an undirected graph, add the edge in both directions
    newNode = new ListNode(u);
    newNode->next = adj[v].head;
    adj[v].head = newNode;
    adj[v].degree++;
}

// Function to perform DFS to check connectivity
void DFS(AdjList* adj, int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (ListNode* node = adj[v].head; node != nullptr; node = node->next) {
        if (!visited[node->vertex]) {
            DFS(adj, node->vertex, visited);
        }
    }
}

// Function to check if all vertices with non-zero degree are connected
bool isConnected(AdjList* adj, int n) {
    std::vector<bool> visited(n, false);
    int startVertex = -1;

    // Find a vertex with non-zero degree to start DFS
    for (int i = 0; i < n; ++i) {
        if (adj[i].degree > 0) {
            startVertex = i;
            break;
        }
    }

    // If there are no edges in the graph, it is trivially connected
    if (startVertex == -1) {
        return true;
    }

    // Perform DFS from the start vertex
    DFS(adj, startVertex, visited);

    // Check if all vertices with non-zero degree are visited
    for (int i = 0; i < n; ++i) {
        if (adj[i].degree > 0 && !visited[i]) {
            return false;
        }
    }

    return true;
}



// Function to check if an Eulerian cycle exists
bool hasEulerianCycle(AdjList* adj, int n) {
    // Check if all vertices with non-zero degree are connected
    if (!isConnected(adj, n)) {
        std::cout << "The graph is not connected." << std::endl;
        return false;
    }

    // Check if every vertex has an even degree
    for (int i = 0; i < n; ++i) {
        if (adj[i].degree % 2 != 0) {
            std::cout << "Vertex " << i << " has an odd degree (" << adj[i].degree << ")." << std::endl;
            return false;
        }
    }

    return true;
}

// Function to generate a random graph
void generateRandomGraph(AdjList* adj, int n, int m, unsigned int seed) {
    std::srand(seed);
    for (int i = 0; i < m; ++i) {
        int u = std::rand() % n;
        int v = std::rand() % n;
        while (v == u) { // Ensure u != v to avoid self-loops
            v = std::rand() % n;
        }
        addEdge(adj, u, v);
    }
}

int main(int argc, char* argv[]) {
    int n = 0; // vertices
    int m = 0; // edges
    unsigned int seed = static_cast<unsigned int>(std::time(0)); // random seed

    int opt;
    while ((opt = getopt(argc, argv, "n:m:s:")) != -1) {
        switch (opt) {
        case 'n':
            n = std::atoi(optarg);
            break;
        case 'm':
            m = std::atoi(optarg);
            break;
        case 's':
            seed = static_cast<unsigned int>(std::atoi(optarg));
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " -n <vertices> -m <edges> -s <seed>" << std::endl;
            return 1;
        }
    }

    if (n <= 0 || m < 0) {
        std::cerr << "Invalid input. Number of vertices must be positive, and number of edges must be non-negative." << std::endl;
        return 1;
    }

    AdjList* adj = new AdjList[n];

    // Generate a random graph
    generateRandomGraph(adj, n, m, seed);
    // Check for Eulerian Cycle
    if (hasEulerianCycle(adj, n)) {
        std::cout << "The graph has an Eulerian cycle." << std::endl;
        // Print the edges of the graph
        
    } else {
        std::cout << "The graph does not have an Eulerian cycle." << std::endl;
    }
    std::cout << "Edges of the graph:" << std::endl;
        for (int i = 0; i < n; ++i) {
            for (ListNode* node = adj[i].head; node != nullptr; node = node->next) {
                if (i < node->vertex) { // To avoid printing duplicate edges
                    std::cout << "(" << i << ", " << node->vertex << ")" << std::endl;
                }
            }
        }
    // Print the degrees of the vertices
    std::cout << "Vertex degrees:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "Vertex " << i << ": " << adj[i].degree << std::endl;
    }

    

    // Clean up the allocated memory for the adjacency list
    for (int i = 0; i < n; ++i) {
        ListNode* current = adj[i].head;
        while (current != nullptr) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] adj;

    return 0;
}
