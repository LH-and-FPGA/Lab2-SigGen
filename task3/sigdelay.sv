module sinegen #(
    parameter COUNT_WIDTH = 8,
               DATA_WIDTH  = 8
) (
    input logic [COUNT_WIDTH-1:0] incr,
    input logic rst,
    input logic en,
    input logic clk,
    input logic [DATA_WIDTH-1:0] din,
    output logic [DATA_WIDTH-1:0] dout
);

    logic [COUNT_WIDTH-1:0] addr;

    counter Counter(
        .rst(rst),
        .en(en),
        .incr({COUNT_WIDTH-1{1'b0},1'b1}),
        .clk(clk),
        .count(addr)
    );

    rom Rom(
        .clk(clk),
        .addr1(addr),
        .addr2(addr + incr),
        .din(din),
        .dout(dout)
    );

endmodule
