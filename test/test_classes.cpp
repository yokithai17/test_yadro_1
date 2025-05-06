#include "test_classes.h"


void createTestFile(const std::string& filename, const std::vector<int32_t>& data) {
  std::ofstream file(filename, std::ios::binary);
  for (auto num : data) {
    file.write(reinterpret_cast<const char*>(&num), sizeof(num));
  }
}

std::vector<int32_t> readTape(const std::string& filename) {
  std::vector<int32_t> result;
  FileTape tape(filename, "config.txt");
  tape.reset();
  while (!tape.is_end()) {
    result.push_back(tape.read());
    tape.move_forward();
  }
  return result;
}