#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub)
{
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(empty_size_pushback)
{
    List<int> testList;

    ASSERT_TRUE(testList.empty());

    // edge case - negative number doesn't subtract from size
    List<int> testList2;
    testList2.push_back(5);
    testList2.push_back(7);
    testList2.push_back(-20);

    ASSERT_FALSE(testList2.empty());
    ASSERT_EQUAL(testList2.size(), 3);

    // edge case - all 0's don't mean list is empty
    List<int> testList3;
    testList3.push_back(0);
    testList3.push_back(0);
    testList3.push_back(0);

    ASSERT_FALSE(testList3.empty());
    ASSERT_EQUAL(testList3.size(), 3);
}

TEST(empty_size_pushfront)
{
    List<int> testList;

    // can't put a decimal since type is int? not an edge case?
    testList.push_front(5);
    testList.push_front(30);
    testList.push_front(-20);
    testList.push_front(40);
    testList.push_front(0);

    ASSERT_FALSE(testList.empty());
    ASSERT_EQUAL(testList.size(), 5);
}

TEST(front_back_pushfrontback)
{
    List<int> testList;

    testList.push_front(5);
    testList.push_front(30);
    testList.push_back(0);
    testList.push_back(0);
}

TEST_MAIN()
