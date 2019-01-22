#ifndef POKEAGB_SAVE_H_
#define POKEAGB_SAVE_H_

enum
{
    SAVE_NORMAL = 0,
    SAVE_LINK,
    SAVE_EREADER,
    SAVE_HALL_OF_FAME,
    SAVE_OVERWRITE_DIFFERENT_FILE,
    SAVE_HALL_OF_FAME_ERASE_BEFORE, // unused
};

// Each 4 KiB flash sector contains 3968 bytes of actual data followed by a 128 byte footer
#define SECTOR_DATA_SIZE 3968
#define SECTOR_FOOTER_SIZE 128


struct SaveBlockChunk {
    u8* data;
    u16 size
}

struct SaveSectionOffset {
    u16 toAdd; // offset really
    u16 size;
};


struct SaveBlockChunk gRamSaveSectionLocations[0xE];

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

extern struct SaveBlock2 *gSaveBlock2Ptr;


#endif /* POKEAGB_SAVE_H_ */
