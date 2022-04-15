#include <UnitTest++/UnitTest++.h>
#include <codecvt>
#include <stdexcept>
#include "modAlphaCipher.h"
#include <iostream>
using namespace std;


SUITE(TestKey)
{
    
    TEST(ValidKey) {

        CHECK_EQUAL(false, cipher_error::getValidKey("5"));
    }

    TEST(LongKey) {

        CHECK_EQUAL(false, cipher_error::getValidKey("9"));
    }

    TEST(NegativeKey) {

        CHECK_THROW(cipher_error::getValidKey("-5"), cipher_error);
    }

    TEST(SymbolsInKey) {

        CHECK_THROW(cipher_error::getValidKey("Bob..."), cipher_error);
    }

    TEST(SpacesInKey) {

        CHECK_THROW(cipher_error::getValidKey("5 5"), cipher_error);
    }

    TEST(EmptyKey) {

        CHECK_THROW(cipher_error::getValidKey(""), cipher_error);
    }
}

SUITE(EncryptTest)
{
    const int key=5;
    RouteTableCipher cipher(key);

    TEST(AlphaUp) {

        CHECK_EQUAL("I T X E TK", cipher.encrypt("TEXTIK", key));
    }

    TEST(AlphaDown) {

        CHECK_EQUAL("i t x e tk", cipher.encrypt("textik", key));
    }

    TEST(SignesInText) {

        CHECK_EQUAL("or lo lw e dH,l", cipher.encrypt("Hello, world", key));
    }

    TEST(RussianAlpha) {

        CHECK_THROW(cipher_error::getValidText("Русский язык"), cipher_error);
    }

    TEST(digits) {

        CHECK_EQUAL("53 05 03 85 855", cipher.encrypt("88005553535", key));
    }

    TEST(NoAlpha) {

        CHECK_EQUAL("7 + 5 5757", cipher.encrypt("555+777", key));
    }

    TEST(EmptyText) {

        CHECK_THROW(cipher_error::getValidText(""), cipher_error);
    }
}

SUITE(DecryptTest)
{
    const int key=5;
    RouteTableCipher cipher(key);

    TEST(RussianAlpha) {
      
        CHECK_THROW(cipher_error::getValidText("Русский язык"), cipher_error);
    }

    TEST(EmptyText) {

        CHECK_THROW(cipher_error::getValidText(""), cipher_error);

    }

}


int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}