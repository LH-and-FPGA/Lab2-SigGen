#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // TODO: Check the doc about this

    Vsinegen* sinegen = new Vsinegen;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    sinegen->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    // init vbuddy
    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab 2: Sinegen");
    vbdSetMode(1);

    sinegen->clk = 1;
    sinegen->en = 1;
    sinegen->rst = 0;
    sinegen->incr = 1;

    int half_cyc_counter = 0;


    while(true) {
        if (vbdFlag() == 1) {
            sinegen->rst = 1;
            if (vbdValue() > 10) {
                sinegen->incr = 10;
            } else {
                sinegen->incr = vbdValue();
            }
        } else {
            sinegen->rst = 0;
        }

        vbdPlot(sinegen->dout, -240, 360);

        for (clk = 0; clk < 2; clk++) {
            // tfp->dump(2*i+clk);
            sinegen->clk = !sinegen->clk;
            sinegen->eval();
        }

        if (vbdGetkey() == 'q') {
            vbdClose();
            tfp->close();
            exit(0);
        }
        // i++;
    }

    vbdClose();
    tfp->close();
    exit(0);
}
