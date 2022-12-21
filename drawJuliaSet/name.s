.data
    msgStart :   .asciz "*****Print Name*****\n"
    teamNumber : .asciz "Team 36\n"
    student1 :   .asciz "CHUNG-MING HUANG\n"
    student2 :   .asciz "YU-HAN LEE\n"
    student3 :   .asciz "YU-HAN LEE\n"
    msgEnd :     .asciz "*****End Print*****\n"

.text
    .globl name @Function
    .globl teamNumber
    .globl student1
    .globl student2
    .globl student3

name:   stmfd sp!, {lr}          @push return address onto stack
        ldr   r0,  =msgStart     @load pointer to format string
        mov   r1,  r13           @back up r13 to r1
        mov   r2,  #0            @r2 = 0
        mov   r3,  #0            @r3 = 0
        adds  r2,  r3            @r2+r3
        adcs  r13, r1, r2        @r13 = r1(r13) + r2(0) set CPSR
        bl    printf             @printf("*****Print Name*****\n")

        ldr   r0,  =teamNumber
        bl printf                @printf("Team 36\n")

        ldr   r0,  =student1
        bl printf                @printf("CHUNG-MING HUANG\n")

        ldr   r0,  =student2
        bl printf                @printf("YU-HAN LEE\n")

        ldr   r0,  =student3
        bl printf                @printf("YU-HAN LEE\n")

        ldr   r0,  =msgEnd
        bl printf                @printf("*****End Print*****\n")

        mov   r0,  #0            @r0 = 0
        mov   r1,  #0            @r1 = 0
        ldmfd sp!, {lr}          @pop return address from stack
        mov   pc,  lr            @return from name


