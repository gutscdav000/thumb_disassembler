/*   author: David Gutsch
     uname: dgutsch
     date; 10/28/2017   */

#include <stdio.h>

// prototypes && macros
void instruction_decoder(int);


char *registers[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6", "r7"};
char *special_registers[] = {"lr", "pc", "sp"};
char *operations[] = {"movs", "cmps", "adds", "subs"};
char *data_processing[] = {"ands", "eors", "lsls", "lsrs", "asrs", "adcs", "sbcs", "rors", "tsts", "rsbs", "cmps", "cmns", "orrs", "muls", "bics", "mvns"};

int inst;

int main(void) {
  printf(".text\n.syntax unified\n.thumb\n");

  while(scanf("%x", &inst) == 1) {
    //printf("hex = 0x%x\n",inst);
    // pass inst to function that decodes and prints instruction
    instruction_decoder(inst);
  }
  return 0;
}



void instruction_decoder(int encoded) {

  
  // add/sub register
  if((encoded >> 10) == 6) {
    int opcode = (((encoded >> 9) & 0b0000001) == 0)? 2: 3; // set op codes for ADD | SUB
    int rd = (encoded & 0b0000000000000111);
    int rm = (encoded >> 6) & 0b0000000111;
    int rn = (encoded >> 3) & 0b0000000000111;
    printf("   %s %s, %s, %s\n", operations[opcode], registers[rd], registers[rn], registers[rm]);
  }
  // add/sub immediate
  else if ((encoded >> 10) == 0x7) {
    int opcode = ((encoded >> 9) & 0b0000001) == 0? 2: 3;
    int rn = (encoded >> 3) & 7;
    int rd = (encoded & 0x0001) & 7;
    int imm3 = (encoded >> 6) & 7;   
    printf("   %s %s, %s, %d\n", operations[opcode], registers[rd], registers[rn], imm3);
  }
  // add/sub/cmp/mov immediate
  else if ((encoded >> 13) == 1) {
    int opcode = (encoded >> 11) & 3;
    int rdn = (encoded >> 8) & 0b00000111;
    int imm8 = (encoded & 0b0000000011111111);
    printf("   %s %s, %d\n", operations[opcode], registers[rdn], imm8);
  }
  
  // data processing
  else if(encoded >> 13 == 2) {
    int opcode = (encoded >> 6) & 0b0000001111;
    int rdn = (encoded & 0b111);
    int rm = (encoded >> 3) & 0b111;
    
    // reverse substract with carry has a funky syntax
    if(opcode == 9)
      printf("   %s %s, %s, #0\n", data_processing[9], registers[rdn], registers[rm]);
    else
      printf("   %s %s, %s\n", data_processing[opcode], registers[rdn], registers[rm]);
  }
  else {
    printf("   .hword 0x%x\n", encoded);
  }
  return;
}
