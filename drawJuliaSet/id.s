.data
    msgStart :     .asciz "*****Input ID*****\n"
    msgq1 :        .asciz "**Please Enter Member1 ID:**\n"
    msgq2 :        .asciz "**Please Enter Member2 ID:**\n"
    msgq3 :        .asciz "**Please Enter Member3 ID:**\n"
    msgq4 :        .asciz "**Please Enter Command **\n"
    msgPrintAll :  .asciz "*****Print Team Member ID and ID Summation*****\n"
    msgIDSum :     .asciz "ID Summation = %d\n"
    msgEnd :       .asciz "*****End Print*****\n"
    NextLine :     .asciz "\n\n"
    PrintInt :     .asciz "%d\n"
    P :            .asciz "p"
    InputInt :     .asciz "%d"
    InputString :  .asciz "%s"

    ID1 :          .word 0       @int
    ID2 :          .word 0
    ID3 :          .word 0
    IDSum :        .word 0
    command :      .space 32
    ID1address:    .word 0
    ID2address:    .word 0
    ID3address:    .word 0
    IDSumaddress:  .word 0

    .text
        .globl  id   @Function
        .globl  ID1
        .globl  ID2
        .globl  ID3
        .globl  IDSum

id : stmfd  sp!,    {r4,r5,r6,lr}    @push return address onto stack

       ldr  r4,     =ID1address
       str  r0,     [r4]

       ldr  r4,     =ID2address
       str  r1,     [r4]

       ldr  r4,     =ID3address
       str  r2,     [r4]

       ldr  r4,     =IDSumaddress
       str  r3,     [r4]

       ldr  r0,     =msgStart        @load pointer to format string
        bl  printf                   @printf("*****Input ID*****\n")

       ldr  r0,     =msgq1
        bl  printf                   @printf("**Please Enter Member1 ID:**\n")
       ldr  r0,     =InputInt        @r0 = "%d"
       ldr  r1,     =ID1             @r1 = Int
        bl  scanf

       ldr  r0,     =msgq2
        bl  printf                   @printf("**Please Enter Member2 ID:**\n")
       ldr  r0,     =InputInt        @r0 = "%d"
       ldr  r1,     =ID2             @r1 = Int
        bl  scanf

       ldr  r0,     =msgq3
        bl  printf                   @printf("**Please Enter Member3 ID:**\n")
       ldr  r0,     =InputInt        @r0 = "%d"
       ldr  r1,     =ID3             @r1 = Int
        bl  scanf

        ldr  r1,     =ID1
       ldr  r1,     [r1]             @ ---addressing mode1--register immediate
       ldr  r2,     =ID2
       ldr  r2,     [r2]
       ldr  r3,     =ID3
       ldr  r3,     [r3]
       mov  r4,     #0               @r4 = 0
       cmp  r3,     r4               @set Z
     addne  r4,     r1, r2           @ ---conditional Execution1-Z clear(!=)
       cmp  r1,     r1               @set Z
     addeq  r4,     r3, r4           @ ---conditional Execution2-Z set(=) -- Operand2-1
     addpl  r4,     r4, #10          @r4 = r4 + 10 ---conditional Execution3
       sub  r4,     #10
       mov  r4,     r4, lsl #1       @r4 = r4 * 2 ---Operand2-2-logical shift left
       sub  r4,     r4, asr #1       @r4 = r4 - r4 / 2 -- Operand2-3-arithmetic shift right
       ldr  r5,     =IDSum
       cmp  r3,     r4
     ldreq  r4,     [r6, #10]!       @ ---addressing mode2
     ldreq  r4,     [r5],  #10       @ ---addressing mode3
       str  r4,     [r5]

       ldr  r1,     =ID1address
       ldr  r1,     [r1]
       ldr  r0,     =ID1
       ldr  r0,     [r0]
       str  r0,     [r1]

       ldr  r1,     =ID2address
       ldr  r1,     [r1]
       ldr  r0,     =ID2
       ldr  r0,     [r0]
       str  r0,     [r1]

       ldr  r1,     =ID3address
       ldr  r1,     [r1]
       ldr  r0,     =ID3
       ldr  r0,     [r0]
       str  r0,     [r1]

       ldr  r1,     =IDSumaddress
       ldr  r1,     [r1]
       ldr  r0,     =IDSum
       ldr  r0,     [r0]
       str  r0,     [r1]


       ldr  r0,     =msgq4
        bl  printf                   @printf("**Please Enter Command **\n")
       ldr  r0,     =InputString     @r0 = "%s"
       ldr  r1,     =command         @r1 = String
        bl  scanf
       ldr  r0,     =P
      ldrb  r0,     [r0]             @ p 8 bits
       ldr  r1,     =command
       ldr  r1,     [r1]
       cmp  r0,     r1
      blne  NotP                     @ if r0(p) != r1(command)->main

       ldr  r0,     =msgPrintAll
        bl  printf                   @printf("*****Print Team Member ID and ID Summation*****\n")
       ldr  r0,     =PrintInt
       ldr  r1,     =ID1
       ldr  r1,     [r1]
        bl  printf
       ldr  r0,     =PrintInt
       ldr  r1,     =ID2
       ldr  r1,     [r1]
        bl  printf
       ldr  r0,     =PrintInt
       ldr  r1,     =ID3
       ldr  r1,     [r1]
        bl  printf
       ldr  r0,     =NextLine
        bl  printf
       ldr  r0,     =msgIDSum
       ldr  r1,     =IDSum
       ldr  r1,     [r1]
        bl  printf
       ldr  r0,     =msgEnd
        bl  printf

       mov  r0,     #0
       mov  r1,     #0
       mov  r2,     #0
       mov  r3,     #0

     ldmfd  sp!,    {r4,r5,r6,lr}
       mov  pc,     lr

NotP:  ldr  r0,     =msgEnd
        bl  printf
       mov  r0,     #0
       mov  r1,     #0
       mov  r2,     #0
       mov  r3,     #0
     ldmfd  sp!,    {r4,r5,r6,lr}
       mov  pc,     lr









