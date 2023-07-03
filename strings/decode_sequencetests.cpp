/**
 * @file decode_sequencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DecodeSequence
 * @version 0.1
 * @date 2023-07-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "decode_sequence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::decode_sequence;

// Test Fixture Data Class
class DecodeSequenceData {
    std::string m_seq, m_expected;
public:
    DecodeSequenceData() = default;

    std::string const & get_seq() { return m_seq; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DecodeSequenceData &);
    friend std::istream& operator>>(std::istream&, DecodeSequenceData &);

};

std::ostream& operator<<(std::ostream& out, const DecodeSequenceData & data) {
    return out << "DecodeSequenceData [ seq=\"" << data.m_seq << "\" expected=\""
        << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, DecodeSequenceData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > seqLoader(data.m_seq);
    in >> seqLoader;

    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class DecodeSequenceFixture :
    public testing::TestWithParam<DecodeSequenceData> {
};

// Parameterized Test Definition
TEST_P(DecodeSequenceFixture, DecodeSequenceTests) {
    DecodeSequenceData data = GetParam();

    Solution solution;

    std::string actual = solution.decode(data.get_seq());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DecodeSequenceTests, DecodeSequenceFixture, testing::ValuesIn(
    Loader<DecodeSequenceData>()(find_path("strings/data/decode_sequence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
