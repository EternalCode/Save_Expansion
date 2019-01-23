#ifndef POKEAGB_CALLBACK_H_
#define POKEAGB_CALLBACK_H_

#include "types.h"
#include "sprite.h"

typedef void (*MainCallback)(void);
typedef void (*IntrCallback)(void);
typedef void (*IntrFunc)(void);
typedef void (*EraseFlash)(u16);

/**
 * Bits for the keypad;
 */
enum Keypad {
    KEY_A = (1 << 0),
    KEY_B = (1 << 1),
    KEY_SELECT = (1 << 2),
    KEY_START = (1 << 3),
    KEY_RIGHT = (1 << 4),
    KEY_LEFT = (1 << 5),
    KEY_UP = (1 << 6),
    KEY_DOWN = (1 << 7),
    KEY_L = (1 << 8),
    KEY_R = (1 << 9),

    /** Directional pad mask */
    KEY_DPAD = (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT),
};


struct Main
{
    /*0x000*/ MainCallback callback1;
    /*0x004*/ MainCallback callback2;

    /*0x008*/ MainCallback savedCallback;

    /*0x00C*/ IntrCallback vblankCallback;
    /*0x010*/ IntrCallback hblankCallback;
    /*0x014*/ IntrCallback vcountCallback;
    /*0x018*/ IntrCallback serialCallback;

    /*0x01C*/ vu16 intrCheck;

    /*0x020*/ u32 *vblankCounter1;
    /*0x024*/ u32 vblankCounter2;

    /*0x028*/ enum Keypad heldKeysRaw;           // held keys without L=A remapping
    /*0x02A*/ enum Keypad newKeysRaw;            // newly pressed keys without L=A remapping
    /*0x02C*/ enum Keypad heldKeys;              // held keys with L=A remapping
    /*0x02E*/ enum Keypad newKeys;               // newly pressed keys with L=A remapping
    /*0x030*/ enum Keypad newAndRepeatedKeys;    // newly pressed keys plus key repeat
    /*0x032*/ enum Keypad keyRepeatCounter;      // counts down to 0, triggering key repeat
    /*0x034*/ u16 watchedKeysPressed; // whether one of the watched keys was pressed
    /*0x036*/ u16 watchedKeysMask;       // bit mask for watched keys

    /*0x038*/ struct OamData oamBuffer[128];

    /*0x438*/ u8 state;

    /*0x439*/ u8 oamLoadDisabled:1;
    /*0x439*/ u8 inBattle:1;
    /*0x439*/ u8 field_439_x4:1;
};

struct Main gMain;

void SetMainCallback(MainCallback func);
void SetMainCallback2(MainCallback func);
void SetVBlankCallback(MainCallback func);
void SetHBlankCallback(MainCallback func);
void SetVCountCallback(IntrCallback callback);
void SetSerialCallback(IntrCallback callback);



#endif /* POKEAGB_CALLBACK_H_ */
