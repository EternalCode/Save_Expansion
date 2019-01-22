#include "include/types.h"
#include "include/core_callback.h"
#include "include/memory.h"
#include "save.h"


/* TODO HandleWriteSector, HandleSavingData hooks */

u8* ParasiteSizeIndex = (u8*)0x20370B8;

struct SaveSectionOffset SaveSectionOffsets[] = {
    {SECTOR_DATA_SIZE * 0, 0xF24}, // saveblock2
    // 0xCC byes wasted

    {SECTOR_DATA_SIZE * 0, SECTOR_DATA_SIZE}, // saveblock 1
    {SECTOR_DATA_SIZE * 1, SECTOR_DATA_SIZE}, // saveblock 1
    {SECTOR_DATA_SIZE * 2, SECTOR_DATA_SIZE}, // saveblock 1
    {SECTOR_DATA_SIZE * 3, 0xD98}, // saveblock 1
    // 0x258 bytes wasted

    {SECTOR_DATA_SIZE * 0, SECTOR_DATA_SIZE}, // saveblock Pokemonstorage
    {SECTOR_DATA_SIZE * 1, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 2, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 3, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 4, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 5, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 6, SECTOR_DATA_SIZE},
    {SECTOR_DATA_SIZE * 7, SECTOR_DATA_SIZE},
    {0x7F80, 0x450},
    // 0xBA0 wasted
};

/* Any save sector that isn't full, we'll plop our data of these sizes in there */
u16 SaveBlockParasiteSizes[3] = {
        SECTOR_DATA_SIZE - 0xF24, // 0xCC
        SECTOR_DATA_SIZE - 0xD98, // 0x258
        SECTOR_DATA_SIZE - 0x450, // 0xBA0
};


u8 HandleWriteSector(u16 chunkId, const struct SaveBlockChunk *chunks)
{
    u16 i;
    u16 sectorNum;
    u8 *chunkData;
    u16 chunkSize;

    // select sector number
    sectorNum = chunkId + gFirstSaveSector;
    sectorNum %= NUM_SECTORS_PER_SAVE_SLOT;
    // select save slot
    sectorNum += NUM_SECTORS_PER_SAVE_SLOT * (gSaveCounter % 2);

    chunkData = chunks[chunkId].data; // gRamSaveSectionLocations[chunkID].data
    chunkSize = chunks[chunkId].size;

    // clear save section.
    memset((void*)gFastSaveSection, 0, sizeof(struct SaveSection));

    gFastSaveSection->id = chunkId;
    gFastSaveSection->signature = FILE_SIGNATURE;
    gFastSaveSection->counter = gSaveCounter;
    if (chunkSize != SECTOR_DATA_SIZE) {
        u8 index = *ParasiteSizeIndex;
        for (i = 0; i < chunkSize; i++) {
            gFastSaveSection->data[i] = chunkData[i];
        }
        /* Parasite Munch Munch */
        for (i = 0; i < SaveBlockParasiteSizes[index]; i++) {
            gFastSaveSection->data[i] = gSaveBlockParasitePtr[i];
        }
        gFastSaveSection->checksum = CalculateChecksum(gFastSaveSection->data, chunkSize);
    } else {
        for (i = 0; i < chunkSize; i++) {
            gFastSaveSection->data[i] = chunkData[i]; // gRamSaveSectionLocations[chunkID].data
        }
        gFastSaveSection->checksum = CalculateChecksum(chunkData, chunkSize);
    }
    return TryWriteSector(sectorNum, gFastSaveSection->data);
}


u8 HandleSavingData(u8 saveType)
{
    u8 i;
    u32 *backupPtr = gMain.vblankCounter1;
    //u8 *tempAddr;

    gMain.vblankCounter1 = NULL;
    UpdateSaveAddresses();

    switch (saveType)
    {
    /*
    case SAVE_HALL_OF_FAME_ERASE_BEFORE: // deletes HOF before overwriting HOF completely. unused
        for (i = 0xE * 2 + 0; i < 32; i++)
            EraseFlashSector(i);
        // fallthrough
    case SAVE_HALL_OF_FAME: // hall of fame.
        if (GetGameStat(GAME_STAT_ENTERED_HOF) < 999)
            IncrementGameStat(GAME_STAT_ENTERED_HOF);
        tempAddr = gDecompressionBuffer;
        HandleWriteSectorNBytes(0x1C, tempAddr, 0xF80);
        HandleWriteSectorNBytes(0x1D, tempAddr + 0xF80, 0xF80);
        // fallthrough
    */

    /* Ereader: save_write_to_flash(0, gRamSaveSectionLocations);*/

    case SAVE_LINK: // _081532C4
        SaveSerializedGame();
        for(i = 0; i < 5; i++)
            save_write_to_flash(i, gRamSaveSectionLocations);
        break;
    default:
        SaveSerializedGame();
        save_write_to_flash(0xFFFF, gRamSaveSectionLocations);
        break;

    }
    gMain.vblankCounter1 = backupPtr;
    return 0;
}

/*
u8 save_write_to_flash(u16 chunkId, const struct SaveBlockChunk *chunks)
{
    u32 retVal;
    u16 i;

    gFastSaveSection = &gSaveDataBuffer;
    if (chunkId != 0xFFFF)  // write single chunk
    {
        retVal = HandleWriteSector(chunkId, chunks);
    }
    else  // write all chunks
    {
        gLastKnownGoodSector = gFirstSaveSector; // backup the current written sector before attempting to write.
        gPrevSaveCounter = gSaveCounter;
        gFirstSaveSector++;
        gFirstSaveSector %= NUM_SECTORS_PER_SAVE_SLOT; // array count save sector locations
        gSaveCounter++;
        retVal = SAVE_STATUS_OK;

        for (i = 0; i < NUM_SECTORS_PER_SAVE_SLOT; i++)
            HandleWriteSector(i, chunks);

        // Check for any bad sectors
        if (gDamagedSaveSectors != 0) // skip the damaged sector.
        {
            retVal = SAVE_STATUS_ERROR;
            gFirstSaveSector = gLastKnownGoodSector;
            gSaveCounter = gPrevSaveCounter;
        }
    }

    return retVal;
}

*/

/*
void UpdateSaveAddresses()
{
    //u8* gRamSaveSectionLocations = (u8*)malloc_and_clear(sizeof(struct SaveSectionOffset) * 0x11);
    u32 i = 0;
    gRamSaveSectionLocations[i].data = (void*)(gSaveBlock2Ptr) + gSaveSectionOffsets[i].toAdd;
    gRamSaveSectionLocations[i].size = gSaveSectionOffsets[i].size;

    for (i = 1; i < 5; i++)
    {
        gRamSaveSectionLocations[i].data = (void*)(gSaveBlock1Ptr) + gSaveSectionOffsets[i].toAdd;
        gRamSaveSectionLocations[i].size = gSaveSectionOffsets[i].size;
    }

    for (i = 5; i < 14; i++)
    {
        gRamSaveSectionLocations[i].data = (void*)(gPokemonStoragePtr) + gSaveSectionOffsets[i].toAdd;
        gRamSaveSectionLocations[i].size = gSaveSectionOffsets[i].size;
    }
}
*/
