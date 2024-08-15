#include <iostream>
#include <vector>
#include <stack>
#include <limits>

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
        return false;
    }

    // Check if every vertex has an even degree
    for (int i = 0; i < n; ++i) {
        if (adj[i].degree % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int n; // vertices
    int m; // edges

    std::cout << "Enter number of vertices and edges: " << std::endl;
    while (true) {
        std::cin >> n >> m;
        if (std::cin.fail() || n < 0 || m < 0) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter two non-negative integers: " << std::endl;
        } else {
            break; // valid input, exit the loop
        }
    }

    AdjList* adj = new AdjList[n];
    std::cout << "Enter " << m << " pairs of vertices (each pair separated by a space): " << std::endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        while (true) {
            std::cin >> u >> v;
            if (std::cin.fail() || u < 0 || v < 0 || u >= n || v >= n) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter two integers between 0 and " << n-1 << " separated by a space: " << std::endl;
            } else {
                addEdge(adj, u, v);
                break; // valid input, exit the loop
            }
        }
    }

    // Check for Eulerian Cycle
    if (hasEulerianCycle(adj, n)) {
        std::cout << "The graph has an Eulerian cycle." << std::endl;
    } else {
        std::cout << "The graph does not have an Eulerian cycle." << std::endl;
    }

    delete[] adj; // Clean up the allocated memory for the adjacency list

    return 0;
}
