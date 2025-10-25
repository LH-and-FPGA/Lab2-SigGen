module rom #(
    parameter ADDRESS_WIDTH = 8,
              DATA_WIDTH    = 8
) (
    input logic clk,
    input logic [ADDRESS_WIDTH-1:0] addr1,
    input logic [ADDRESS_WIDTH-1:0] addr2,
    input logic [DATA_WIDTH-1:0] din,
    output logic [DATA_WIDTH-1:0] dout
);
    // 如何防止读时写或者写时读的冲突？
    logic [DATA_WIDTH-1:0] rom_array [2**ADDRESS_WIDTH-1:0];
    // Make it larger than 512*8, just have a try

    always_ff @(posedge clk) begin
        rom_array[addr1] <= din;
        dout <= rom_array[addr2];
    end

endmodule
