#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

string SumOfNum(string num1, string num2) {   // функция для сложения двух больших чисел столбиком
    string result;
    int addit = 0;   // число, которое добавляется в следующий разряд (если значение вычислений выходит за 9)
    int i = num1.size() - 1;   // индексы последних разрядов чисел                      
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || addit) {   // цикл продолжается до тех пор, пока есть разряд или перенос
        int summ = addit;                 // проверяем на наличие разрядов в числах и, переобразуя их, добавляем в сумму
        if (i >= 0)
            summ += (num1[i--] - '0');
        if (j >= 0)
            summ += (num2[j--] - '0');
        result.push_back((summ % 10) + '0');   // добавление последней цифры суммы в результат
        addit = summ / 10;   // обновление переноса
    }

    reverse(result.begin(), result.end());  // переворачиваем полученный результат, т.к мы добавляли цифры в обратном порядке
    return result;
}

// следующие две функции поразрядно умножают два числа столбиком
string MultOfDigit(string num, char digit, int zeroes) {   // функция для умножения большого числа на одну цифру
    int addit = 0;   //перменная для переноса
    string result(zeroes, '0');   // инициализируем переменную, заполненную нулями, соответсвующими количеству разярдов
    int digitInt = digit - '0';   // перевод в численный формат

    // поразрядное умножение
    for (int i = num.size() - 1; i >= 0; i--) {
        int mult = (num[i] - '0') * digitInt + addit;    //умножаем на текущую цифру, учитывая переносное значение
        result.push_back((mult % 10) + '0');    // добавление последней цифры умножения в результат
        addit = mult / 10; // число, которое добавляется в следующий разряд (если значение вычислений выходит за 9)
    }

    while (addit) {
        result.push_back((addit % 10) + '0');   // учитываем возможное оставшееся переносное значение и добавляем его к результату
        addit /= 10;
    }

    reverse(result.begin(), result.end());   // переворачиваем полученный результат, т.к мы добавляли цифры в обратном порядке
    return result;
}

string MultOfNum(string num1, string num2) {   // сама функция, которая реализует умножение двух больших чисел с помощью предыдущей фунции
    string result = "0";   
    int num2_len = num2.size();

    for (int i = num2_len - 1; i >= 0; i--) {                                 // проходим с конца
        string result_mult = MultOfDigit(num1, num2[i], num2_len - 1 - i);    // умножаем num1 на цифру num2 (предварительно получив длину), добавляя необходимые нули
        result = SumOfNum(result, result_mult);                               // суммируем текущий результат
    }

    return result;
}

string PowerOfArg(string base, int power) {    // функция для возведения в степень
    string result = "1";
    string current = base;   // перменная, которая будет хранить текущее значение, возводимое в степень

    while (power > 0) {
        if (power % 2 == 1) {   // умножаем результат на текущее значение если оно нечетное
            result = MultOfNum(result, current);
        }
        current = MultOfNum(current, current);    // имитируем возведение в квадрат
        power /= 2;   // переход к следующей степени
    }

    return result;
}

string PolySumm(string* coeff, int n, string x) {   // функция для вычисления точного значения многочлена
    // Проверка на случай, если n = 0 и a_0 = 0
    if (n == 0 && coeff[0] == "0") {
        return "0"; // // проверка на то, что n и a равны 0
    }

    string result = "0";
    for (int i = n; i >= 0; i--) {   // проходим по коэф., начиная с высшей степени
        string temp = PowerOfArg(x, i);   // возводим в степень
        temp = MultOfNum(temp, coeff[i]);   // умножаем коэф. и параметр
        result = SumOfNum(result, temp);    // суммируем результат и получившееся значение
    }
    return result;
}

bool ChechkForCorr(string str) {   // функция для проверки входных данных
    if (str.empty())
        return false;

    if (str.size() > 1 && str[0] == '0') {   // проверка на ведущие нули 
        return false;
    }

    for (char el : str) {   // проверка, что все символы - цифры
        if (!isdigit(el)) {
            return false;
        }
    }

    return true;
}

string ForwardZeroes(string str) {   // функция для отбрасывания ведущих нулей в выводе
    if (str.empty()) {
        return "0"; // если строка пустая, возвращаем "0"
    }

    int index = 0; // переменная для хранения индекса первого ненулевого символа

    if (index == str.size()) { // если все символы нули, возвращаем 0
        return "0";
    }

    while ((index < str.size()) && (str[index] == '0')) { // поиск первого ненулевого символа
        index++;
    }

    string result;
    for (int i = index; i < str.size(); i++) {
        result += str[i]; // добавляем ненулевые символы в результат
    }

    return result;     // возвращаем строку без ведущих нулей
}

string Triada(string str) {   // функция для представления числа в виде триад (для удобности)
    string final_view;
    int count = 0;   // переменная, которая отслеживает триады

    if (str.empty())   // проверка на то, что n и a равны 0
        return "0";

    for (int i = str.size() - 1; i >= 0; i--) {   // проходим по строке с конца к началу
        if (count > 0 && count % 3 == 0)    // добавляем пробел после каждой третьей цифры
            final_view += ' ';
        final_view += str[i];
        count++;
    }

    reverse(final_view.begin(), final_view.end()); // переворачиваем строку
    return final_view;
}

string PolyOutput(string* coeff, int k_n, string x_val) { // функция для вывода полученного многочлена
    string poly;

    // Проверка на случай, если n = 0 и a_0 = 0
    if (k_n == 0 && coeff[0] == "0") {
        return "0"; // проверка на то, что n и a равны 0
    }

    for (int i = k_n; i >= 0; i--) {
        if (coeff[i] == "0")
            continue;    // пропускаем нулевые коэффициенты

        if (!poly.empty())
            poly += " + ";    // добавляем знак сложения

        if (i == 0)            // собираем и выводим полученный многочлен, требуемого вида
            poly += coeff[i];     // коэффициент
        else if (i == 1)
            poly += coeff[i] + "*" + x_val;    // параметр
        else
            poly += coeff[i] + "*" + x_val + "^" + to_string(i);   // степень
    }

    if (poly.empty()) {
        return "0"; // если все коэффициенты нулевые, возвращаем "0"
    }

    return poly;
}
