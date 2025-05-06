#include "test_classes.h"

namespace fs = std::filesystem;

TEST(TapeSorterTest, SortAlreadySorted) {
    const std::string inputFile = "input.bin";
    const std::string outputFile = "output.bin";
    std::vector<int32_t> data = {1, 2, 3, 4, 5};

  test_class(data).operator()(inputFile, outputFile);
}

TEST(TapeSorterTest, SortReverseOrder) {
    const std::string inputFile = "input.bin";
    const std::string outputFile = "output.bin";
    std::vector<int32_t> data = {5, 4, 3, 2, 1};

  test_class(data).operator()(inputFile, outputFile);
}

TEST(TapeSorterTest, SortWithDuplicates) {
    const std::string inputFile = "input.bin";
    const std::string outputFile = "output.bin";
    std::vector<int32_t> data = {3, 1, 2, 3, 1};

   test_class(data).operator()(inputFile, outputFile);
}