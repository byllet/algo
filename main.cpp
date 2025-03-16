#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
using Graph = std::vector<std::vector<T>>;

template <class T>
std::vector<long long> BFS(const Graph<T>& graph, const T& start_node) {
  std::vector<long long> distances(graph.size(), -1);
  distances[start_node] = 0;

  std::queue<T> q;
  q.push(start_node);
  
  while (!q.empty()) {
    T cur_node = q.front();
    q.pop();
    for (const auto& neighbor : graph[cur_node]) {
      if (distances[neighbor] != -1) {
        continue;
      }

      distances[neighbor] = distances[cur_node] + 1;
      q.push(neighbor);
    }
  }

  return distances;
}

template <class T>
int ReadFromFile(const std::string& filename, Graph<T>& graph, T& start_node) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Cannot open " << filename << "\n ";
    file.close();
    return -1;
  }

  T nodes_count;
  file >> nodes_count;
  graph = Graph<T>(nodes_count);

  T edges_count;
  file >> edges_count;

  for (std::size_t i = 0; i < edges_count; ++i) {
    T a, b;
    file >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  file >> start_node;
  file.close();

  return 0;
}

int main() {
  Graph<std::size_t> graph;
  std::size_t start_node;

  if (ReadFromFile("graph.txt", graph, start_node) == -1) {
    return 0;
  }

  auto distances = BFS(graph, start_node);
  for (auto& d : distances) {
    std::cout << d << '\n';
  }

  return 0;
}
