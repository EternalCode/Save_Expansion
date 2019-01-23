/* Math */
__aeabi_idiv = 0x081E3B68|1;
__aeabi_idivmod = 0x081E3B68|1;
__aeabi_uidiv = 0x081E3B68|1;
__aeabi_uidivmod = 0x081E3B68|1;


/*
 * core_callback.h
 */
gMain = 0x030030F0;
SetMainCallback = 0x080565E0|1;
SetMainCallback2 = 0x08000544|1;
SetVBlankCallback = 0x080006F4|1;
SetHBlankCallback = 0x08000700|1;
SetVCountCallback = 0x0800070C|1;
SetSerialCallback = 0x08000718|1;


/*
 * save.h
 */

 gRamSaveSectionLocations = 0x030053B0;
 gSaveBlock1Ptr = 0x03005008;
 gSaveBlock2Ptr = 0x0300500C;
 gSaveBlock3Ptr = 0x030050010;
 gFirstSaveSector = 0x03005380;
 gSaveCounter = 0x03005390;
 gFastSaveSection = 0x03005394;

 SaveSerializedGame = 0x0804C300|1;
 UpdateSaveAddresses = 0x080DA1D4|1;
 CalculateChecksum = 0x080DA1A8|1;
 TryWriteSector = 0x080D99D8|1;
 save_write_to_flash = 0x080D97D0|1;
 DoReadFlashWholeSection = 0x080DA190|1;


/*
 * Memory.h
 */
 malloc_init = 0x08002B80|1;
 malloc = 0x08002B9C|1;
 malloc_and_clear = 0x08002BB0|1;
 free = 0x08002BC4|1;
 memcpy = 0x081E5E78|1;
 memset = 0x081E5ED8|1;
