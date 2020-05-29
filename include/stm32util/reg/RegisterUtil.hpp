#pragma once

#include <cstdint>
#include <type_traits>

namespace stm32util::reg {
    struct BitPositionAndState {
        uint8_t position;
        bool state;
    };

    static constexpr BitPositionAndState POS0_L{0, false};
    static constexpr BitPositionAndState POS1_L{1, false};
    static constexpr BitPositionAndState POS2_L{2, false};
    static constexpr BitPositionAndState POS3_L{3, false};
    static constexpr BitPositionAndState POS4_L{4, false};
    static constexpr BitPositionAndState POS5_L{5, false};
    static constexpr BitPositionAndState POS6_L{6, false};
    static constexpr BitPositionAndState POS7_L{7, false};
    static constexpr BitPositionAndState POS8_L{8, false};
    static constexpr BitPositionAndState POS9_L{9, false};
    static constexpr BitPositionAndState POS10_L{10, false};
    static constexpr BitPositionAndState POS11_L{11, false};
    static constexpr BitPositionAndState POS12_L{12, false};
    static constexpr BitPositionAndState POS13_L{13, false};
    static constexpr BitPositionAndState POS14_L{14, false};
    static constexpr BitPositionAndState POS15_L{15, false};
    static constexpr BitPositionAndState POS16_L{16, false};
    static constexpr BitPositionAndState POS17_L{17, false};
    static constexpr BitPositionAndState POS18_L{18, false};
    static constexpr BitPositionAndState POS19_L{19, false};
    static constexpr BitPositionAndState POS20_L{20, false};
    static constexpr BitPositionAndState POS21_L{21, false};
    static constexpr BitPositionAndState POS22_L{22, false};
    static constexpr BitPositionAndState POS23_L{23, false};
    static constexpr BitPositionAndState POS24_L{24, false};
    static constexpr BitPositionAndState POS25_L{25, false};
    static constexpr BitPositionAndState POS26_L{26, false};
    static constexpr BitPositionAndState POS27_L{27, false};
    static constexpr BitPositionAndState POS28_L{28, false};
    static constexpr BitPositionAndState POS29_L{29, false};
    static constexpr BitPositionAndState POS30_L{30, false};
    static constexpr BitPositionAndState POS31_L{31, false};

    static constexpr BitPositionAndState POS0_H{0, true};
    static constexpr BitPositionAndState POS1_H{1, true};
    static constexpr BitPositionAndState POS2_H{2, true};
    static constexpr BitPositionAndState POS3_H{3, true};
    static constexpr BitPositionAndState POS4_H{4, true};
    static constexpr BitPositionAndState POS5_H{5, true};
    static constexpr BitPositionAndState POS6_H{6, true};
    static constexpr BitPositionAndState POS7_H{7, true};
    static constexpr BitPositionAndState POS8_H{8, true};
    static constexpr BitPositionAndState POS9_H{9, true};
    static constexpr BitPositionAndState POS10_H{10, true};
    static constexpr BitPositionAndState POS11_H{11, true};
    static constexpr BitPositionAndState POS12_H{12, true};
    static constexpr BitPositionAndState POS13_H{13, true};
    static constexpr BitPositionAndState POS14_H{14, true};
    static constexpr BitPositionAndState POS15_H{15, true};
    static constexpr BitPositionAndState POS16_H{16, true};
    static constexpr BitPositionAndState POS17_H{17, true};
    static constexpr BitPositionAndState POS18_H{18, true};
    static constexpr BitPositionAndState POS19_H{19, true};
    static constexpr BitPositionAndState POS20_H{20, true};
    static constexpr BitPositionAndState POS21_H{21, true};
    static constexpr BitPositionAndState POS22_H{22, true};
    static constexpr BitPositionAndState POS23_H{23, true};
    static constexpr BitPositionAndState POS24_H{24, true};
    static constexpr BitPositionAndState POS25_H{25, true};
    static constexpr BitPositionAndState POS26_H{26, true};
    static constexpr BitPositionAndState POS27_H{27, true};
    static constexpr BitPositionAndState POS28_H{28, true};
    static constexpr BitPositionAndState POS29_H{29, true};
    static constexpr BitPositionAndState POS30_H{30, true};
    static constexpr BitPositionAndState POS31_H{31, true};

    namespace detail {

        //Much nicer solution exists with c++17 with for loops allowed in constexpr

        template <uint8_t Position, bool State>
        constexpr typename std::enable_if<State, uint32_t>::type mask() {
            return static_cast<uint32_t>(0b1U) << Position;
        }

        template <uint8_t Position, bool State>
        constexpr typename std::enable_if<!State, uint32_t>::type mask() {
            return 0U;
        }

        template <BitPositionAndState const& LastBitPositionAndState>
        constexpr uint32_t clearMaskNot() {
            return mask<LastBitPositionAndState.position, !LastBitPositionAndState.state>();
        }

        template <BitPositionAndState const& CurrentBitPositionAndState,
                  BitPositionAndState const& NextBitPositionAndState,
                  BitPositionAndState const&... RemainingBitPositionsAndStates>
        constexpr uint32_t clearMaskNot() {
            return mask<CurrentBitPositionAndState.position, !CurrentBitPositionAndState.state>() |
                   clearMaskNot<NextBitPositionAndState, RemainingBitPositionsAndStates...>();
        }

        template <BitPositionAndState const& LastBitPositionAndState>
        constexpr uint32_t setMask() {
            return mask<LastBitPositionAndState.position, LastBitPositionAndState.state>();
        }

        template <BitPositionAndState const& CurrentBitPositionAndState,
                  BitPositionAndState const& NextBitPositionAndState,
                  BitPositionAndState const&... RemainingBitPositionsAndStates>
        constexpr uint32_t setMask() {
            return mask<CurrentBitPositionAndState.position, CurrentBitPositionAndState.state>() |
                   setMask<NextBitPositionAndState, RemainingBitPositionsAndStates...>();
        }

    } // namespace detail

    template <BitPositionAndState const&... BitPositionsAndStates>
    inline void setBits(volatile uint32_t* reg) {
        *reg = (*reg | detail::setMask<BitPositionsAndStates...>()) & ~detail::clearMaskNot<BitPositionsAndStates...>();
    }

    template <uint8_t BitPosition>
    inline bool getBit(uint32_t reg) {
        return static_cast<bool>(reg & detail::mask<BitPosition, true>());
    }

    template <uint8_t BytePosition>
    inline void setByte(volatile uint32_t* reg, uint8_t byte) {
        static_assert(BytePosition <= 3);

        constexpr uint8_t bitPosition = (BytePosition * 8);
        constexpr uint32_t mask       = static_cast<uint32_t>(0xFFU) << bitPosition;
        constexpr uint32_t clearMask  = ~mask;

        *reg = (*reg & clearMask) | (static_cast<uint32_t>(byte) << bitPosition);
    }

    template <uint8_t BytePosition>
    inline uint8_t getByte(uint32_t reg) {
        static_assert(BytePosition <= 3);

        constexpr uint8_t bitPosition = (BytePosition * 8);
        constexpr uint32_t mask       = static_cast<uint32_t>(0xFFU) << bitPosition;

        return static_cast<uint8_t>((reg & mask) >> bitPosition);
    }

} // namespace stm32util::reg
