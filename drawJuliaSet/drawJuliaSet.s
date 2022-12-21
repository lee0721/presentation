.data
.text
    .globl  drawJuliaSet   @Function
.constant:
    .word   1500           @.constant
    .word   4000000        @.constant+4
    .word   0xffff         @.constant+8


drawJuliaSet: stmfd  sp!,  {r4-r11,lr}    @push return address onto stack
              mov    r11,  r0             @r11 = r0(cY)
              mov    r4,   r2             @r4 = r2(frame)
			  mov   r2,  r14  @ copy lr
			  adds  r14,  r0,  r15  @ !!!!!!
			  movge   r14,  r2  @ back r14 ***conditional Execution***
			  
              mov    r5,   #0             @r5 = 0 int x=0
forx:         cmp    r5,   #640           @ x<640
              bge    outx

              mov    r6,   #0             @r6 = 0 int y=0
fory:         cmp    r6,   #480           @ y < 480
              bge    outy

              @ zx = 1500 * (x - 320) / 320;
              sub    r0,   r5,   #320     @temp = x - 320 ***Operand2***
              ldr    r1,   .constant      @r1 = 1500
              mul    r0,   r1,   r0       @temp(r0) = r1(1500)*temp
              mov    r1,   #320           @r1 = 320
              bl     __aeabi_idiv         @r0 = (1500*(x - 320))(r0) / 320(r1)
              mov    r8,   r0             @zx(r8) = r0

              @ zy = 1000 * (y - (height>>1)) / (height>>1);
			  mov    r0,   #480           @r0 = 480(height)
              mov    r2,   r0,  LSR #1    @height>>1  ***Operand2***
              sub    r0,   r6,   r2       @temp = y - (height>>1)
              mov    r1,   #1000          @r1 = 1000
			  cmp	 r0,   r1             @help next instruction
			  moveq  r0,   r1			  @***conditional Execution***
              mul    r0,   r1   ,r0       @temp = 1000*temp
              mov    r1,   r2             @r1 = r2 (height>>1)
              bl     __aeabi_idiv         @r0 = 1000 * (y - (height>>1)) / (height>>1)
              mov    r9,   r0             @zy(r9) = r0

              mov    r7,  #255            @i = 255

              mul    r0,   r8,   r8       @r0 = r8(zx) * r8(zx)
              mul    r1,   r9,   r9       @r1 = r9(zy) * r9(zy)
              add    r2,   r0,   r1       @r2 = r0(zx * zx) + r1(zy * zy)
              ldr    r3,   .constant+4    @r3 = 4000000
              cmp    r2,   r3
              bge    whileout             @zx * zx + zy * zy >= 4000000
              @zx * zx + zy * zy < 4000000
              cmp    r7,  #0
              ble    whileout             @i <= 0
              @i > 0

while:        sub    r0,   r0,   r1       @r2 = zx * zx - zy * zy
              mov    r1,   #1000          @r1 = 1000
              bl     __aeabi_idiv         @r0 = (zx * zx - zy * zy) / 1000
              sub    r10,  r0,   #700     @r10(tmp) = (zx * zx - zy * zy) / 1000 - 700
              mul    r0,   r8,   r9       @r0 = r8(zx) * r9(zy)
              mov    r1,   #500           @r1 = 500
              bl     __aeabi_idiv         @r0 = zx*zy/500
              add    r9,   r0,   r11      @zy = zx*zy/500 + cY
              mov    r8,   r10            @zx = tmp
              sub    r7,   #1             @i--

              mul    r0,   r8,   r8       @r0 = r8(zx) * r8(zx)
              mul    r1,   r9,   r9       @r1 = r9(zy) * r9(zy)
              add    r2,   r0,   r1       @r2 = r0(zx * zx) + r1(zy * zy)
              ldr    r3,   .constant+4    @r3 = 4000000
              cmp    r2,   r3
              bge    whileout             @zx * zx + zy * zy >= 4000000
              @zx * zx + zy * zy < 4000000
			  subge  r2,	r2,	  r3	  @***conditional Execution***
              cmp    r7,   #0
              ble    whileout             @i <= 0
              @i > 0
              b      while

whileout:
              @ color = (i & 0xff) | ((i & 0xff) << 8 );
              and    r0,   r7,   #0xff    @ r0 = i & 0xff
              mov    r1,   #8
              orr    r7,   r0,   r0, LSL r1 @ r7 = (i & 0xff) | ((i & 0xff) << 8 ) ***Operand2***

              @ color = (~color)&0xffff
              ldr    r0,   .constant+8    @r0 = 0xffff
              bic    r7,   r0,   r7       @r7 = (~r7) & 0xffff

              @frame[y][x] = color;
              @frame[y][x] = frame + 1280*y +2*x
              mov    r0,   r4             @r0 = frame
              mov    r1,   #1280          @r1 = 1280
              mul    r1,   r1,  r6        @r1 = 1280*y
              mov    r2,   #2             @r2 = 2
              mul    r2,   r2,  r5        @r2 = 2*x
              add    r0,   r0,  r1        @r0 = frame + 1280*y
              add    r0,   r0,  r2        @r0 = frame + 1280*y +2*x
              strh   r7,  [r0]

              add    r6,   #1             @y++
              b      fory

outy:         add    r5,   #1             @x++
              b      forx

outx:         ldmfd  sp!,  {r4-r11, lr}   @end
              mov    pc, lr

