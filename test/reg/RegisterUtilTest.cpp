/**
 * @file RegisterUtilTest.cpp
 * @author Ayberk Özgür
 * @brief Register utilities unit tests
 */

#include <stm32util/reg/RegisterUtil.hpp>

#include <gtest/gtest.h>

namespace stm32util::reg::test {

    class RegisterUtilTest : public ::testing::Test {
    protected:
        RegisterUtilTest()           = default;
        ~RegisterUtilTest() override = default;
        void SetUp() override {
            reg = 0x00000000U;
        }
        void TearDown() override {}

        uint32_t reg;
    };

    TEST_F(RegisterUtilTest, SetBits_AllHigh) {
        reg = 0x00000000U;
        setBits<POS0_H, POS1_H, POS2_H, POS3_H, POS4_H, POS5_H, POS6_H, POS7_H, POS8_H, POS9_H, POS10_H, POS11_H,
                POS12_H, POS13_H, POS14_H, POS15_H, POS16_H, POS17_H, POS18_H, POS19_H, POS20_H, POS21_H, POS22_H,
                POS23_H, POS24_H, POS25_H, POS26_H, POS27_H, POS28_H, POS29_H, POS30_H, POS31_H>(&reg);
        EXPECT_EQ(reg, 0b1111'1111'1111'1111'1111'1111'1111'1111U);
    }

    TEST_F(RegisterUtilTest, SetBits_AllLow) {
        reg = 0xFFFFFFFFU;
        setBits<POS0_L, POS1_L, POS2_L, POS3_L, POS4_L, POS5_L, POS6_L, POS7_L, POS8_L, POS9_L, POS10_L, POS11_L,
                POS12_L, POS13_L, POS14_L, POS15_L, POS16_L, POS17_L, POS18_L, POS19_L, POS20_L, POS21_L, POS22_L,
                POS23_L, POS24_L, POS25_L, POS26_L, POS27_L, POS28_L, POS29_L, POS30_L, POS31_L>(&reg);
        EXPECT_EQ(reg, 0b0000'0000'0000'0000'0000'0000'0000'0000U);
    }

    TEST_F(RegisterUtilTest, SetBits_Interlaced1) {
        reg = 0x00000000U;
        setBits<POS0_H, POS2_H, POS4_H, POS6_H, POS8_H, POS10_H, POS12_H, POS14_H, POS16_H, POS18_H, POS20_H, POS22_H,
                POS24_H, POS26_H, POS28_H, POS30_H>(&reg);
        EXPECT_EQ(reg, 0b0101'0101'0101'0101'0101'0101'0101'0101U);
    }

    TEST_F(RegisterUtilTest, SetBits_Interlaced2) {
        reg = 0xFFFFFFFFU;
        setBits<POS0_L, POS2_L, POS4_L, POS6_L, POS8_L, POS10_L, POS12_L, POS14_L, POS16_L, POS18_L, POS20_L, POS22_L,
                POS24_L, POS26_L, POS28_L, POS30_L>(&reg);
        EXPECT_EQ(reg, 0b1010'1010'1010'1010'1010'1010'1010'1010U);
    }

    TEST_F(RegisterUtilTest, SetBits_Interlaced3) {
        reg = 0x00000000U;
        setBits<POS1_H, POS3_H, POS5_H, POS7_H, POS9_H, POS11_H, POS13_H, POS15_H, POS17_H, POS19_H, POS21_H, POS23_H,
                POS25_H, POS27_H, POS29_H, POS31_H>(&reg);
        EXPECT_EQ(reg, 0b1010'1010'1010'1010'1010'1010'1010'1010U);
    }

    TEST_F(RegisterUtilTest, SetBits_Interlaced4) {
        reg = 0xFFFFFFFFU;
        setBits<POS1_L, POS3_L, POS5_L, POS7_L, POS9_L, POS11_L, POS13_L, POS15_L, POS17_L, POS19_L, POS21_L, POS23_L,
                POS25_L, POS27_L, POS29_L, POS31_L>(&reg);
        EXPECT_EQ(reg, 0b0101'0101'0101'0101'0101'0101'0101'0101U);
    }

    TEST_F(RegisterUtilTest, SetBits_Random1) {
        reg = 0b1010'1010'1010'1010'1010'1010'1010'1010U;
        setBits<POS2_H, POS3_L, POS5_H, POS6_L, POS8_H, POS10_L, POS11_H, POS13_L, POS14_H, POS16_L, POS18_H, POS19_L,
                POS21_H, POS22_L, POS26_H, POS28_L>(&reg);
        EXPECT_EQ(reg, 0b1010'1110'1010'0110'1100'1011'1010'0110U);
    }

    TEST_F(RegisterUtilTest, SetBits_Random2) {
        reg = 0b1010'1010'1010'1010'1010'1010'1010'1010U;
        setBits<POS0_H, POS2_L, POS6_H, POS7_L, POS9_H, POS12_L, POS13_H, POS15_L, POS17_H, POS19_L, POS22_H, POS24_L,
                POS25_H, POS26_L, POS30_H, POS31_L>(&reg);
        EXPECT_EQ(reg, 0b0110'1010'1110'0010'0010'1010'0110'1011U);
    }

    TEST_F(RegisterUtilTest, GetBits_Random1) {
        reg = 0b1111'0000'1011'0001'0100'1010'0001'0110U;
        EXPECT_EQ(getBit<0>(reg), false);
        EXPECT_EQ(getBit<1>(reg), true);
        EXPECT_EQ(getBit<2>(reg), true);
        EXPECT_EQ(getBit<3>(reg), false);
        EXPECT_EQ(getBit<4>(reg), true);
        EXPECT_EQ(getBit<5>(reg), false);
        EXPECT_EQ(getBit<6>(reg), false);
        EXPECT_EQ(getBit<7>(reg), false);
        EXPECT_EQ(getBit<8>(reg), false);
        EXPECT_EQ(getBit<9>(reg), true);
        EXPECT_EQ(getBit<10>(reg), false);
        EXPECT_EQ(getBit<11>(reg), true);
        EXPECT_EQ(getBit<12>(reg), false);
        EXPECT_EQ(getBit<13>(reg), false);
        EXPECT_EQ(getBit<14>(reg), true);
        EXPECT_EQ(getBit<15>(reg), false);
        EXPECT_EQ(getBit<16>(reg), true);
        EXPECT_EQ(getBit<17>(reg), false);
        EXPECT_EQ(getBit<18>(reg), false);
        EXPECT_EQ(getBit<19>(reg), false);
        EXPECT_EQ(getBit<20>(reg), true);
        EXPECT_EQ(getBit<21>(reg), true);
        EXPECT_EQ(getBit<22>(reg), false);
        EXPECT_EQ(getBit<23>(reg), true);
        EXPECT_EQ(getBit<24>(reg), false);
        EXPECT_EQ(getBit<25>(reg), false);
        EXPECT_EQ(getBit<26>(reg), false);
        EXPECT_EQ(getBit<27>(reg), false);
        EXPECT_EQ(getBit<28>(reg), true);
        EXPECT_EQ(getBit<29>(reg), true);
        EXPECT_EQ(getBit<30>(reg), true);
        EXPECT_EQ(getBit<31>(reg), true);
    }

    TEST_F(RegisterUtilTest, GetBits_Random2) {
        reg = 0b0000'1111'0100'1110'1011'0101'1110'1001U;
        EXPECT_EQ(getBit<0>(reg), true);
        EXPECT_EQ(getBit<1>(reg), false);
        EXPECT_EQ(getBit<2>(reg), false);
        EXPECT_EQ(getBit<3>(reg), true);
        EXPECT_EQ(getBit<4>(reg), false);
        EXPECT_EQ(getBit<5>(reg), true);
        EXPECT_EQ(getBit<6>(reg), true);
        EXPECT_EQ(getBit<7>(reg), true);
        EXPECT_EQ(getBit<8>(reg), true);
        EXPECT_EQ(getBit<9>(reg), false);
        EXPECT_EQ(getBit<10>(reg), true);
        EXPECT_EQ(getBit<11>(reg), false);
        EXPECT_EQ(getBit<12>(reg), true);
        EXPECT_EQ(getBit<13>(reg), true);
        EXPECT_EQ(getBit<14>(reg), false);
        EXPECT_EQ(getBit<15>(reg), true);
        EXPECT_EQ(getBit<16>(reg), false);
        EXPECT_EQ(getBit<17>(reg), true);
        EXPECT_EQ(getBit<18>(reg), true);
        EXPECT_EQ(getBit<19>(reg), true);
        EXPECT_EQ(getBit<20>(reg), false);
        EXPECT_EQ(getBit<21>(reg), false);
        EXPECT_EQ(getBit<22>(reg), true);
        EXPECT_EQ(getBit<23>(reg), false);
        EXPECT_EQ(getBit<24>(reg), true);
        EXPECT_EQ(getBit<25>(reg), true);
        EXPECT_EQ(getBit<26>(reg), true);
        EXPECT_EQ(getBit<27>(reg), true);
        EXPECT_EQ(getBit<28>(reg), false);
        EXPECT_EQ(getBit<29>(reg), false);
        EXPECT_EQ(getBit<30>(reg), false);
        EXPECT_EQ(getBit<31>(reg), false);
    }

    TEST_F(RegisterUtilTest, SetBytes_Random1) {
        reg = 0b1010'1010'1010'1010'1010'1010'1010'1010U;
        setByte<0>(&reg, 0b0111'0011U);
        setByte<1>(&reg, 0b0111'1110U);
        setByte<2>(&reg, 0b0100'0101U);
        setByte<3>(&reg, 0b1101'1101U);
        EXPECT_EQ(reg, 0b1101'1101'0100'0101'0111'1110'0111'0011U);
    }

    TEST_F(RegisterUtilTest, SetBytes_Random2) {
        reg = 0b1010'1010'1010'1010'1010'1010'1010'1010U;
        setByte<0>(&reg, 0b1111'0101U);
        setByte<1>(&reg, 0b0000'0100U);
        setByte<2>(&reg, 0b0011'1110U);
        setByte<3>(&reg, 0b0101'0010U);
        EXPECT_EQ(reg, 0b0101'0010'0011'1110'0000'0100'1111'0101U);
    }

    TEST_F(RegisterUtilTest, GetBytes_Random1) {
        reg = 0b1101'1101'0100'0101'0111'1110'0111'0011U;
        EXPECT_EQ(getByte<0>(reg), 0b0111'0011U);
        EXPECT_EQ(getByte<1>(reg), 0b0111'1110U);
        EXPECT_EQ(getByte<2>(reg), 0b0100'0101U);
        EXPECT_EQ(getByte<3>(reg), 0b1101'1101U);
    }

    TEST_F(RegisterUtilTest, GetBytes_Random2) {
        reg = 0b0101'0010'0011'1110'0000'0100'1111'0101U;
        EXPECT_EQ(getByte<0>(reg), 0b1111'0101U);
        EXPECT_EQ(getByte<1>(reg), 0b0000'0100U);
        EXPECT_EQ(getByte<2>(reg), 0b0011'1110U);
        EXPECT_EQ(getByte<3>(reg), 0b0101'0010U);
    }

} // namespace stm32util::reg::test
