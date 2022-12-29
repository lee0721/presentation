
module stimulus ;
reg clk, reset;
reg [2:0]howManyTicket, origin, destination;
reg [5:0]money;
wire [6:0]costOfTicket, moneyToPay, totalMoney;  
vending_machine v(clk, reset, howManyTicket, origin, destination,
 money, costOfTicket, moneyToPay, totalMoney);
initial clk = 1'b0;
always #5 clk = ~clk;

initial			
begin
  reset = 1;
  #5 reset = 0; origin = 3'd2; destination = 3'd5;
  #10 howManyTicket = 3'd3;
  #10 money = 10 ;			
  #5 money = 5 ;
  #5 money = 10 ;			
  #10 reset = 1; 
  #10 origin = 4;
  #10destination = 2;
  #10 howManyTicket = 5;
  #10 money = 10 ;			
  #10 money = 50 ;			
  #10 money = 10 ;					
end
endmodule
