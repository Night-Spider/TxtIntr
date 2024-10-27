#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <string>
#include <unistd.h> // Для getopt

using namespace std;

void printUsage() {
    cout << "Использование: ./stat_calculator -o <operation> <num1> <num2> ... <num8>\n";
    cout << "Где <operation> может быть 'sr' для среднего арифметического или 'med' для медианы.\n";
    cout << "Количество чисел должно быть от 6 до 8.\n";
}

double calculateSR(const vector<double>& numbers) {
    return accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
}

double calculateMed(vector<double> numbers) {
    sort(numbers.begin(), numbers.end());
    size_t size = numbers.size();
    if (size % 2 == 0) {
        return (numbers[size / 2 - 1] + numbers[size / 2]) / 2;
    } else {
        return numbers[size / 2];
    }
}

int main(int argc, char* argv[]) {
    int opt;
    string operation;

    // Обработка аргументов с помощью getopt
    while ((opt = getopt(argc, argv, "o:")) != -1) {
        switch (opt) {
            case 'o':
                operation = optarg;
                break;
            default:
                printUsage();
                return 1;
        }
    }

    // Считываем оставшиеся аргументы (числа)
    vector<double> numbers;
    for (int i = optind; i < argc; ++i) {
        try {
            numbers.push_back(stod(argv[i]));
        } catch (const invalid_argument&) {
            cerr << "Ошибка: '" << argv[i] << "' не является числом." << endl;
            printUsage();
            return 1;
        }
    }

    // Проверка количества чисел
    if (numbers.size() < 6 || numbers.size() > 8) {
        printUsage();
        return 1;
    }

    // Выполнение операции
    if (operation == "sr") {
        double mean = calculateSR(numbers);
        cout << "Среднее арифметическое: " << mean << endl;
    } else if (operation == "med") {
        double median = calculateMed(numbers);
        cout << "Медиана: " << median << endl;
    } else {
        cerr << "Ошибка: Неизвестная операция '" << operation << "'.\n";
        printUsage();
        return 1;
    }

    return 0;
}
