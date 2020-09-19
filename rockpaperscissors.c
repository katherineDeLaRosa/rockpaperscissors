
#include <stdlib.h>
#include <string.h>
#include<time.h>


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// include NESLIB header
#include "neslib.h"
#include "neslib.h"
#include <stdio.h> 
#include <stdlib.h>

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

/*{pal:"nes",la
out:"nes"}*/
// setup PPU and tables




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
int index;
char CpuGuess;
char UserGuess;
int wins;



void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}


void title_screen() 
{

  vram_adr(NTADR_A(3,2));	
  vram_write("Rock, Paper, Scissors!", 22);
  vram_adr(NTADR_A(6,22));	
  vram_write("Press start to begin", 20);  
  ppu_on_all();
  

  
 while(1)
  {
    
    if(pad_trigger(0)&PAD_START) break;    
    
  }
  
  ppu_off();
}// title_screen



void check(char user, char cpu){ // delete to fix
  
  if(user == 'r'){ // user choice == rock
    if(cpu == 's'){ // if cpu is scissors you win
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You won !!!!      ", 18);
      //wins++;for the rounds 
      ppu_on_all();      
    }
    else if(cpu == 'r'){// if cpu is rock you tied
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You tied !!!!     ", 18);      
      ppu_on_all();         
    }
    else{ // if cpu is paper you loose
      ppu_off();
      vram_adr(NTADR_A(8,23));
      vram_write("You lost.          ",18);      
      ppu_on_all();
    }
  }
  else if(user == 'p'){ // user choice == paper
    if(cpu == 'r'){ // if cpu is rock you win
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You won !!!!      ", 18);
      //wins++; for the rounds 
      ppu_on_all();      
    }
    else if(cpu == 'p'){ // if cpu is paper you tied
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You tied !!!!     ", 18);
      ppu_on_all();         
    }
    else{ // if cpu is scissors you loose
      ppu_off();
      vram_adr(NTADR_A(8,23));
      vram_write("You lost.          ",18);
      ppu_on_all();
    }
  }
  else{ // user choice == scissors
    if(cpu == 'p'){ // if cpu is paper you win
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You won !!!!      ", 18);
      //wins++; for the rounds
      ppu_on_all();      
    }
    else if(cpu == 's'){ // if cpu is scissors you tied
      ppu_off();
      vram_adr(NTADR_A(8,23));	
      vram_write("You tied !!!!     ", 18);
      ppu_on_all();         
    }
    else{ // if cpu is rock you loose
      ppu_off();
      vram_adr(NTADR_A(8,23));
      vram_write("You lost.          ",18);
      ppu_on_all();
    }
    
  }  
}// check

void wonLost(int win){
  if(win >= 3){
    ppu_off();
    vram_adr(NTADR_A(8,19));
    vram_write("You lost to the cpu :/.  ",26);
    ppu_on_all();
    
  }
  else{
    ppu_off();
    vram_adr(NTADR_A(8,19));
    vram_write("You won against the cpu!!!",26);
    ppu_on_all();
    
  }
  
  
}

void guess()
{   
  ppu_off();
  vram_adr(NTADR_A(2,2));
  vram_write("Rock, Paper, Scissors!", 23);
  vram_adr(NTADR_A(4,3));
  vram_write("choose your play!", 17);
  vram_adr(NTADR_A(2,5));
  vram_write("Up: Rock",8);
  vram_adr(NTADR_A(2,6));
  vram_write("Left: Paper",11);
  vram_adr(NTADR_A(2,7));
  vram_write("Right: Scissors",15);
  vram_adr(NTADR_A(6,22));	
  vram_write("                         ", 20); 
  ppu_on_all();
  
  comp = (rand()%(3-1))+1;
  comp = (rand()%(3))+1;
  
  while(1) {    
    pad = pad_trigger(i);
    
      
      if(pad & PAD_LEFT){        
      	vram_adr(NTADR_A(2,9));
      	vram_write("You choose Rock!!   ",21);     
        UserGuess = 'r';
        break;
       
      }      
      else if(pad & PAD_UP){
        vram_adr(NTADR_A(2,9));
      	vram_write("You choose Paper!!    ",21); 
        UserGuess = 'p';
        break;
        
      } //else if  
      else if(pad & PAD_RIGHT){
      	vram_adr(NTADR_A(2,9));
      	vram_write("You choose Scissors!!",21); 
        UserGuess = 's';
        break;
        
      }//else if        
  
  }//while  
  ppu_off();

  if (comp ==1){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Rock.    ", 20);
     CpuGuess ='r';
  };
  if (comp == 2){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Paper.   ", 20);
     CpuGuess = 'p';
  };
  if (comp ==3){
     vram_adr(NTADR_A(450,5));
     vram_write("Cpu chose Scissors.", 20);
     CpuGuess ='s';
  };
  
  // enable rendering
  ppu_on_all();
  // infinite loop
  
  
  check(UserGuess,CpuGuess);// delete to fix
  
  
}//guess

int rounds;
void main(void) {
  setup_graphics();  
  title_screen();
  rounds =0;
  wins = 0;
 
  while (rounds < 5) 
  {          
     guess();  
     //rounds++;// for the rounds
  } 
  //wonLost(wins);  // for the rounds
    
}



