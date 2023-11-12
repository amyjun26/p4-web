#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

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

    // edge case - all negatives
    List<int> testList4;
    testList4.push_back(-4);
    testList4.push_back(-30);
    testList4.push_back(-40);

    ASSERT_FALSE(testList4.empty());
    ASSERT_EQUAL(testList4.size(), 3);
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

    // edge case - all 0s
    List<int> testList2;
    testList2.push_front(0);
    testList2.push_front(0);
    testList2.push_front(0);

    ASSERT_FALSE(testList2.empty());
    ASSERT_EQUAL(testList2.size(), 3);
    ASSERT_EQUAL(testList2.front(), 0);
}

TEST(front_back_pushfrontback)
{
    List<int> testList;

    // order should be 30, 5, 0, 10
    testList.push_front(5);
    testList.push_front(30);
    testList.push_back(0);
    testList.push_back(10);

    ASSERT_EQUAL(testList.front(), 30);
    ASSERT_EQUAL(testList.back(), 10);

    // edge case - all negatives
    List<int> testList2;
    testList2.push_front(-10);
    testList2.push_front(-40);
    testList2.push_front(-20);

    ASSERT_EQUAL(testList2.front(), -20);
    ASSERT_EQUAL(testList2.back(), -10);
}

TEST(popfrontback)
{
    List<double> testList;

    // edge case - all decimals
    // -20.4343, 4.6, 3.2, 30.5, 5,7
    testList.push_front(5.7);
    testList.push_front(30.5);
    testList.push_front(3.2);
    testList.push_front(4.6);
    testList.push_front(-20.4343);

    // size and front / back BEFORE pop_back
    ASSERT_EQUAL(testList.size(), 5);
    ASSERT_EQUAL(testList.front(), -20.4343);
    ASSERT_EQUAL(testList.back(), 5.7);
    // size and front / back AFTER pop_back
    testList.pop_back();
    ASSERT_EQUAL(testList.size(), 4);
    ASSERT_EQUAL(testList.front(), -20.4343);
    ASSERT_EQUAL(testList.back(), 30.5);
}

TEST(clear_copyall_copyctor)
{
    List<double> testList;

    testList.push_front(5.7);
    testList.push_front(30.5);
    testList.push_front(3.2);
    testList.push_front(4.6);

    testList.clear();

    ASSERT_EQUAL(testList.size(), 0);

    // testing = operator and the copy constructor
    List<int> testList2;
    List<int> testList3;

    // also an edge case since they're all same number
    testList2.push_back(5);
    testList2.push_back(5);
    testList2.push_back(5);
    testList2.push_back(5);

    // invoking copy_all function, as = operator function copies from testList2
    testList3 = testList2; // also invokes copy ctor
    ASSERT_EQUAL(testList3.size(), testList2.size());
    ASSERT_EQUAL(testList3.front(), testList2.front());
    ASSERT_EQUAL(testList3.back(), testList2.back());

    // see if changing list 3 will change list 2
}

// Iterator is a nested type of a list instantiation. Need List<int>::Iterator.

TEST_MAIN()
