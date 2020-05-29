/**
 * @file GPIOUtil.hpp
 * @author Ayberk Özgür
 * @brief STM32 GPIO utilities to set/reset pins easy and fast
 */

#pragma once

#include <cstdint>
#include <type_traits>

namespace stm32util::gpio {

    using GPIOPin          = uint16_t;
    using GPIOPortRegister = uint32_t;

    struct GPIOPinAndState {
        GPIOPin pin;
        bool state;
    };

    struct GPIOPortAndPin {
        volatile GPIOPortRegister* bsrr;
        volatile GPIOPortRegister* idr;
        GPIOPin pin;
    };

    static constexpr GPIOPin PIN0  = 0b0000'0000'0000'0001U;
    static constexpr GPIOPin PIN1  = 0b0000'0000'0000'0010U;
    static constexpr GPIOPin PIN2  = 0b0000'0000'0000'0100U;
    static constexpr GPIOPin PIN3  = 0b0000'0000'0000'1000U;
    static constexpr GPIOPin PIN4  = 0b0000'0000'0001'0000U;
    static constexpr GPIOPin PIN5  = 0b0000'0000'0010'0000U;
    static constexpr GPIOPin PIN6  = 0b0000'0000'0100'0000U;
    static constexpr GPIOPin PIN7  = 0b0000'0000'1000'0000U;
    static constexpr GPIOPin PIN8  = 0b0000'0001'0000'0000U;
    static constexpr GPIOPin PIN9  = 0b0000'0010'0000'0000U;
    static constexpr GPIOPin PIN10 = 0b0000'0100'0000'0000U;
    static constexpr GPIOPin PIN11 = 0b0000'1000'0000'0000U;
    static constexpr GPIOPin PIN12 = 0b0001'0000'0000'0000U;
    static constexpr GPIOPin PIN13 = 0b0010'0000'0000'0000U;
    static constexpr GPIOPin PIN14 = 0b0100'0000'0000'0000U;
    static constexpr GPIOPin PIN15 = 0b1000'0000'0000'0000U;

    static constexpr GPIOPinAndState PIN0_L{PIN0, false};
    static constexpr GPIOPinAndState PIN1_L{PIN1, false};
    static constexpr GPIOPinAndState PIN2_L{PIN2, false};
    static constexpr GPIOPinAndState PIN3_L{PIN3, false};
    static constexpr GPIOPinAndState PIN4_L{PIN4, false};
    static constexpr GPIOPinAndState PIN5_L{PIN5, false};
    static constexpr GPIOPinAndState PIN6_L{PIN6, false};
    static constexpr GPIOPinAndState PIN7_L{PIN7, false};
    static constexpr GPIOPinAndState PIN8_L{PIN8, false};
    static constexpr GPIOPinAndState PIN9_L{PIN9, false};
    static constexpr GPIOPinAndState PIN10_L{PIN10, false};
    static constexpr GPIOPinAndState PIN11_L{PIN11, false};
    static constexpr GPIOPinAndState PIN12_L{PIN12, false};
    static constexpr GPIOPinAndState PIN13_L{PIN13, false};
    static constexpr GPIOPinAndState PIN14_L{PIN14, false};
    static constexpr GPIOPinAndState PIN15_L{PIN15, false};

    static constexpr GPIOPinAndState PIN0_H{PIN0, true};
    static constexpr GPIOPinAndState PIN1_H{PIN1, true};
    static constexpr GPIOPinAndState PIN2_H{PIN2, true};
    static constexpr GPIOPinAndState PIN3_H{PIN3, true};
    static constexpr GPIOPinAndState PIN4_H{PIN4, true};
    static constexpr GPIOPinAndState PIN5_H{PIN5, true};
    static constexpr GPIOPinAndState PIN6_H{PIN6, true};
    static constexpr GPIOPinAndState PIN7_H{PIN7, true};
    static constexpr GPIOPinAndState PIN8_H{PIN8, true};
    static constexpr GPIOPinAndState PIN9_H{PIN9, true};
    static constexpr GPIOPinAndState PIN10_H{PIN10, true};
    static constexpr GPIOPinAndState PIN11_H{PIN11, true};
    static constexpr GPIOPinAndState PIN12_H{PIN12, true};
    static constexpr GPIOPinAndState PIN13_H{PIN13, true};
    static constexpr GPIOPinAndState PIN14_H{PIN14, true};
    static constexpr GPIOPinAndState PIN15_H{PIN15, true};

    namespace detail {

        // Much nicer solution exists with c++17 with for loops allowed in constexpr

        template <stm32util::gpio::GPIOPin Pin, bool State>
        constexpr typename std::enable_if<State, uint32_t>::type gpioBSRRMask() {
            return static_cast<uint32_t>(Pin);
        }

        template <stm32util::gpio::GPIOPin Pin, bool State>
        constexpr typename std::enable_if<!State, uint32_t>::type gpioBSRRMask() {
            return static_cast<uint32_t>(Pin) << 16;
        }

        template <stm32util::gpio::GPIOPinAndState const& LastPinAndState>
        constexpr uint32_t gpioBSRRMask() {
            return gpioBSRRMask<LastPinAndState.pin, LastPinAndState.state>();
        }

        template <stm32util::gpio::GPIOPinAndState const& CurrentPinAndState,
                  stm32util::gpio::GPIOPinAndState const& NextPinAndState,
                  stm32util::gpio::GPIOPinAndState const&... RemainingPinsAndStates>
        constexpr uint32_t gpioBSRRMask() {
            return gpioBSRRMask<CurrentPinAndState.pin, CurrentPinAndState.state>() |
                   gpioBSRRMask<NextPinAndState, RemainingPinsAndStates...>();
        }

    } // namespace detail

    template <GPIOPinAndState const&... PinsAndStates>
    inline void setMultipleGPIOSinglePort(volatile GPIOPortRegister& bsrr) {
        bsrr = detail::gpioBSRRMask<PinsAndStates...>();
    }

    template <GPIOPortAndPin const& PortAndPin>
    inline void setSingleGPIO(bool state) {
        if (state)
            *(PortAndPin.bsrr) = detail::gpioBSRRMask<PortAndPin.pin, true>();
        else
            *(PortAndPin.bsrr) = detail::gpioBSRRMask<PortAndPin.pin, false>();
    }

    template <GPIOPortAndPin const& PortAndPin, bool State>
    inline void setSingleGPIO() {
        *(PortAndPin.bsrr) = detail::gpioBSRRMask<PortAndPin.pin, State>();
    }

    template <GPIOPortAndPin const& PortAndPin>
    inline bool readSingleGPIO() {
        return static_cast<bool>(*(PortAndPin.idr) & PortAndPin.pin);
    }

} // namespace stm32util::gpio
