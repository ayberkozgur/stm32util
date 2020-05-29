/**
 * @file GPIOUtilTest.cpp
 * @author Ayberk Özgür
 * @brief GPIO utilities unit tests
 */

#include <stm32util/gpio/GPIOUtil.hpp>

#include <gtest/gtest.h>

namespace stm32util::gpio::test {

    static GPIOPortRegister bsrr;
    static GPIOPortRegister idr;

    static constexpr GPIOPortAndPin TEST_PIN0{&bsrr, &idr, PIN0};
    static constexpr GPIOPortAndPin TEST_PIN1{&bsrr, &idr, PIN1};
    static constexpr GPIOPortAndPin TEST_PIN2{&bsrr, &idr, PIN2};
    static constexpr GPIOPortAndPin TEST_PIN3{&bsrr, &idr, PIN3};
    static constexpr GPIOPortAndPin TEST_PIN4{&bsrr, &idr, PIN4};
    static constexpr GPIOPortAndPin TEST_PIN5{&bsrr, &idr, PIN5};
    static constexpr GPIOPortAndPin TEST_PIN6{&bsrr, &idr, PIN6};
    static constexpr GPIOPortAndPin TEST_PIN7{&bsrr, &idr, PIN7};
    static constexpr GPIOPortAndPin TEST_PIN8{&bsrr, &idr, PIN8};
    static constexpr GPIOPortAndPin TEST_PIN9{&bsrr, &idr, PIN9};
    static constexpr GPIOPortAndPin TEST_PIN10{&bsrr, &idr, PIN10};
    static constexpr GPIOPortAndPin TEST_PIN11{&bsrr, &idr, PIN11};
    static constexpr GPIOPortAndPin TEST_PIN12{&bsrr, &idr, PIN12};
    static constexpr GPIOPortAndPin TEST_PIN13{&bsrr, &idr, PIN13};
    static constexpr GPIOPortAndPin TEST_PIN14{&bsrr, &idr, PIN14};
    static constexpr GPIOPortAndPin TEST_PIN15{&bsrr, &idr, PIN15};

    class GPIOUtilTest : public ::testing::Test {
    protected:
        GPIOUtilTest()           = default;
        ~GPIOUtilTest() override = default;
        void SetUp() override {
            bsrr = 0x00000000U;
            idr  = 0x00000000U;
        }
        void TearDown() override {}
    };

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_AllLow) {
        setMultipleGPIOSinglePort<PIN0_L, PIN1_L, PIN2_L, PIN3_L, PIN4_L, PIN5_L, PIN6_L, PIN7_L, PIN8_L, PIN9_L,
                                  PIN10_L, PIN11_L, PIN12_L, PIN13_L, PIN14_L, PIN15_L>(bsrr);
        EXPECT_EQ(bsrr, 0b1111'1111'1111'1111'0000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_AllHigh) {
        setMultipleGPIOSinglePort<PIN0_H, PIN1_H, PIN2_H, PIN3_H, PIN4_H, PIN5_H, PIN6_H, PIN7_H, PIN8_H, PIN9_H,
                                  PIN10_H, PIN11_H, PIN12_H, PIN13_H, PIN14_H, PIN15_H>(bsrr);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'1111'1111'1111'1111U);
    }

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_Interlaced) {
        setMultipleGPIOSinglePort<PIN1_H, PIN3_H, PIN5_H, PIN7_H, PIN9_H, PIN11_H, PIN13_H, PIN15_H, PIN0_L, PIN2_L,
                                  PIN4_L, PIN6_L, PIN8_L, PIN10_L, PIN12_L, PIN14_L>(bsrr);
        EXPECT_EQ(bsrr, 0b0101'0101'0101'0101'1010'1010'1010'1010U);
    }

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_Random) {
        setMultipleGPIOSinglePort<PIN1_H, PIN2_H, PIN3_H, PIN5_H, PIN8_H, PIN13_H, PIN0_L, PIN4_L, PIN6_L, PIN12_L,
                                  PIN14_L>(bsrr);
        EXPECT_EQ(bsrr, 0b0101'0000'0101'0001'0010'0001'0010'1110U);
    }

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_Edges1) {
        setMultipleGPIOSinglePort<PIN0_H, PIN15_L>(bsrr);
        EXPECT_EQ(bsrr, 0b1000'0000'0000'0000'0000'0000'0000'0001U);
    }

    TEST_F(GPIOUtilTest, SetMultiplePinsSinglePort_Edges2) {
        setMultipleGPIOSinglePort<PIN0_L, PIN15_H>(bsrr);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0001'1000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, SetSinglePinDynamic_EachHigh) {
        SetUp();
        setSingleGPIO<TEST_PIN0>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0001U);

        SetUp();
        setSingleGPIO<TEST_PIN1>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0010U);

        SetUp();
        setSingleGPIO<TEST_PIN2>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0100U);

        SetUp();
        setSingleGPIO<TEST_PIN3>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'1000U);

        SetUp();
        setSingleGPIO<TEST_PIN4>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0001'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN5>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0010'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN6>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0100'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN7>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'1000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN8>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0001'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN9>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0010'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN10>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0100'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN11>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'1000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN12>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0001'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN13>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0010'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN14>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0100'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN15>(true);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'1000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, SetSinglePinDynamic_EachLow) {
        SetUp();
        setSingleGPIO<TEST_PIN0>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0001'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN1>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0010'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN2>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0100'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN3>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0000'1000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN4>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0001'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN5>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0010'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN6>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'0100'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN7>(false);
        EXPECT_EQ(bsrr, 0b0000'0000'1000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN8>(false);
        EXPECT_EQ(bsrr, 0b0000'0001'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN9>(false);
        EXPECT_EQ(bsrr, 0b0000'0010'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN10>(false);
        EXPECT_EQ(bsrr, 0b0000'0100'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN11>(false);
        EXPECT_EQ(bsrr, 0b0000'1000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN12>(false);
        EXPECT_EQ(bsrr, 0b0001'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN13>(false);
        EXPECT_EQ(bsrr, 0b0010'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN14>(false);
        EXPECT_EQ(bsrr, 0b0100'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN15>(false);
        EXPECT_EQ(bsrr, 0b1000'0000'0000'0000'0000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, SetSinglePinStatic_EachHigh) {
        SetUp();
        setSingleGPIO<TEST_PIN0, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0001U);

        SetUp();
        setSingleGPIO<TEST_PIN1, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0010U);

        SetUp();
        setSingleGPIO<TEST_PIN2, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'0100U);

        SetUp();
        setSingleGPIO<TEST_PIN3, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0000'1000U);

        SetUp();
        setSingleGPIO<TEST_PIN4, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0001'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN5, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0010'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN6, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'0100'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN7, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0000'1000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN8, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0001'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN9, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0010'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN10, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'0100'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN11, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0000'1000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN12, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0001'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN13, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0010'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN14, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'0100'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN15, true>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0000'1000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, SetSinglePinStatic_EachLow) {
        SetUp();
        setSingleGPIO<TEST_PIN0, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0001'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN1, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0010'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN2, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'0100'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN3, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0000'1000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN4, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0001'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN5, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0010'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN6, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'0100'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN7, false>();
        EXPECT_EQ(bsrr, 0b0000'0000'1000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN8, false>();
        EXPECT_EQ(bsrr, 0b0000'0001'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN9, false>();
        EXPECT_EQ(bsrr, 0b0000'0010'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN10, false>();
        EXPECT_EQ(bsrr, 0b0000'0100'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN11, false>();
        EXPECT_EQ(bsrr, 0b0000'1000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN12, false>();
        EXPECT_EQ(bsrr, 0b0001'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN13, false>();
        EXPECT_EQ(bsrr, 0b0010'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN14, false>();
        EXPECT_EQ(bsrr, 0b0100'0000'0000'0000'0000'0000'0000'0000U);

        SetUp();
        setSingleGPIO<TEST_PIN15, false>();
        EXPECT_EQ(bsrr, 0b1000'0000'0000'0000'0000'0000'0000'0000U);
    }

    TEST_F(GPIOUtilTest, ReadPin_AllLow) {
        idr = 0x00000000U;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), false);
    }

    TEST_F(GPIOUtilTest, ReadPin_AllHigh) {
        idr = 0x0000FFFFU;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), true);
    }

    TEST_F(GPIOUtilTest, ReadPin_Interlaced) {
        idr = 0b0000'0000'0000'0000'1010'1010'1010'1010U;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), true);
    }

    TEST_F(GPIOUtilTest, ReadPin_Random) {
        idr = 0b0000'0000'0000'0000'0010'0001'0010'1110U;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), false);
    }

    TEST_F(GPIOUtilTest, ReadPin_Edges1) {
        idr = 0b0000'0000'0000'0000'1000'0000'0000'0001U;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), true);
    }

    TEST_F(GPIOUtilTest, ReadPin_Edges2) {
        idr = 0b0000'0000'0000'0000'0111'1111'1111'1110U;
        EXPECT_EQ(readSingleGPIO<TEST_PIN0>(), false);
        EXPECT_EQ(readSingleGPIO<TEST_PIN1>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN2>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN3>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN4>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN5>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN6>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN7>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN8>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN9>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN10>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN11>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN12>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN13>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN14>(), true);
        EXPECT_EQ(readSingleGPIO<TEST_PIN15>(), false);
    }

} // namespace stm32util::gpio::test
