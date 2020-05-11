#pragma once

#include <cstdint>

namespace stm32util::time {
    inline void busyWait(const uint32_t clockMHz, const uint32_t delayNs) {
        volatile uint32_t counter = delayNs * clockMHz / (6 * 1000U); // TODO: CHECK 6 INSTRUCTIONS ON REAL HW
        for (; counter > 0; counter--)
            asm volatile("");
    }
} // namespace stm32util::time
