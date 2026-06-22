#include <gtest/gtest.h>
#include "cli/parser.hpp"

TEST(CliParser, DefaultThreshold) {
    astra::CliOptions opts;
    EXPECT_FLOAT_EQ(opts.threshold, 0.5f);
}

TEST(CliParser, DefaultWindowSize) {
    astra::CliOptions opts;
    EXPECT_EQ(opts.window_size, 5);
}
