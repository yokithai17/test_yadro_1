#pragma once

#include "TapeDevice.h"
#include <vector>
#include <string>

class TapeSorter
{
public:
    TapeSorter(TapeDevice& inputTape, TapeDevice& outputTape, size_t maxMemory, const std::string& config);
    void sort();

private:
    void split_and_sort();
    void merge_chunks();

    TapeDevice& M_input_tape_;
    TapeDevice& M_output_tape;
    std::string M_config_;
    size_t M_max_memory_bytes_;
    std::vector<std::string> M_temp_files_;
};
