/*
	Title: MIPS Single-Cycle Control Unit
	Editor: Selene (Computer System and Architecture Lab, ICE, CYCU)
	
	Input Port
		1. opcode: 輸入的指令代號，據此產生對應的控制訊號
	Input Port
		1. RegDst: 控制RFMUX
		2. ALUSrc: 控制ALUMUX
		3. MemtoReg: 控制WRMUX
		4. RegWrite: 控制暫存器是否可寫入
		5. MemRead:  控制記憶體是否可讀出
		6. MemWrite: 控制記憶體是否可寫入
		7. Branch: 與ALU輸出的zero訊號做AND運算控制PCMUX
		8. ALUOp: 輸出至ALU Control
*/
module control_single( opcode, RegDst, ALUSrc, MemtoReg, RegWrite, 
					   MemRead, MemWrite, Ori, Beq, Bne, Jump, ALUOp);
    input[5:0] opcode;
    output RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Ori, Beq, Bne, Jump;
    output[1:0] ALUOp;
    reg RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Ori, Beq, Bne, Jump = 0;
    reg[1:0] ALUOp = 0;

    	parameter R_FORMAT = 6'd0;
	parameter ORI = 6'd13;	 //十六進位d轉13
    	parameter LW = 6'd35;    //十六進位23轉35
    	parameter SW = 6'd43;   
    	parameter BEQ = 6'd4;
	parameter BNE = 6'd5;				  
	parameter J = 6'd2;

    always @( opcode ) begin
        case ( opcode )
          R_FORMAT : 
          begin
				RegDst = 1'b1; ALUSrc = 1'b0; MemtoReg = 1'b0; RegWrite = 1'b1; MemRead = 1'b0; 
				MemWrite = 1'b0; Ori = 1'b0; Beq = 1'b0; Bne = 1'b0; Jump = 1'b0; ALUOp = 2'b10; 
	  end
	  ORI : 
          begin
				RegDst = 1'b0; ALUSrc = 1'b1; MemtoReg = 1'b0; RegWrite = 1'b1; MemRead = 1'b0; 
				MemWrite = 1'b0; Ori = 1'b1; Beq = 1'b0; Bne = 1'b0; Jump = 1'b0; ALUOp = 2'b00; 						   																																	 
          end
          LW :
          begin
				RegDst = 1'b0; ALUSrc = 1'b1; MemtoReg = 1'b1; RegWrite = 1'b1; MemRead = 1'b1; 
				MemWrite = 1'b0; Ori = 1'b0; Beq = 1'b0; Bne = 1'b0; Jump = 1'b0; ALUOp = 2'b00; 
          end
          SW :
          begin
				RegDst = 1'bx; ALUSrc = 1'b1; MemtoReg = 1'bx; RegWrite = 1'b0; MemRead = 1'b0; 
				MemWrite = 1'b1; Ori = 1'b0; Beq = 1'b0; Bne = 1'b0; Jump = 1'b0; ALUOp = 2'b00; 
          end
          BEQ :
          begin
				RegDst = 1'bx; ALUSrc = 1'b0; MemtoReg = 1'bx; RegWrite = 1'b0; MemRead = 1'b0; 
				MemWrite = 1'b0; Ori = 1'b0; Beq = 1'b1; Bne = 1'b0; Jump = 1'b0; ALUOp = 2'b01; 
          end
	  BNE :
          begin
				RegDst = 1'bx; ALUSrc = 1'b0; MemtoReg = 1'bx; RegWrite = 1'b0; MemRead = 1'b0; 
				MemWrite = 1'b0; Ori = 1'b0; Beq = 1'b0; Bne = 1'b1; Jump = 1'b0; ALUOp = 2'b01; 
          end		 																																									 	   
	  J :
	  begin
				RegDst = 1'bx; ALUSrc = 1'b0; MemtoReg = 1'bx; RegWrite = 1'b0; MemRead = 1'b0; 
				MemWrite = 1'b0; Ori = 1'b0; Beq = 1'b0; Bne = 1'b0; Jump = 1'b1; ALUOp = 2'b01; 
	  end
          default
          begin
				$display("control_single unimplemented opcode %d", opcode);
				RegDst = 1'bx; ALUSrc = 1'bx; MemtoReg = 1'bx; RegWrite = 1'bx; MemRead = 1'bx; 
				MemWrite = 1'bx; Ori = 1'bx; Beq = 1'bx; Bne = 1'bx; Jump = 1'bx; ALUOp = 2'bxx; 
          end

        endcase
    end
endmodule

