/**
 * @file merge_arrays_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution to the problem https://www.techiedelight.com/?problem=MergeArraysII
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "merge_arrays_two.h"

using namespace valhalla::arrays::merge_arrays_two;

#include <iostream>

using namespace std;

class MergeArraysTwoData {
    vector<int> m_actualX, m_actualY, m_expected;

public:
    MergeArraysTwoData() = default;

    MergeArraysTwoData(vector<int> actualX, vector<int> actualY, vector<int> expected)
        : m_actualX(actualX), m_actualY(actualY), m_expected(expected) {}

    MergeArraysTwoData(const MergeArraysTwoData& other) {
        m_actualX = other.m_actualX;
        m_actualY = other.m_actualY;
        m_expected = other.m_expected;
    }

    const vector<int>& GetActualX() { return m_actualX; }
    const vector<int>& GetActualY() { return m_actualY; }
    const vector<int>& GetExpected() { return m_expected; }

    friend ostream& operator<<(ostream&, const MergeArraysTwoData&);
};

std::ostream& operator<<(std::ostream& out, const MergeArraysTwoData &data) {
    out << "{ ";
    out << "Actual X: [";
    for(int value : data.m_actualX) {
        out << " " << value;
    }
    out << " ] and Actual Y: [";
    for(int value : data.m_actualY) {
        out << " " << value;
    }
    out << " ] ==> Expected: [";
    for(int value : data.m_expected) {
        out << " " << value;
    }
    out << " ] }";

    return out;
}

class MergeArraysTwoFixture :
    public testing::TestWithParam<MergeArraysTwoData> {
private:
    MergeArraysTwoData data;

protected:
    void SetUp() override {
        data = GetParam();
    }

    const vector<int>& GetActualX() { return data.GetActualX(); }
    const vector<int>& GetActualY() { return data.GetActualY(); }
};

std::ostream& operator<<(std::ostream& out, const vector<int> &values) {
    out << "[";
    for(int value : values) {
        out << " " << value;
    }
    out << " ]";

    return out;
}

TEST_P(MergeArraysTwoFixture, MergeArraysTwo) {
    Solution solution;

    MergeArraysTwoData data = GetParam();

    cout << "Data: " << data << endl;

    vector<int> actualX(data.GetActualX());
    vector<int> actualY(data.GetActualY());

    solution.merge(actualX, actualY);

    cout << "Actual: " << actualX << endl;

    ASSERT_EQ(actualX, data.GetExpected());
}

INSTANTIATE_TEST_SUITE_P(MergeArraysTwo, MergeArraysTwoFixture,
    testing::Values(
        MergeArraysTwoData({},{},{}),
        MergeArraysTwoData({0,2},{1},{1,2}),
        MergeArraysTwoData({0, 2, 0, 3, 0, 5, 6, 0, 0},{1, 8, 9, 10, 15},{1, 2, 3, 5, 6, 8, 9, 10, 15}),
        MergeArraysTwoData({1,0},{2},{1,2}),
        MergeArraysTwoData({0, 0, 0, 0, 0}, {1, 2, 5, 8, 10}, {1, 2, 5, 8, 10}),
        MergeArraysTwoData({0, 1, 0, 0, 0, 2}, {0, 0, 0, 0}, {0, 0, 0, 0, 1, 2}),
        MergeArraysTwoData({-10, 0, -5, 0, -2}, {-9, -6}, {-10, -9, -6, -5, -2}),
        MergeArraysTwoData({0, 2, 0, 3, 0, 5, 6, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 2, 3, 5, 6}),
        MergeArraysTwoData({0, 0, 0, 0}, {-1, 1}, {-1, 0, 0, 1})
    ));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
