
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,   // background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
};
int comp;
char pad;
int i;

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void main(void)
{
  setup_graphics();
  // draw message  
  vram_adr(NTADR_A(2,2));
  vram_write("Rock, Paper, Scissors!", 22);
  vram_adr(NTADR_A(2,3));
  vram_write("choose your play!", 17);
  vram_adr(NTADR_A(2,5));
  vram_write("Up: Rock",8);
  vram_adr(NTADR_A(2,6));
  vram_write("Left: Paper",11);
  vram_adr(NTADR_A(2,7));
  vram_write("Right: Scissors",15);
  
  comp = rand()%(3-1)+1;
  
  

  if (comp ==1){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Rock. ", 15);
  };
  if (comp == 2){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Paper. ", 16);
  };
  if (comp ==3){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Scissors.", 20);
  };
  
  // enable rendering
  ppu_on_all();
  // infinite loop
  while(1) {
    i=0;
    pad = pad_trigger(i);
    
      if(pad & PAD_LEFT){        
      	vram_adr(NTADR_A(2,9));
      	vram_write("You choose Paper!!   ",21);     
      }
      else if(pad & PAD_RIGHT){
      	vram_adr(NTADR_A(2,9));
      	vram_write("You choose Scissors!!",21);        
      }
      else if(pad & PAD_UP){
        vram_adr(NTADR_A(2,9));
      	vram_write("You choose Rock!!    ",21); 
      }    
    
  
  }
  
  
}
