.data
    data_1: .word 0x12345678
    data_2: .word 0xffffdddd
.text
    
main:
    lw s0, data_1   #s0 = A
    lw s1, data_2   #s1 = B
    li s2, 0        #s2: high 32 of number
    li s3, 0        #s3: low 32 of number
    li s4, 0        #used to check how many bit should shift
    
int_mul:
    slti t1, s4, 32
    beq t1, zero, exit
    srl t0, s1, s4
    andi t0, t0, 0x00000001        #check B's rightest bit
    beq t0, zero, skip            #if(rightest bit is zero) jump
    sll s5,s0,s4                    #s0 is A,S5 the low bit i want
    li t2, 32
    sub t2, t2, s4
    srl s6, s0, t2             #s0 is A, S6 the high bit i want
    add s7, s3, s5             #s7 is 32_low + low bit i want
    jal overflow_detect_function
    
no_overflow:
    #mv s3, s7
    add s2, s2, s6
    jal skip
    
skip:
    addi s4, s4 ,1
    jal int_mul

overflow_detect_function:
    sltu t3, s7, s3
    mv s3, s7
    beq t3, zero, no_overflow
    # if not jump  -->  overflow
    add s2, s2, s6
    addi s2, s2, 1
    addi s4, s4 ,1
    jal int_mul

exit:
    li a7,10
    ecall
