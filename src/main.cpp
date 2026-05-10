#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <random>
#include <string>

namespace {

std::mt19937 makeRng() {
    std::random_device rd;
    return std::mt19937{rd()};
}

void printHeader(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

template <typename Container>
void printContainer(const Container& c, const std::string& label) {
    std::cout << label << ": ";
    for (const auto& x : c) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

// -------------------- Завдання 1 --------------------
// 1) std::list<int> (20 елементів), випадкове заповнення. Функція bool isOdd(int).
bool isOdd(int n) {
    return (n % 2) != 0;
}

void task1() {
    printHeader("Task 1: list<int> + remove_if + isOdd() function");

    std::list<int> values;
    auto rng = makeRng();
    std::uniform_int_distribution<int> dist(-50, 50);

    for (int i = 0; i < 20; ++i) {
        values.push_back(dist(rng));
    }

    printContainer(values, "Before");

    // ПРИМІТКА: std::remove_if не видаляє елементи зі std::list, а лише «пересуває» їх.
    // Для std::list ідіоматично: values.remove_if(...), або erase(remove_if(...)).
    // Тут робимо явно як у вимозі: std::remove_if + erase.
    values.erase(std::remove_if(values.begin(), values.end(), isOdd), values.end());

    printContainer(values, "After (odd removed)");
}

// -------------------- Завдання 2 --------------------
// 2) std::array<string> з іменами, порівняння за довжиною, сортування.
bool shorterByLength(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

void task2() {
    printHeader("Task 2: array<string> + sort by length (function pointer)");

    std::array<std::string, 8> names{ "Oleh", "Anastasiia", "Ira", "Dmytro", "Kateryna", "Li", "Yaroslav", "Maks" };
    printContainer(names, "Before");

    std::sort(names.begin(), names.end(), shorterByLength);

    printContainer(names, "After (sorted by length)");
}

} // анонімний простір імен

int main() {
    std::cout << "Lab 9: STL algorithms / iterators / containers\n";

    task1();
    task2();

    return 0;
}