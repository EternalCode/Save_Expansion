        .gba
        .thumb
        .open "roms/BPRE0.gba","build/multi.gba", 0x08000000

        .include "patches/save.s"

		.org 0x08FFFFFF
			.fill 0xFFFFFF, 0xFF

        .org 0x09700000
        .importobj "build/linked.o"
        .close
