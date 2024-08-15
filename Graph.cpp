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
    AdjList() : head(nullptr) {}
};

// Function to add an edge to the adjacency list
void addEdge(AdjList* adj, int u, int v) {
    ListNode* newNode = new ListNode(v);
    newNode->next = adj[u].head;
    adj[u].head = newNode;
}



int main() {
    int n; // vertices
    int m; // edges

    std::cout << "Enter number of vertices and edges: " << std::endl;
    while (true) {
        std::cin >> n >> m;
        if (std::cin.fail()  ||n < 0 || m < 0) {
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
            if (std::cin.fail()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter two integers separated by a space: " << std::endl;
            } else {
                addEdge(adj, u, v);
                break; // valid input, exit the loop
            }
        }
    }

  
    delete[] adj; // Clean up the allocated memory for the adjacency list

    return 0;
}