#include <algorithm>
#include <array>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <string>
#include <map>
#include <vector>

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
// -------------------- Завдання 3 --------------------
// 3) std::deque<double> з цінами, функтор Multiplier(rate), обробка через алгоритми.
struct Multiplier {
    double rate;

    explicit Multiplier(double r) : rate(r) {}

    double operator()(double x) const {
        return x * rate;
    }
};

void task3() {
    printHeader("Task 3: deque<double> + functor Multiplier + transform");

    std::deque<double> prices{ 19.99, 35.50, 120.00, 5.25, 87.30 };
    printContainer(prices, "Before");

    const double taxRate = 1.20; // наприклад, +20%
    std::transform(prices.begin(), prices.end(), prices.begin(), Multiplier{taxRate});

    std::cout << std::fixed << std::setprecision(2);
    printContainer(prices, "After (*1.20)");
}

// -------------------- Завдання 4 --------------------
// 4) std::set<int>, функтор WithinRange(min,max) + std::count_if.
struct WithinRange {
    int min;
    int max;

    WithinRange(int mn, int mx) : min(mn), max(mx) {}

    bool operator()(int x) const {
        return x >= min && x <= max;
    }
};

void task4() {
    printHeader("Task 4: set<int> + count_if + WithinRange functor");

    std::set<int> s{ -10, -2, 0, 1, 2, 5, 10, 11, 20, 42 };

    const int min = 0;
    const int max = 10;

    const auto count = std::count_if(s.begin(), s.end(), WithinRange{min, max});
    std::cout << "Elements in [" << min << ", " << max << "] = " << count << '\n';
}
// -------------------- Завдання 5 --------------------
// 5) std::map<string,int> (умовний склад). Використовуючи алгоритми, показати елементи з кількістю > 100.
void task5() {
    printHeader("Task 5: map<string,int> + algorithm to print qty > 100 (lambda)");

    std::map<std::string, int> inventory{
        {"apples", 120},
        {"bananas", 80},
        {"coffee", 250},
        {"tea", 40},
        {"sugar", 101}
    };

    std::for_each(inventory.begin(), inventory.end(), [](const auto& kv) {
        if (kv.second > 100) {
            std::cout << kv.first << " -> " << kv.second << '\n';
        }
    });
}

// -------------------- Завдання 6 --------------------
// 6) std::vector<int>, замінити всі від’ємні числа на 0.
void task6() {
    printHeader("Task 6: vector<int> + replace_if negatives with 0 (lambda)");

    std::vector<int> v{ 5, -3, 10, -100, 0, 7, -1 };
    printContainer(v, "Before");

    std::replace_if(v.begin(), v.end(), [](int x) { return x < 0; }, 0);

    printContainer(v, "After");
}
} // анонімний простір імен

int main() {
    std::cout << "Lab 9: STL algorithms / iterators / containers\n";

    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    return 0;
}