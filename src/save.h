#ifndef POKEAGB_SAVE_H_
#define POKEAGB_SAVE_H_


// Each 4 KiB flash sector contains 3968 bytes of actual data followed by a 128 byte footer
#define SECTOR_DATA_SIZE 0xFF0
#define SECTOR_FOOTER_SIZE 128
#define NUM_SECTORS_PER_SAVE_SLOT 14
#define PLAYER_NAME_LENGTH 8
#define FILE_SIGNATURE 0x08012025
#define gSaveBlockParasite 0x0203B174
#define parasiteSize 0xEC4

// yes that's var 0x8000. It will be used for save index tracking.
u8* ParasiteSizeIndex = (u8*)0x020370B8;

enum
{
    SAVE_NORMAL = 0,
    SAVE_LINK,
    SAVE_EREADER,
    SAVE_HALL_OF_FAME,
    SAVE_OVERWRITE_DIFFERENT_FILE,
    SAVE_HALL_OF_FAME_ERASE_BEFORE, // unused
};


struct SaveBlockChunk {
    u8* data;
    u16 size;
};

struct SaveSectionOffset {
    u16 toAdd; // offset really
    u16 size;
};

struct SaveBlockChunk gRamSaveSectionLocations[0xE];

struct Time
{
    /*0x00*/ s16 days;
    /*0x02*/ s8 hours;
    /*0x03*/ s8 minutes;
    /*0x04*/ s8 seconds;
};

#define POKEMON_SLOTS_NUMBER 412
#define DEX_FLAGS_NO ((POKEMON_SLOTS_NUMBER / 8) + ((POKEMON_SLOTS_NUMBER % 8) ? 1 : 0))

struct Pokedex
{
    /*0x00*/ u8 order;
    /*0x01*/ u8 unknown1;
    /*0x02*/ u8 nationalMagic; // must equal 0xDA in order to have National mode
    /*0x03*/ u8 unknown2;
    /*0x04*/ u32 unownPersonality; // set when you first see Unown
    /*0x08*/ u32 spindaPersonality; // set when you first see Spinda
    /*0x0C*/ u32 unknown3;
    /*0x10*/ u8 owned[DEX_FLAGS_NO];
    /*0x44*/ u8 seen[DEX_FLAGS_NO];
};

struct UnkSaveBlock2Substruct_55C
{
    /* 0x000:0x55C */ u8 unk_00_0:1;
    u8 unk_00_1:1;
    /* 0x001:0x55D */ u8 unk_01;
    /* 0x002:0x55E */ u8 unk_02[2];
    /* 0x004:0x560 */ u16 unk_04[2];
    /* 0x008:0x564 */ u16 unk_08[2];
    /* 0x00C:0x568 */ u16 unk_0C[2];
    /* 0x010:0x56C */ u8 unk_10;
    /* 0x011:0x56D */ u8 unk_11[3];
    /* 0x014:0x570 */ u16 unk_14;
    /* 0x016:0x572 */ u8 unk_16;
}; // size: 0x018

#define LINK_B_RECORDS_COUNT 5

struct LinkBattleRecord
{
    u8 name[PLAYER_NAME_LENGTH];
    u16 trainerId;
    u16 wins;
    u16 losses;
    u16 draws;
};

struct LinkBattleRecords
{
    struct LinkBattleRecord entries[LINK_B_RECORDS_COUNT];
    u8 languages[LINK_B_RECORDS_COUNT];
};

struct BerryCrush
{
    u16 berryCrushResults[4];
    u32 berryPowderAmount;
    u32 unk;
};

struct SaveBlock2
{
    /*0x000*/ u8 playerName[PLAYER_NAME_LENGTH];
    /*0x008*/ u8 playerGender; // MALE, FEMALE
    /*0x009*/ u8 specialSaveWarp;
    /*0x00A*/ u8 playerTrainerId[4];
    /*0x00E*/ u16 playTimeHours;
    /*0x010*/ u8 playTimeMinutes;
    /*0x011*/ u8 playTimeSeconds;
    /*0x012*/ u8 playTimeVBlanks;
    /*0x013*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x014*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
    u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
    u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
    u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
    u16 optionsBattleSceneOff:1; // whether battle animations are disabled
    u16 regionMapZoom:1; // whether the map is zoomed in
    /*0x018*/ struct Pokedex pokedex;
    /*0x090*/ u8 filler_90[0x8];
    /*0x098*/ struct Time localTimeOffset;
    /*0x0A0*/ struct Time lastBerryTreeUpdate;
    /*0x0A8*/ u32 field_A8;
    /*0x0AC*/ u8 filler_AC[0x3F4];
    /*0x4A0*/ u32 unk_4A0[0x2F];
    /*0x55c*/ struct UnkSaveBlock2Substruct_55C unk_55C;
    /*0x574*/ u8 filler_574[0x324];
    /*0x898*/ u16 mapView[0x100];
    /*0xA98*/ struct LinkBattleRecords linkBattleRecords;
    /*0xAF0*/ struct BerryCrush berryCrush;
    /*0xB00*/ u8 filler_B00[0x420];
    /*0xF20*/ u32 encryptionKey;
};

struct SaveSection
{
    u8 data[0xFF4];
    u16 id;
    u16 checksum;
    u32 signature;
    u32 counter;
}; // size is 0x1000


struct SaveSection* gFastSaveSection;
struct SaveBlock2 *gSaveBlock2Ptr;
u16* gFirstSaveSector;
u32* gSaveCounter;


void SaveSerializedGame(void);
void UpdateSaveAddresses(void);
u16 CalculateChecksum(void* data, u16 size);
u8 DoReadFlashWholeSection(u8 sector, struct SaveSection *section);
u8 TryWriteSector(u8 sector, u8 *data);
u8 save_write_to_flash(u16 chunkId, const struct SaveBlockChunk *chunks);

#endif /* POKEAGB_SAVE_H_ */
