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
#include <cctype>

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

    values.erase(std::remove_if(values.begin(), values.end(), isOdd), values.end());

    printContainer(values, "After (odd removed)");
}

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

void task6() {
    printHeader("Task 6: vector<int> + replace_if negatives with 0 (lambda)");

    std::vector<int> v{ 5, -3, 10, -100, 0, 7, -1 };
    printContainer(v, "Before");

    std::replace_if(v.begin(), v.end(), [](int x) { return x < 0; }, 0);

    printContainer(v, "After");
}
void task7() {
    printHeader("Task 7: vector<int> + sum & average without accumulate");

    std::vector<int> v{ 2, 4, 6, 8, 10 };
    printContainer(v, "Values");
    long long sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });

    const double avg = v.empty() ? 0.0 : static_cast<double>(sum) / static_cast<double>(v.size());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sum = " << sum << ", Average = " << avg << '\n';
}

bool isVowelLatin(char ch) {
    const unsigned char uc = static_cast<unsigned char>(ch);
    const char c = static_cast<char>(std::tolower(uc));
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::size_t countVowelsLatin(const std::string& s) {
    return static_cast<std::size_t>(std::count_if(s.begin(), s.end(), isVowelLatin));
}

void task8() {
    printHeader("Task 8: string + count vowels using count_if (function)");

    const std::string text = "Hello, Ukraine!";
    const auto vowelsCount = countVowelsLatin(text);

    std::cout << "Text: " << text << '\n';
    std::cout << "Vowels (EN) count = " << vowelsCount << '\n';
}
} 

int main() {
    std::cout << "Lab 9: STL algorithms / iterators / containers\n";

    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    return 0;
}