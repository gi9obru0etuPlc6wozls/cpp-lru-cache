#include <thread>
#include "lrucache.hpp"
#include "gtest/gtest.h"

const int NUM_OF_TEST1_RECORDS = 50000;
const int NUM_OF_TEST2_RECORDS = 50000;
const int TEST2_CACHE_CAPACITY = 50;

TEST(CacheTest, SimplePut) {
    cache::lru_cache<int, int> cache_lru(1);
    cache_lru.put(7, 777);
    EXPECT_TRUE(cache_lru.exists(7));
    EXPECT_EQ(777, cache_lru.get(7));
    EXPECT_EQ(1, cache_lru.size());
}

TEST(CacheTest, MissingValue) {
    cache::lru_cache<int, int> cache_lru(1);
    EXPECT_THROW(cache_lru.get(7), std::range_error);
}

TEST(CacheTest1, KeepsAllValuesWithinCapacity) {
    cache::lru_cache<int, int> cache_lru(TEST2_CACHE_CAPACITY);

    for (int i = 0; i < NUM_OF_TEST2_RECORDS; ++i) {
        cache_lru.put(i, i);
    }

    for (int i = 0; i < NUM_OF_TEST2_RECORDS - TEST2_CACHE_CAPACITY; ++i) {
        EXPECT_FALSE(cache_lru.exists(i));
    }

    for (int i = NUM_OF_TEST2_RECORDS - TEST2_CACHE_CAPACITY; i < NUM_OF_TEST2_RECORDS; ++i) {
        EXPECT_TRUE(cache_lru.exists(i));
        EXPECT_EQ(i, cache_lru.get(i));
    }

    size_t size = cache_lru.size();
    EXPECT_EQ(TEST2_CACHE_CAPACITY, size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //int ret = RUN_ALL_TESTS();
    std::thread t1(RUN_ALL_TESTS);
    std::thread t2(RUN_ALL_TESTS);
    std::thread t3(RUN_ALL_TESTS);
    std::thread t4(RUN_ALL_TESTS);
    std::thread t5(RUN_ALL_TESTS);
    std::thread t6(RUN_ALL_TESTS);
    std::thread t7(RUN_ALL_TESTS);
    std::thread t8(RUN_ALL_TESTS);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    return 0;
}
