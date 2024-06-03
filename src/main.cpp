#include <iostream>
#include "Valu.h"

int main(int argc, char **argv) {
    Verilated::debug(0);
    auto contextp = std::make_unique<VerilatedContext>();
    contextp->commandArgs(argc, argv);
    auto model = std::make_unique<Valu>(contextp.get());
    while (!contextp->gotFinish()) {
        model->funct = 0b0000;
        model->lhs = 1;
        model->rhs = 2;
        model->eval();
        contextp->timeInc(1);
        std::cout << model->out << std::endl;
        break;
    }
    model->final();
    contextp->statsPrintSummary();
    return 0;
}
