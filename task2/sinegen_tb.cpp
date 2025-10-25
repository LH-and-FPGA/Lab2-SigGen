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
    vbdSetMode(0);

    sinegen->clk = 1;
    sinegen->en = 1;
    sinegen->rst = 0;
    sinegen->incr = 1;
    sinegen->cnt_incr = 5;

    int cyc_counter = 0;

    while(true) {
        vbdCycle(cyc_counter++);
        if (vbdFlag() == 0) {
            sinegen->incr = vbdValue();
        } else {
            if (vbdValue() > 20) {
                sinegen->cnt_incr = 20;
            } else {
                sinegen->cnt_incr = vbdValue();
            }
        }
        // sinegen->incr = vbdValue();

        vbdPlot(sinegen->dout1, -240, 360);
        vbdPlot(sinegen->dout2, -240, 360);

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
