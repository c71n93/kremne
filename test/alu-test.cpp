#include "gtest/gtest.h"
#include <random>
#include "Valu.h"

class AluTest : public ::testing::Test {
protected:
    void TearDown() override { model->final(); }
    template<typename T> T random(T range_from, T range_to) {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<T> distr(range_from, range_to);
        return distr(generator);
    }

    std::shared_ptr<VerilatedContext> contextp = std::make_unique<VerilatedContext>();
    std::shared_ptr<Valu> model = std::make_unique<Valu>(contextp.get());
    uint32_t lhs = random<uint32_t>(0, std::numeric_limits<uint32_t>::max());
    uint32_t rhs = random<uint32_t>(0, std::numeric_limits<uint32_t>::max());
    int32_t neg_lhs = random<int32_t>(std::numeric_limits<int32_t>::min(), 0);
    int32_t neg_rhs = random<int32_t>(std::numeric_limits<int32_t>::min(), 0);
    uint32_t shift_rhs = random<uint32_t>(0, 31);
};

TEST_F(AluTest, AndTest) {
    model->funct = 0b0000;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs & rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, OrTest) {
    model->funct = 0b0001;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs | rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, XorTest) {
    model->funct = 0b0010;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs ^ rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, AddTest) {
    model->funct = 0b0011;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs + rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, SubTest) {
    model->funct = 0b1011;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs - rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, SrlTest) {
    model->funct = 0b0100;
    model->lhs = lhs;
    model->rhs = shift_rhs;
    model->eval();
    EXPECT_EQ(lhs >> shift_rhs, model->out) << "lhs = " << lhs << " rhs = " << shift_rhs << std::endl;
}

TEST_F(AluTest, SraTest) {
    model->funct = 0b1100;
    model->lhs = neg_lhs;
    model->rhs = shift_rhs;
    model->eval();
    EXPECT_EQ(neg_lhs >> shift_rhs, model->out) << "lhs = " << neg_lhs << " rhs = " << shift_rhs << std::endl;
}

TEST_F(AluTest, SllTest) {
    model->funct = 0b0101;
    model->lhs = lhs;
    model->rhs = shift_rhs;
    model->eval();
    EXPECT_EQ(lhs << shift_rhs, model->out) << "lhs = " << lhs << " rhs = " << shift_rhs << std::endl;
}

TEST_F(AluTest, SltuTest) {
    model->funct = 0b0110;
    model->lhs = lhs;
    model->rhs = rhs;
    model->eval();
    EXPECT_EQ(lhs < rhs, model->out) << "lhs = " << lhs << " rhs = " << rhs << std::endl;
}

TEST_F(AluTest, SltTest) {
    model->funct = 0b0110;
    model->lhs = neg_lhs;
    model->rhs = neg_rhs;
    model->eval();
    EXPECT_EQ(neg_lhs < neg_rhs, model->out) << "lhs = " << neg_lhs << " rhs = " << neg_rhs << std::endl;
}
