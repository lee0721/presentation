module vending_machine(clk, reset, howManyTicket, origin, destination,
 money, costOfTicket, moneyToPay, totalMoney);

input clk, reset;
input [2:0]howManyTicket, origin, destination;
reg [6:0]temp;
input [5:0]money;
output reg [6:0]costOfTicket, moneyToPay, totalMoney;
//狀態定義              
parameter s0 = 3'd0; 
parameter s1 = 3'd1; 
parameter s2 = 3'd2; 
parameter s3 = 3'd3;
//設置內部狀態暫存器
reg [2:0] state;
reg [2:0] next_state;

always @(posedge(clk)) begin
    if (reset) begin
        state = s3;
        moneyToPay = 0; 
        totalMoney <= 0;
    end else begin
        state = next_state; //改變為下個狀態
    end
end
//將s0~s3狀態描寫
always @(posedge(clk)) begin
        case (state)
            s0: 
             begin
               if (origin == destination )
                 costOfTicket <= 5; 
               else if ( ( origin - destination ) == 1 || ( destination - origin ) == 1 )
                 costOfTicket <= 10;
               else if ( ( origin - destination ) == 2 || ( destination - origin ) == 2 )
                 costOfTicket <= 15;
               else if ( ( origin - destination ) == 3 || ( destination - origin ) == 3 )
                 costOfTicket <= 20;
               else if ( ( origin - destination ) == 4 || ( destination - origin ) == 4 )
                 costOfTicket <= 25;
             end
            s1: moneyToPay = costOfTicket*howManyTicket ;
            s2:
             begin
               totalMoney = totalMoney + money;
               if ( totalMoney <  moneyToPay ) 
                 begin
                 if ( reset == 0 ) begin
                   $display("totalMoney:%d", totalMoney);
                   $display("you should need to pay:%d", moneyToPay - totalMoney );
                   end
                 end
               else
                 begin
                 temp = 0;
                 if ( reset == 0 ) begin
                   $display("totalMoney:%d", totalMoney);
                   $display("you should need to pay:%d", temp );
                    end
                 end
             end
            s3: 
               begin
               if ( reset == 0 ) begin
                 $display("change:%d", totalMoney - moneyToPay );
                 $display("Ticketnum:%d", howManyTicket );
                 end
               end
        endcase
end
//表示出state machine
always @(state or origin or destination or howManyTicket or totalMoney or moneyToPay or reset ) begin
    begin
        case (state)
            s0: if ( origin < 6 && origin > 0 && destination < 6 && destination > 0 ) begin
                next_state=s1;
            end else 
                next_state=s0;
            s1: begin
if (howManyTicket < 6 && howManyTicket > 0 ) 
                next_state=s2;
                else if ( reset == 1 ) 
                  next_state=s3; 
            else 
                next_state=s1; end
            s2: if ( totalMoney <  moneyToPay )
                next_state=s2;
                else
                next_state=s3;
            s3: next_state=s0;
            default:next_state=s0;
        endcase
    end
end
endmodule 



