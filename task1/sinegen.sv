module sinegen #(
    parameter COUNT_WIDTH = 8,
               DATA_WIDTH  = 8
) (
    input logic [COUNT_WIDTH-1:0] incr,
    input logic rst,
    input logic en,
    input logic clk,
    output logic [DATA_WIDTH-1:0] dout
);

    logic [COUNT_WIDTH-1:0] addr;

    counter Counter(
        .rst(rst),
        .en(en),
        .incr(incr),
        .clk(clk),
        .count(addr)
    );

    rom Rom(
        .clk(clk),
        .addr(addr),
        .dout(dout)
    );

endmodule
