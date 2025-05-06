#include "TapeSorter.h"
#include "FileTape.h"
#include <algorithm>

void TapeSorter::sort() {
  split_and_sort();
  merge_chunks();
}

void TapeSorter::merge_chunks() {
  std::vector<std::unique_ptr<FileTape>> tempTapes;
  for (const auto& filename : M_temp_files_) {
    tempTapes.emplace_back(std::make_unique<FileTape>(filename, M_config_));
  }

  while (!tempTapes.empty()) {
    int32_t minVal = std::numeric_limits<int32_t>::max();
    size_t minIndex = 0;

    for (size_t i = 0; i < tempTapes.size(); ++i) {
      if (!tempTapes[i]->is_end()) {
        int32_t current = tempTapes[i]->read();
        if (current < minVal) {
          minVal = current;
          minIndex = i;
        }
      }
    }

    M_output_tape.write(minVal);
    M_output_tape.move_forward();

    tempTapes[minIndex]->move_forward();

    std::erase_if(tempTapes,
                  [](const auto& tape) {
                    return tape->is_end();
                  });
  }
}


TapeSorter::TapeSorter(TapeDevice& inputTape, TapeDevice& outputTape, size_t maxMemoryBytes, const std::string& cfg)
  : M_input_tape_(inputTape), M_output_tape(outputTape),M_max_memory_bytes_(maxMemoryBytes), M_config_(cfg) {}


void TapeSorter::split_and_sort() {
  std::vector<int32_t> buffer;
  buffer.reserve(M_max_memory_bytes_ / sizeof(int32_t));

  M_input_tape_.reset();
  while (!M_input_tape_.is_end()) {
    buffer.clear();
    for (size_t i = 0; i < buffer.capacity() && !M_input_tape_.is_end(); ++i) {
      buffer.push_back(M_input_tape_.read());
      M_input_tape_.move_forward();
    }

    std::sort(buffer.begin(), buffer.end());

    std::string tempFilename = "tmp/chunk_" + std::to_string(M_temp_files_.size()) + ".bin";
    FileTape tempTape(tempFilename, M_config_);
    for (int32_t num : buffer) {
      tempTape.write(num);
      tempTape.move_forward();
    }

    M_temp_files_.push_back(tempFilename);
  }
}
