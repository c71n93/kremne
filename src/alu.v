module alu(input [31:0] lhs, rhs, input [3:0] funct, output reg [31:0] out);
    always @(*) begin
        case(funct[3:0])
            4'b0_000: out = lhs & rhs; // AND
            4'b0_001: out = lhs | rhs; // OR
            4'b0_010: out = lhs ^ rhs; // XOR
            4'b0_011: out = lhs + rhs; // ADD
            4'b1_011: out = lhs - rhs;  // SUB
            4'b0_100: out = lhs >> rhs[4:0]; // SRL
            4'b1_100: out = $signed(lhs) >>> rhs[4:0]; // SRA
            4'b0_101: out = lhs << rhs[4:0]; // SLL
            4'b0_110: out = (lhs < rhs) ? 1 : 0; // SLTU
            4'b1_110: out = ($signed(lhs) < $signed(rhs)) ? 1 : 0; // SLT
            default: out = 0;
        endcase
    end
endmodule
