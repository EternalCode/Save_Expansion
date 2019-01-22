#ifndef POKEAGB_SPRITE_H_
#define POKEAGB_SPRITE_H_

#include "types.h"

struct OamData {
   u32 y : 8;

   /**
    * 0=Normal, 1=Affine, 2=Disable, 3=Double Size
    */
   u32 affine_mode : 2;

   /**
    * 0=Normal, 1=Semi-Transparent, 2=OBJ Window, 3=Prohibited
    */
   u32 obj_mode : 2;

   /**
    * Enable mosaic
    */
   u32 mosaic : 1;

   /**
    * 1=256 colours
    */
   u32 bpp : 1;

   /**
    * 0=Square,1=Horizontal,2=Vertical,3=Prohibited
    */
   u32 shape : 2;

   u32 x : 9;
   u32 matrix_num : 3; // bits 3/4 are h-flip/v-flip if not in affine mode
   u32 h_flip : 1;
   u32 v_flip : 1;
   /**
    * Size  Square   Horizontal  Vertical
    * 0     8x8      16x8        8x16
    * 1     16x16    32x8        8x32
    * 2     32x32    32x16       16x32
    * 3     64x64    64x32       32x64
    */
   u32 size : 2;

   u16 tile_num : 10;

   /**
    * 0-3; 0=Highest
    */
   u16 priority : 2;
   u16 palette_num : 4;
   u16 affine_param;
};

#endif /* POKEAGB_SPRITE_H_ */
