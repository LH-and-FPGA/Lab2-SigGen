module sinegen #(
    parameter COUNT_WIDTH = 8,
               DATA_WIDTH  = 8
) (
    input logic [COUNT_WIDTH-1:0] incr,
    input logic rst,
    input logic en,
    input logic clk,
    output logic [DATA_WIDTH-1:0] dout1,
    output logic [DATA_WIDTH-1:0] dout2
);

    logic [COUNT_WIDTH-1:0] addr;

    counter Counter(
        .rst(rst),
        .en(en),
        .incr({{(COUNT_WIDTH-1){1'b0}}, 1'b1}),
        .clk(clk),
        .count(addr)
    );

    rom Rom(
        .clk(clk),
        .addr1(addr),
        .addr2(addr + incr),
        .dout1(dout1),
        .dout2(dout2)
    );

endmodule
