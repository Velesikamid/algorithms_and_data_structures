#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <stack>
#include <limits>

template<class Vertex, class Distance = double>
class Graph {
public:
    struct Edge {
        Vertex _from;
        Vertex _to;
        Distance _distance;

        Edge(const Vertex& f, const Vertex& t, const Distance& d) : _from(f), _to(t), _distance(d) {}

        bool operator==(const Edge& other) const {
            return _from == other._from && _to == other._to && _distance == other._distance;
        }
    };

private:
    std::vector<Vertex> _vertices;
    std::multimap<Vertex, Edge> _edges;

public:
    bool has_vertex(const Vertex& v) const {
        return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
    }

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v)) return false;
        _vertices.push_back(v);
        return true;
    }

    bool remove_vertex(const Vertex& v) {
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        if (it == _vertices.end()) return false;
        _vertices.erase(it);

        auto range = _edges.equal_range(v);
        _edges.erase(range.first, range.second);

        for (auto it = _edges.begin(); it != _edges.end(); ) {
            if (it->second._to == v) it = _edges.erase(it);
            else ++it;
        }

        return true;
    }

    std::vector<Vertex> vertices() const {
        return _vertices;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("One or both vertices don't exist");
        _edges.insert({ from, Edge(from, to, d) });
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        bool removed = false;
        for (auto it = _edges.begin(); it != _edges.end(); ) {
            if (it->first == from && it->second._to == to) {
                it = _edges.erase(it);
                removed = true;
            } else ++it;
        }
        return removed;
    }

    bool remove_edge(const Edge& e) {
        auto range = _edges.equal_range(e._from);
        for (auto it = range.first; it != range.second; ++ it) {
            if (it->second == e) {
                _edges.erase(it);
                return true;
            }
        }
        return false;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        auto range = _edges.equal_range(from);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second._to == to) return true;
        }
        return false;
    }

    bool has_edge(const Edge& e) const {
        auto range = _edges.equal_range(e._from);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == e) return true;
        }
        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex) {
        std::vector<Edge> result;
        auto range = _edges.equal_range(vertex);
        for (auto it = range.first; it != range.second; ++it) {
            result.push_back(it->second);
        }
        return result;
    }

    size_t order() const {
        return _vertices.size();
    }

    size_t degree(const Vertex& v) const {
        return _edges.count(v)
    }

    bool is_connected() const {
        if (_vertices.empty()) return true;

        for (const auto& start : _vertices) {
            std::set<Vertex> visited;
            std::stack<Vertex> stack;
            stack.push(start);
            visited.insert(start);

            while (!stack.empty()) {
                Vertex current = stack.top();
                stack.pop();

                auto range = _edges.equal_range(current);
                for (auto it = range.first; it != range.second; ++it) {
                    Vertex neighbor = it->second._to;
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        stack.push(neighbor);
                    }
                }
            }

            if (visited.size() != _vertices.size()) return false;
        }
        return true;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) 
            throw std::invalid_argument("One or both vertices don't exist");
        
        std::map<Vertex, Distance> distances;
        std::map<Vertex, Vertex>predecessors;
        for (const auto& v : _vertices) distances[v] = std::numeric_limits<Distance>::max();
        distances[from] = 0;

        for (size_t i = 1; i < _vertices.size(); ++i) {
            for (const auto& edge_pair : _edges) {
                const Edge& e = edge_pair.second;
                if (distances[e._from] != std::numeric_limits<Distance>::max() &&
                    distances[e._to] > distances[e._from] + e._distance) {
                    distances[e._to] = distances[e._from] + e._distance;
                    predecessors[e._to] = e._from;
                }
            }
        }

        for (const auto& edge_pair : _edges) {
            const Edge& e = edge_pair.second;
            if(distances[e._from] != std::numeric_limits<Distance>::max() &&
               distances[e._to] > distance[e._from] + e._distance) {
                throw std::runtime_error("Graph contains negative weight cycle");
            }
        }

        if (distances[to] == std::numeric_limits<Distance>::max()) {
            return {};
        }

        std::vector<Edge> path;
        Vertex current = to;
        while (current != from) {
            Vertex prev = predecessors[current];
            auto range = _edges.equal_range(prev);
            Distance min_dist = std::numeric_limits<Distance>::max();
            Edge min_edge(prev, current, min_dist);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second._to == current && it->second._distance < min_dist) {
                    min_dist = it->second._distance;
                    min_edge = it->second;
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

            auto range = _edges.equal_range(current);
            for (auto it = range.first; it != range.second; ++it) {
                Vertex neighbor = it->second._to;
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    stack.push(neighbor);
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
                    total_distance += edge.distance;
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