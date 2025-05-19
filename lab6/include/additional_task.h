#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <limits>
#include <functional>
#include <list>
#include "HashTable.h" // Подключаем ваш HashTable

template<class Vertex, class Distance = double>
class Graph {
public:
    struct Edge {
        Vertex _from;
        Vertex _to;
        Distance _distance;

        Edge(const Vertex& f, const Vertex& t, const Distance& d) 
            : _from(f), _to(t), _distance(d) {}

        bool operator==(const Edge& other) const {
            return _from == other._from && _to == other._to && _distance == other._distance;
        }
    };

private:
    HashTable<Vertex, bool> _vertices;  // Храним вершины (ключ - вершина, значение - не используется)
    HashTable<Vertex, std::list<Edge>> _edges;  // Храним рёбра (ключ - вершина, значение - список рёбер)

public:
    bool has_vertex(const Vertex& v) const {
        return _vertices.search(v) != nullptr;
    }

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v)) return false;
        bool dummy = true;
        _vertices.insert(v, dummy);
        return true;
    }

    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) return false;

        // Удаляем все рёбра, исходящие из вершины
        _edges.erase(v);

        // Удаляем все рёбра, входящие в вершину
        for (auto& bucket : _edges) {
            auto& edges_list = bucket.second;
            edges_list.remove_if([&v](const Edge& e) { return e._to == v; });
        }

        // Удаляем саму вершину
        _vertices.erase(v);
        return true;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> result;
        for (const auto& bucket : _vertices) {
            result.push_back(bucket.first);
        }
        return result;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("One or both vertices don't exist");

        Edge new_edge(from, to, d);
        auto* edges_list = _edges.search(from);
        if (edges_list) {
            edges_list->push_back(new_edge);
        } else {
            std::list<Edge> new_list = { new_edge };
            _edges.insert(from, new_list);
        }
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        auto* edges_list = _edges.search(from);
        if (!edges_list) return false;

        size_t initial_size = edges_list->size();
        edges_list->remove_if([&to](const Edge& e) { return e._to == to; });
        return edges_list->size() != initial_size;
    }

    bool remove_edge(const Edge& e) {
        auto* edges_list = _edges.search(e._from);
        if (!edges_list) return false;

        size_t initial_size = edges_list->size();
        edges_list->remove(e);
        return edges_list->size() != initial_size;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        const auto* edges_list = _edges.search(from);
        if (!edges_list) return false;

        for (const auto& edge : *edges_list) {
            if (edge._to == to) return true;
        }
        return false;
    }

    bool has_edge(const Edge& e) const {
        const auto* edges_list = _edges.search(e._from);
        if (!edges_list) return false;

        for (const auto& edge : *edges_list) {
            if (edge == e) return true;
        }
        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex) {
        std::vector<Edge> result;
        const auto* edges_list = _edges.search(vertex);
        if (edges_list) {
            result.assign(edges_list->begin(), edges_list->end());
        }
        return result;
    }

    size_t order() const {
        return _vertices.size();
    }

    size_t degree(const Vertex& v) const {
        const auto* edges_list = _edges.search(v);
        return edges_list ? edges_list->size() : 0;
    }

    bool is_connected() const {
        if (order() == 0) return true;

        for (const auto& start : vertices()) {
            std::set<Vertex> visited;
            std::stack<Vertex> stack;
            stack.push(start);
            visited.insert(start);

            while (!stack.empty()) {
                Vertex current = stack.top();
                stack.pop();

                const auto* edges_list = _edges.search(current);
                if (edges_list) {
                    for (const auto& edge : *edges_list) {
                        Vertex neighbor = edge._to;
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            stack.push(neighbor);
                        }
                    }
                }
            }

            if (visited.size() != order()) return false;
        }
        return true;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) 
            throw std::invalid_argument("One or both vertices don't exist");
        
        std::map<Vertex, Distance> distances;
        std::map<Vertex, Vertex> predecessors;
        for (const auto& v : vertices()) distances[v] = std::numeric_limits<Distance>::max();
        distances[from] = 0;

        for (size_t i = 1; i < order(); ++i) {
            for (const auto& vertex : _edges) {
                for (const auto& edge : vertex.second) {
                    if (distances[edge._from] != std::numeric_limits<Distance>::max() &&
                        distances[edge._to] > distances[edge._from] + edge._distance) {
                        distances[edge._to] = distances[edge._from] + edge._distance;
                        predecessors[edge._to] = edge._from;
                    }
                }
            }
        }

        // Проверка на отрицательные циклы
        for (const auto& vertex : _edges) {
            for (const auto& edge : vertex.second) {
                if (distances[edge._from] != std::numeric_limits<Distance>::max() &&
                    distances[edge._to] > distances[edge._from] + edge._distance) {
                    throw std::runtime_error("Graph contains negative weight cycle");
                }
            }
        }

        if (distances[to] == std::numeric_limits<Distance>::max()) {
            return {};
        }

        std::vector<Edge> path;
        Vertex current = to;
        while (current != from) {
            Vertex prev = predecessors[current];
            Distance min_dist = std::numeric_limits<Distance>::max();
            Edge min_edge(prev, current, min_dist);
            
            const auto* edges_list = _edges.search(prev);
            if (edges_list) {
                for (const auto& edge : *edges_list) {
                    if (edge._to == current && edge._distance < min_dist) {
                        min_dist = edge._distance;
                        min_edge = edge;
                    }
                }
            }
            path.push_back(min_edge);
            current = prev;
        }
        
        std::reverse(path.begin(), path.end());
        return path;
    }

    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
        if (!has_vertex(start_vertex)) {
            throw std::invalid_argument("Vertex doesn't exist");
        }

        std::set<Vertex> visited;
        std::stack<Vertex> stack;
        stack.push(start_vertex);
        visited.insert(start_vertex);

        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();
            action(current);

            const auto* edges_list = _edges.search(current);
            if (edges_list) {
                for (const auto& edge : *edges_list) {
                    Vertex neighbor = edge._to;
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        stack.push(neighbor);
                    }
                }
            }
        }
    }
};

template<typename Vertex, typename Distance = double>
Vertex find_optimal_warehouse(const Graph<Vertex, Distance>& graph) {
    if (!graph.is_connected()) {
        throw std::runtime_error("Graph is not connected");
    }

    std::vector<Vertex> vertices = graph.vertices();
    if (vertices.empty()) {
        throw std::runtime_error("Graph is empty");
    }

    Vertex optimal_vertex;
    Distance min_max_distance = std::numeric_limits<Distance>::max();

    for (const auto& v : vertices) {
        Distance current_max = 0;
        for (const auto& u : vertices) {
            if (v != u) {
                auto path = graph.shortest_path(v, u);
                Distance total_distance = 0;
                for (const auto& edge : path) {
                    total_distance += edge._distance;
                }
                if (total_distance > current_max) {
                    current_max = total_distance;
                }
            }
        }
        if (current_max < min_max_distance) {
            min_max_distance = current_max;
            optimal_vertex = v;
        }
    }

    return optimal_vertex;
}