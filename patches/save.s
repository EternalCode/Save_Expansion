// save game function redirections
.org 0x080D9870
    ldr r2, =(HandleWriteSector|1)
    bx r2
.pool

.org 0x080D9E54
    ldr r2, =(HandleLoadSector|1)
    bx r2
.pool

.org 0x080DA248
    ldr r1, =(HandleSavingData|1)
    bx r1
.pool

// Disable read and write of sector 30 + 31
.org 0x0815D80C
    bx lr
.pool

.org 0x080DA5E0
    mov r0, #0xFF
    bx lr

// Disable the VRAM buffer being used for random screens
.org 0x080F5190
    mov r8, r8
    mov r8, r8
.pool

.org 0x080F52A0
    mov r8, r8
    mov r8, r8
.pool

.org 0x0813BAA8
    mov r8, r8
    mov r8, r8
.pool

// Disable help menu
.org 0x0813B8C2
    .byte 0x1D, 0xE0
.pool


// table adjustments
.org 0x080DA23C
    .word SaveSectionOffsets
.pool
