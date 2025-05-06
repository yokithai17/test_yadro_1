#include "FileTape.h"
#include "TapeSorter.h"
#include <iostream>

int main(int args, char* argv[]) {
  if (args != 4) {
    std::cerr << "Usage: " << argv[0] << "./turing <input> <output>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string input = argv[1];
  std::string output = argv[2];
  std::string config = argv[3];

  FileTape input_tape(input, config);
  FileTape output_tape(output, config);

  TapeSorter sorter(input_tape, output_tape, 1024, config);
  sorter.sort();
}
