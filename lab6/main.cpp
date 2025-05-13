#include "graph.h"

int main() {
    // Пример использования класса Graph
    Graph<std::string, double> trade_points;

    // Добавляем торговые точки
    trade_points.add_vertex("A");
    trade_points.add_vertex("B");
    trade_points.add_vertex("C");
    trade_points.add_vertex("D");
    trade_points.add_vertex("E");

    // Добавляем пути между ними с расстояниями
    trade_points.add_edge("A", "B", 2.0);
    trade_points.add_edge("B", "A", 2.0);
    trade_points.add_edge("A", "C", 1.0);
    trade_points.add_edge("C", "A", 1.0);
    trade_points.add_edge("B", "C", 3.0);
    trade_points.add_edge("C", "B", 3.0);
    trade_points.add_edge("B", "D", 5.0);
    trade_points.add_edge("D", "B", 5.0);
    trade_points.add_edge("C", "D", 2.0);
    trade_points.add_edge("D", "C", 2.0);
    trade_points.add_edge("D", "E", 4.0);
    trade_points.add_edge("E", "D", 4.0);

    // Проверяем связность графа
    std::cout << "Graph is connected: " << std::boolalpha << trade_points.is_connected() << std::endl;

    // Находим оптимальное место для склада
    std::string warehouse = find_optimal_warehouse(trade_points);
    std::cout << "Optimal warehouse location: " << warehouse << std::endl;

    // Вычисляем кратчайший путь от A до E
    auto path = trade_points.shortest_path("A", "E");
    std::cout << "Shortest path from A to E: ";
    double total_distance = 0;
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << "), ";
        total_distance += edge.distance;
    }
    std::cout << "\nTotal distance: " << total_distance << std::endl;

    // Демонстрация обхода графа
    std::cout << "DFS traversal from A:\n";
    trade_points.walk("A", [](const std::string& vertex) {
        std::cout << "Visited: " << vertex << std::endl;
    });

    // Получаем вектор вершин при обходе
    std::vector<std::string> visited_vertices;
    trade_points.walk("A", [&visited_vertices](const std::string& vertex) {
        visited_vertices.push_back(vertex);
    });

    std::cout << "Visited vertices in order: ";
    for (const auto& v : visited_vertices) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}