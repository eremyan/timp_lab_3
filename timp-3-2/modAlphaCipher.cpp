#include "modAlphaCipher.h"
#include <codecvt>
using namespace std;
RouteTableCipher::RouteTableCipher(const int& skey)
{
    key=skey;
}

string RouteTableCipher::encrypt(string open_text, const int& skey)
{
    int height;
    if(open_text.length()%skey!=0)
        height=open_text.length()/skey+1;
    else
        height=open_text.length()/skey;
    char mass[height][skey];
    int k=0;
    for (int i=0; i<height; i++) {
        for (int j=0; j<skey; j++) {
            if (k<open_text.length()) {
                mass[i][j]=open_text[k];
                k++;
            } else
                mass[i][j]=' ';

        }

    }
    string cipher_text;
    for (int i=skey-1; i>=0; i--) {
        for (int j=0; j<height; j++) {
            cipher_text+=mass[j][i];
        }
    }
    return cipher_text;

}

string RouteTableCipher::decrypt(string cipher_text, const int& skey)
{
    int height=cipher_text.length()/skey;
    char mass[skey][height];
    int k=0;
    for(int i=skey-1; i>=0; i--) {
        for(int j=0; j<height; j++) {
            mass[i][j]=cipher_text[k];
            k++;

        }
    }
    string decrypted_text;
    for(int i=0; i<height; i++) {
        for(int j=0; j<skey; j++) {
            decrypted_text+=mass[j][i];
        }
    }
    return decrypted_text;
}

int cipher_error::getValidKey(const string skey)
{
    int tmp;
    if(skey.empty())
        throw cipher_error("Пустой ключ");
    if(skey.find_first_not_of("0123456789",0)!=string::npos)
        throw cipher_error("Недопустимые символы, ключ должен быть числом больше нуля");
    tmp=stoi(skey);
    return 0;
}

int cipher_error::getValidText(const string text)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    if(text.empty())
        throw cipher_error("Текст не должен быть пустым");
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
    wstring wtext=codec.from_bytes(text);
    int len=wtext.length();
    for (int i=0; i<len; i++) {
        if(wtext[i]>=L'А' && wtext[i]<=L'я') {
            if(wtext[i]>=L'а' && wtext[i]<=L'я') {
                throw cipher_error("В тексте не должно быть русских букв");
            }
        }
    }

}