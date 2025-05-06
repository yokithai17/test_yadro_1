#pragma once

#include <gtest/gtest.h>
#include "TapeSorter.h"
#include "FileTape.h"
#include <vector>
#include <algorithm>
#include <filesystem>

void createTestFile(const std::string& filename, const std::vector<int32_t>& data);

std::vector<int32_t> readTape(const std::string& filename);

struct test_class {
  test_class(const std::vector<int32_t>& v) : v(v) {};

  void operator()(const std::string& inputFile, const std::string& outputFile) const
  {
    namespace fs = std::filesystem;
    createTestFile(inputFile, v);
    {
      FileTape inputTape(inputFile, "config.txt");
      FileTape outputTape(outputFile, "config.txt");
      TapeSorter sorter(inputTape, outputTape, 1024, "config.txt");
      sorter.sort();
    }

    auto result = readTape(outputFile);
    ASSERT_TRUE(std::ranges::is_sorted(result));

    fs::remove(inputFile);
    fs::remove(outputFile);
  }
private:
  std::vector<int32_t> v;
};