// Copyright 2025 Peter
#define BOOST_TEST_MODULE RandWriterTests
#include <string>
#include <map>
#include <stdexcept>
#include "RandWriter.hpp"
#include <boost/test/included/unit_test.hpp>

std::map<char, int> countCharFrequencies(const std::string& text) {
    std::map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    return freqMap;
}
/*
BOOST_AUTO_TEST_CASE(test_error_checking) {
    // Sample text for testing
    std::string sampleText = "abcdefghijklmnopqrstuvwxyz";


    BOOST_REQUIRE_NO_THROW(RandWriter writer(sampleText, 3));

    RandWriter writer(sampleText, 3);

    BOOST_REQUIRE_NO_THROW(writer.freq("abc"));
    BOOST_REQUIRE_NO_THROW(writer.freq("abc", 'd'));

    BOOST_REQUIRE_THROW(writer.freq("ab"), std::exception);
    BOOST_REQUIRE_THROW(writer.freq("abcd"), std::exception);

    BOOST_REQUIRE_THROW(writer.freq("ab", 'c'), std::exception);
    BOOST_REQUIRE_THROW(writer.freq("abcd", 'c'), std::exception);

    BOOST_REQUIRE_THROW(writer.kRand("ab"), std::exception);
    BOOST_REQUIRE_THROW(writer.kRand("abcd"), std::exception);

    BOOST_REQUIRE_THROW(writer.kRand("xyz"), std::exception);

    BOOST_REQUIRE_THROW(writer.generate("ab", 10), std::exception);
    BOOST_REQUIRE_THROW(writer.generate("abcd", 10), std::exception);
} */

BOOST_AUTO_TEST_CASE(test_krand) {
    std::string sampleText = "abcabdabeabfabgabhabcabd";
    RandWriter writer(sampleText, 2);

    char result = writer.kRand("ab");
    BOOST_REQUIRE(result == 'c' || result == 'd' || result == 'e' ||
                  result == 'f' || result == 'g' || result == 'h');

    BOOST_REQUIRE_EQUAL(writer.kRand("bc"), 'a');

    bool differentResults = false;
    char firstResult = writer.kRand("ab");

    for (int i = 0; i < 50 && !differentResults; i++) {
        if (writer.kRand("ab") != firstResult) {
            differentResults = true;
        }
    }

    BOOST_REQUIRE(differentResults);
}

BOOST_AUTO_TEST_CASE(test_generate_results) {
    std::string sampleText = "abcabdabeabfabgabhabcabd";
    RandWriter writer(sampleText, 2);
    std::string generated = writer.generate("ab", 10);
    BOOST_REQUIRE_EQUAL(generated.length(), 10);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "ab");
    for (size_t i = 2; i < generated.length(); i++) {
        std::string kgram = generated.substr(i-2, 2);
        char nextChar = generated[i];
        BOOST_REQUIRE_GT(writer.freq(kgram, nextChar), 0);
    }
    generated = writer.generate("bc", 15);
    BOOST_REQUIRE_EQUAL(generated.length(), 15);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "bc");
}

