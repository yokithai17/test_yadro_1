#pragma once

#include "TapeDevice.h"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

class FileTape final : public TapeDevice
{
public:
    FileTape(const std::string& filename, const std::string& configPath);
    ~FileTape() override;
    int32_t read() override;
    void write(int32_t data) override;
    void move_forward() override;
    void move_backward() override;
    void reset() override;
    bool is_end() const override;

private:
    void load_config(const std::string& configPath);
    void apply_delay(unsigned int milliseconds) const;

    std::fstream M_file_;
    size_t M_position_;
    size_t M_size_;
    unsigned int M_read_delay_{};
    unsigned int M_write_delay{};
    unsigned int M_move_delay{};
    unsigned int M_reset_delay_{};
};
