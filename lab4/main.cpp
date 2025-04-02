#include <chrono>
#include <vector>

#include "BinarySearchTree/binary_search_tree.h"

size_t lcg()
{
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

template <class Func>
auto measureTime(Func func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void experiment(int size)
{
    BinarySearchTree<int> tree;

    auto fillTime = measureTime([&]()
                                {
        for (int i = 0; i < size; ++i) {
            tree.insert(lcg());
        } });

    int searchCount = 1000;
    auto searchTime = measureTime([&]()
                                  {
        for (int i = 0; i < searchCount; ++i) {
            tree.contains(lcg());
        } });

    int modifyCount = 1000;
    auto modifyTime = measureTime([&]()
                                  {
        for (int i = 0; i < modifyCount; ++i) {
            int num = lcg();
            tree.insert(num);
            tree.erase(num);
        } });

    std::cout << "Size: " << size << "\n";
    std::cout << "Fill time: " << fillTime << " us" << "\n";
    std::cout << "Search time: " << searchTime << " us" << "\n";
    std::cout << "Modify time: " << modifyTime << " us" << "\n";
}

void compareWithVector(int size)
{
    std::vector<int> vec;

    auto fillTime = measureTime([&]()
                                {
        for (int i = 0; i < size; ++i) {
            vec.push_back(lcg());
        } });

    int searchCount = 1000;
    auto searchTime = measureTime([&]()
                                  {
        for (int i = 0; i < searchCount; ++i) {
            auto it = std::find(vec.begin(), vec.end(), lcg());
        } });

    int modifyCount = 1000;
    auto modifyTime = measureTime([&]()
                                  {
        for (int i = 0; i < modifyCount; ++i) {
            vec.push_back(lcg());
            vec.pop_back();
        } });

    std::cout << "Vector size: " << size << "\n";
    std::cout << "Fill time: " << fillTime << " us" << "\n";
    std::cout << "Search time: " << searchTime << " us" << "\n";
    std::cout << "Modify time: " << modifyTime << " us" << "\n";
}

int main()
{
    BinarySearchTree<int> tree1;
    tree1.insert(100);
    tree1.insert(50);
    tree1.insert(51);
    std::cout << "tree1: ";
    tree1.print();

    BinarySearchTree<int> tree2(tree1);
    tree2.insert(75);
    tree2.insert(110);
    BinarySearchTree tree3 = tree1;
    tree3.insert(25);
    tree3.insert(120);
    std::cout << "tree1: ";
    tree1.print();
    std::cout << "tree2: ";
    tree2.print();
    std::cout << "tree3: ";
    tree3.print();

    std::cout << "75 is in tree1: " << tree1.contains(75) << "\n"
              << "75 is in tree2: " << tree2.contains(75) << "\n";

    tree1.erase(100);
    tree2.erase(75);
    tree3.erase(50);
    std::cout << "tree1: ";
    tree1.print();
    std::cout << "tree2: ";
    tree2.print();
    std::cout << "tree3: ";
    tree3.print();

    BinarySearchTreeWithDuplicates<int> tree4;
    tree4.insert(8);
    tree4.insert(3);
    tree4.insert(6);
    tree4.insert(10);
    tree4.insert(11);
    tree4.insert(6);
    tree4.insert(10);
    tree4.insert(10);
    std::cout << "tree4: ";
    tree4.print();
    tree4.erase(10);
    std::cout << "tree4: ";
    tree4.print();

    std::cout << "tree3: ";
    for (auto key : tree3) std::cout << key << " ";
    std::cout << "\n";

    std::cout << "tree1 is in tree2: " << is_include(tree1, tree2) << "\n";
    std::cout << "tree1 is in tree3: " << is_include(tree1, tree3) << "\n";

    std::cout << "\n";

    int sizes[] = {1000, 10000, 100000};
    for (int size : sizes)
    {
        experiment(size);
        compareWithVector(size);
    }

    return 0;
}