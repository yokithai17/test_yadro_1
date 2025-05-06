#pragma once

#include <cstdint>

class TapeDevice
{
public:
    virtual ~TapeDevice() = default;
    virtual int32_t read() = 0;
    virtual void write(int32_t data) = 0;
    virtual void move_forward() = 0;
    virtual void move_backward() = 0;
    virtual void reset() = 0;
    virtual bool is_end() const = 0;
};
