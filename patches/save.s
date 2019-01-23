// save game hooks
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

.org 0x0815D80C
    bx lr
.pool

.org 0x080DA5E0
    mov r0, #0xFf
    bx lr

// table adjustments
.org 0x080DA23C
    .word SaveSectionOffsets
.pool
