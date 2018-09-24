/*   author: David Gutsch
     date:   9/10/2018*/

#include <stdio.h>

// prototypes && macros
void instruction_decoder(int);


char *registers[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
char *special_registers[] = {"lr", "pc", "sp"};
char *operations[] = {"movs", "cmps", "adds", "subs"};
char *data_processing[] = {"ands", "eors", "lsls", "lsrs", "asrs", "adcs", "sbcs", "rors", "tsts", "rsbs", "cmp", "cmn", "orrs", "muls", "bics", "mvns"};
char *load_store[] = {"str", "strh", "strb", "ldrsb", "ldr", "ldrh", "ldrb", "ldrsh"};

int inst;

int main(void) {
  printf(".text\n.syntax unified\n.thumb\n");

  while(scanf("%x", &inst) == 1) {
    //printf("hex = 0x%x\n",inst);
    // pass inst to function that decodes and prints instruction
    instruction_decoder(inst);

    /* eventually. . . differentiate 16-bit and 32-bit instructions
       if bit[11:15] == 0b111xx && bit[11:15] != 0b11100 -> 
                     32bit_instruction_decoder(inst)
       else -> 16bit_instruction_decoder(inst)
     */
  }
  return 0;
}



void instruction_decoder(int encoded) {

  
  // add/sub register
  // T1 adds & subs
  if((encoded >> 10) == 6) {
    int opcode = (((encoded >> 9) & 0b0000001) == 0)? 2: 3; // set op codes for ADD | SUB
    int rd = (encoded & 0b0000000000000111);
    int rm = (encoded >> 6) & 0b0000000111;
    int rn = (encoded >> 3) & 0b0000000000111;
    printf("   %s %s, %s, %s\n", operations[opcode], registers[rd], registers[rn], registers[rm]);
  }
  // bx & blx
  else if((encoded >> 8) == 0b01000111) {
    char* operation = ((encoded >> 7) & 0b000000001) == 1? "blx": "bx";
    int rm = (encoded >> 3) & 0b0000000001111;
    printf("   %s %s\n", operation, registers[rm]);
  }
  //  add & movs 
  else if((encoded >> 10) == 0b010001) {
    // movs rd rm
    if (((encoded >> 8) & 0b00000011) == 0x2) {
      int rd = encoded & 0b0000000000000111;
      int rm = (encoded >> 3) & 0b0000000001111;
      printf("   mov %s, %s\n", registers[rd], registers[rm]);
    }
    // add T2
    else { // ((encoded >> 8) & 0b0000011) == 0x0
      int rdn = 0x07 & encoded;
      int rm = (encoded >> 3) & 0b0000000001111;
      printf("   add %s, %s\n", registers[rdn], registers[rm]);
    }
  }
  // add/sub immediate 3
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
    long long int imm8 = (encoded & 0x00ff);
    printf("   %s %s, %lld\n", operations[opcode], registers[rdn], imm8);
  }
  // data processing
  else if(encoded >> 10 == 0x10) {
    int opcode = (encoded >> 6) & 0b0000001111;
    int rdn = (encoded & 0b111);
    int rm = (encoded >> 3) & 0b111;
    
    // reverse substract with carry has a funky syntax
    if(opcode == 9)
      printf("   %s %s, %s, #0\n", data_processing[9], registers[rdn], registers[rm]);
    else
      printf("   %s %s, %s\n", data_processing[opcode], registers[rdn], registers[rm]);
  }
  // movs rd rm
  else if ((encoded >> 6) == 0) {
    int rd = encoded & 0b0000000000000111;
    int rm = (encoded >> 3) & 0b0000000000111;
    printf("   movs %s, %s\n", registers[rd], registers[rm]);
  }
  // Load and store (register offset) instructions
  else if((encoded >> 12) == 0x5) {    
    int opcode = (encoded >> 9) & 0b0000111;
    int rm = (encoded >> 6) & 0b0000000111;
    int rn = (encoded >> 3) & 0b0000000000111;
    int rt = encoded & 0b0000000000000111;
    printf("   %s %s, [%s, %s]\n",load_store[opcode], registers[rt], registers[rn] , registers[rm]);
  }
  /* untested cases */
  // str rt, [rn, #imm5] T1
  // ldr rt, [rn, #imm5] 
  else if((encoded >> 12) == 0b0110) {
    printf("untested 1\n");
    int opcode = ((encoded >> 11) & 0b00001) == 1? 4: 0;
    int rt = encoded & 0b0000000000000111;
    int rn = (encoded >> 3) & 0b0000000000111;
    int imm5 = (encoded >> 6) & 0b0000011111;
    printf("   %s %s, [%s, %d]\n", load_store[opcode], registers[rt], registers[rn], imm5);
  }
  // str str rt, [sp, #imm8] T2
  // ldr rt, [sp, #imm8] 
  else if((encoded >> 12) == 0b1001) {
    printf("untested 2\n");
    int opcode = ((encoded >> 11) & 0b00001) == 1? 4: 0;
    int rt = (encoded >> 8) & 0b00000111;
    //int imm8 = encoded & 0x00ff;
    int imm8 = encoded & 0b0000000011111111;
    printf("   %s %s, [SP, %d]\n", load_store[opcode], registers[rt], imm8);
  }
  else {
    printf("   .hword 0x%x\n", encoded);
  }
  return;
}
