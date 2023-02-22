/**
 * @file loadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file will contain different tests that uses the Loader class
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "loader.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::AllOfArray;

class Data {
    static const char m_s_delim = '\t';
    std::string m_data;
    std::string m_value;
public:
    Data() = default;
    Data(std::string data, std::string value) : m_data(data), m_value(value) {}

    friend bool operator==(const Data &, const Data &);
    friend std::istream& operator>>(std::istream&, Data&);
    friend std::ostream& operator<<(std::ostream&, const Data&);
};

bool operator==(const Data & lhs, const Data & rhs) {
    return lhs.m_data == rhs.m_data && lhs.m_value == rhs.m_value;
}

std::ostream& operator<<(std::ostream& out, const Data & data) {
    // write the Data object fields to the stream
    out << data.m_data << data.m_s_delim;
    out << data.m_value << data.m_s_delim;

    return out;
}

std::istream& operator>>(std::istream& is, Data & data) {
    // read the Data object fields from the stream
    std::getline(is, data.m_data, data.m_s_delim);
    std::getline(is, data.m_value, data.m_s_delim);

    return is;
}

TEST(LoaderTestSuite, StringLoaderTests) {
    std::string filename = "string.txt";
    std::vector<Data> expected = { Data("A", "1"), Data("B", "2"), Data("C", "3") };

    // create the test file with the required formatted data
    std::ofstream os(filename);
    for (Data data : expected) {
        os << data;
    } // for
    os.close();

    valhalla::utils::loaders::Loader<Data> loader;

    std::vector<Data> datas = loader(filename);

    ASSERT_EQ(datas, expected);

    // only remove file iff the test was successful
    std::remove(filename.c_str());
}

TEST(LoaderTestSuite, CharLoaderTests) {
    const char * filename = "char.txt";
    std::vector<Data> expected = { Data("A", "1"), Data("B", "2"), Data("C", "3") };

    // create the test file with the required formatted data
    std::ofstream os(filename);
    for (Data data : expected) {
        os << data;
    } // for
    os.close();

    valhalla::utils::loaders::Loader<Data> loader;

    std::vector<Data> datas = loader(filename);

    ASSERT_EQ(datas, expected);

    // only remove file iff the test was successful
    std::remove(filename);
}

TEST(LoaderTestSuite, IStreamLoaderTests) {
    const char * filename = "ifstream.txt";
    std::vector<Data> expected = { Data("A", "1"), Data("B", "2"), Data("C", "3") };

    // create the test file with the required formatted data
    std::ofstream os(filename);
    for (Data data : expected) {
        os << data;
    } // for
    os.close();

    valhalla::utils::loaders::Loader<Data> loader;

    std::ifstream is(filename);

    std::vector<Data> datas = loader(is);

    ASSERT_EQ(datas, expected);

    // only remove file iff the test was successful
    std::remove(filename);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
