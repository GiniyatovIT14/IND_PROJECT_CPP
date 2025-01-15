#include <iostream>
#include <string>
#include <Windows.h>
#include "header.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");

    cout << "\n\tДоброго времени суток! Если тебе стало скучно и ты увлекаешься математикой, то ты попал по адресу!" << endl;
    cout << "\tЗдесь ты можешь составить многочлен вида: P(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0" << endl;
    cout << "\tА я помогу вычислить его. Все, что от тебя требуется это ввести некоторые данные! Ну что, приступим?\n" << endl;

    string nStr; cout << "Введи степень многочлена (n) -> "; cin >> nStr;

    if (!ChechkForCorr(nStr)) {    // проверка на корректность ввода
        cout << "Ох, забыл уточнить: степень многочлена должна быть целым неотрицательным числом без ведущих нулей, давай попробуем заново." << endl;
        return 1;
    }

    int n = 0;   

    int MAX_INT = 2147483647; // максимальное значение для int (опираясь на него проверим на переполнение)
    for (char el : nStr) {
        if (n > (MAX_INT - (el - '0')) / 10) { // проверяем на наличие ереполнения
            cout << "Из головы вылетело: степень многочлена не должна превышать значение INT." << endl;
            return 1; // Переполнение
        }
        n = n * 10 + (el - '0');
    }

    string* coeff = new string[n + 1];     // объявляем динамический массив для коэффициентов
    for (int i = n; i >= 0; i--) {
        cout << "Введи коэффициент a_" << i << " -> "; cin >> coeff[i];
        if (!ChechkForCorr(coeff[i])) {
            cout << "Да... С коэффициентами та же ситуация: коэффициент должен быть целым неотрицательным числом без ведущих нулей." << endl;
            return 1;
        }
    }

    string x; cout << "Введи значение x -> "; cin >> x;
    if (!ChechkForCorr(x)) {
        cout << "Не знаю как сказать, но параметр x тоже должен быть целым неотрицательным числом без ведущих нулей." << endl;
        return 1;
    }

    string polyOutput = PolyOutput(coeff,    n, x); // вывод полученного многочлена
    cout << "\nТак-с, а вот такой 'прекрасный' многочлен мы получили -> " << polyOutput << endl;

    string result = PolySumm(coeff, n, x); // получаем значение многочлена
    result = ForwardZeroes(result);  // убираем ведущие нули
    string formatted_Result = Triada(result);  // форматируем вывод с пробелами (для удобства)

    cout << "\nРаботёнка была не из легких, но я посчитал значение -> " << formatted_Result << endl;    // вывод ответа после всех редактирований
    
    delete[] coeff;   // подчищаем за собой

    return 0;
}
