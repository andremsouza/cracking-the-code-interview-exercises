// Given a directed graph, design an algorithm to find out whether there is a
// route between two nodes

// * Solution: implementing DFS and BFS (iteratively)
// * BFS may be more useful to find the shortest path between two nodes.
// * DFS is simpler, and may be implemented recursively.

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

typedef unsigned int uint;

class Graph {
 private:
  std::vector<std::vector<int>> adj_list_;
  uint node_number_;

 public:
  Graph(uint node_number);

  void AddEdge(uint src, uint dst);

  bool BFS(uint src, uint dst);
  bool DFS(uint src, uint dst);

  void Print();
};

Graph::Graph(uint node_number) : node_number_(node_number) {
  adj_list_.resize(node_number_);
}

void Graph::AddEdge(uint src, uint dst) { adj_list_[src].push_back(dst); }

bool Graph::BFS(uint src, uint dst) {
  // keep track of visited nodes
  std::vector<bool> visited(node_number_, false);
  // use a queue to control node visit order
  // initialize with src array
  std::queue<uint> queue({src});

  // iterate while queue is not empty
  while (!queue.empty()) {
    // pop node from queue
    auto cur = queue.front();
    queue.pop();

    // check if cur == dst.
    if (cur == dst) {
      return true;
    }

    // if not visited, mark as visited
    if (!visited[cur]) {
      visited[cur] = true;
    }

    // push all unvisited neighbors of cur to queue
    for (const auto &i : adj_list_[cur]) {
      if (!visited[i]) {
        queue.push(i);
      }
    }
  }
  // return false if dst has not been found in the graph
  return false;
}

bool Graph::DFS(uint src, uint dst) {
  // keep track of visited nodes
  std::vector<bool> visited(node_number_, false);
  // use a stack to control node visit order
  // initialize with src array
  std::stack<uint> stack({src});

  // iterate while stack is not empty
  while (!stack.empty()) {
    // pop node from stack
    auto cur = stack.top();
    stack.pop();

    // check if cur == dst.
    if (cur == dst) {
      return true;
    }

    // if not visited, mark as visited
    if (!visited[cur]) {
      visited[cur] = true;
    }

    // push all unvisited neighbors of cur to stack
    for (const auto &i : adj_list_[cur]) {
      if (!visited[i]) {
        stack.push(i);
      }
    }
  }
  // return false if dst has not been found in the graph
  return false;
}

void Graph::Print() {
  for (int i = 0; i < (int)node_number_; i++) {
    // print current vertex number
    std::cout << i << " --> ";
    // print all neighboring vertices of vertex i
    for (int v : adj_list_[i]) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  // testing implementation
  Graph g(5);
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(1, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 2);
  g.AddEdge(4, 0);
  g.AddEdge(2, 1);
  g.AddEdge(2, 4);

  g.Print();

  std::cout << "BFS(0 to 4): " << g.BFS(0, 4) << std::endl;
  std::cout << "DFS(0 to 4): " << g.DFS(0, 4) << std::endl;

  return 0;
}
