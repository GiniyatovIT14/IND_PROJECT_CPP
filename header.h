#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

// функции, отвечающие за подсчет значения многочлена
string SumOfNum(string num1, string num2);

string MultOfDigit(string num, char digit, int zeroes);

string MultOfNum(string num1, string num2);

string PowerOfArg(string base, int power);

string PolySumm(string* coeff, int k, string x);

// функция, проверяющая корректность ввода
bool ChechkForCorr(string str);

// функции, отвечающие за форматированный вывод.
string ForwardZeroes(string str);

string Triada(string str);

string PolyOutput(string* coeff, int k_n, string x_val);
