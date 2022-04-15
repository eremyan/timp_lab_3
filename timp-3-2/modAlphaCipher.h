#pragma once
#include <string>
#include <locale>
#include <stdexcept>
#include <cctype>

using namespace std;
class RouteTableCipher
{
private:
    int key;// ключ (число столбцов)
public:
    RouteTableCipher()=delete;
    RouteTableCipher(const int& skey); // конструктор для установки ключа
    string encrypt(string open_text, const int& skey); // метод шифрования
    string decrypt(string cipher_text, const int& skey); // метод расшифрования

};

class cipher_error: public invalid_argument
{
public:
    explicit cipher_error (const string& what_arg):
        invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        invalid_argument(what_arg) {}
    static int getValidKey(const string skey);
    static int getValidText(const string text);
};