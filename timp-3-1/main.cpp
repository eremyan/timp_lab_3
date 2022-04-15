#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <stdexcept>
#include "modAlphaCipher.h"
using namespace std;
struct KeyBoba_fixture {
    
    modAlphaCipher * p;
    KeyBoba_fixture()
    {
        p = new modAlphaCipher(L"АБОБА");
    }
    ~KeyBoba_fixture()
    {
        delete p;
    }
};

SUITE(TestKey)
{

    TEST(ValidKey) {
        modAlphaCipher cipher(L"АБВГ");

        CHECK(true);
    }

    TEST(KeyUp) {
        modAlphaCipher cipher(L"АБВГДЕ");
        
        CHECK(true);
    }

    TEST(KeyLower) {
        modAlphaCipher cipher(L"абвг");
        
        CHECK(true);
    }

    TEST(NumInKey) {
        
        CHECK_THROW(modAlphaCipher cipher(L"д1"),cipher_error);
    }

    TEST(SignesInKey) {
        
        CHECK_THROW(modAlphaCipher cipher(L"а,б,в"),cipher_error);

    }

    TEST(SpaceInKey) {
    
        CHECK_THROW(modAlphaCipher cipher(L"а б в"), cipher_error);
    }

}

SUITE(EncryptTest)
{
    
    
    TEST_FIXTURE(KeyBoba_fixture, SignesInText) {
        wstring open_text=L"БЮП, САБПШ";
        
        CHECK_THROW(p->encrypt(open_text), cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, digits) {
        wstring open_text=L"пять5шесть6";
        
        CHECK_THROW(p->encrypt(open_text),cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, EmptyText) {
        wstring open_text=L"";
        
        CHECK_THROW(p->encrypt(open_text),cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, NonAlpha) {
        wstring open_text=L"555+777";
        
        CHECK_THROW(p->encrypt(open_text), cipher_error);
    }
    
    TEST(MaxShift) {
        const wstring key=L"Я";
        modAlphaCipher cipher(key);
        wstring open_text=L"ЯМАЛОНЕНЕЦКИЙОКРУГ";
        wstring res=L"ЮЛЯКНМДМДХЙЗИНЙПТВ";
        
        CHECK_EQUAL(true,res==cipher.encrypt(open_text));
    }
    
    
}

SUITE(DecryptTest)
{
    
    TEST_FIXTURE(KeyBoba_fixture, SignesInText) {
        wstring cipher_text=L"БЮП, САБПШ";
        
        CHECK_THROW(p->decrypt(cipher_text), cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, digits) {
        wstring cipher_text=L"пять5шесть6";
        
        CHECK_THROW(p->decrypt(cipher_text), cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, EmptyText) {
        wstring cipher_text=L"";
        
        CHECK_THROW(p->decrypt(cipher_text), cipher_error);
    }
    
    TEST_FIXTURE(KeyBoba_fixture, NonAlpha) {
        wstring cipher_text=L"555+777";
        
        CHECK_THROW(p->decrypt(cipher_text), cipher_error); 
    }
    
    TEST(MaxShift) {
        const wstring key=L"Я";
        modAlphaCipher cipher(key);
        wstring cipher_text=L"ЮЛЯКНМДМДХЙЗИНЙПТВ";
        wstring res=L"ЯМАЛОНЕНЕЦКИЙОКРУГ";
        
        CHECK_EQUAL(true,res==cipher.decrypt(cipher_text));
    }
}

int main()
{
    return UnitTest::RunAllTests();
}