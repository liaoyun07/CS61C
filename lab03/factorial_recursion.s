.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    addi t1, x0, 1
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    beq a0, t1, return
    addi sp, sp, -8
    sw ra, 0(sp)
    sw a0, 4(sp)
    addi a0, a0, -1
    jal ra, factorial
return:
    lw ra, 0(sp)
    lw t0, 4(sp)
    addi sp, sp, 8
    mul a0, a0, t0
    #can't use x0 insted 0
    jalr x0, ra, 0