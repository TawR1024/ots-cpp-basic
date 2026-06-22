#include <gtest/gtest.h>
#include "detector/star_detector.hpp"

TEST(StarDetector, DefaultConstruction) {
    astra::StarDetector detector;
    EXPECT_NO_THROW(detector.detect(""));
}

TEST(StarDetector, ZeroStarsOnEmptyPath) {
    astra::StarDetector detector;
    auto result = detector.detect("");
    EXPECT_EQ(result.star_count, 0);
}
