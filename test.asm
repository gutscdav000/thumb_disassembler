.text
.syntax unified
.thumb
   ands r0, r1
   adds r0, r1, r2
   adds r0, r6, 6
   adds r2, 128
   ands r0, r1
   subs r5, 85
   subs r3, r5, r7
   subs r1, r2, 3
   eors r0, r2
   lsls r0, r3
   lsrs r0, r4
   asrs r0, r5
   movs r0, 255
   movs r3, 128	
   cmps r1, 64
   eors r5, r6
   lsls r2, r4
   lsrs r6, r7
   asrs r1, r3
   adcs r4, r7
   sbcs r3, r4
   rors r0, r2
   tsts r4, r5
   rsbs r0, r1, #0
   cmp r0, r3
   cmn r0, r3
   orrs r0, r1
   muls r2, r5
   bics r0, r1
   mvns r3, r6
   adds r1, #128
   subs r3, #128
   cmp r1, r3
   cmp r5, r7
   mov r0, r1	
   mov r4, r7
   mov r7, r9
   add r0, r3
   add r5, r7
   add r0, r12
   add r3, r15
   add r0, r1	
   str r1, [r3, r4]
   str r0, [r2, r5]
   str r7, [r5, r6]
   strh r0, [r4, r7]
   strh r1, [r2, r3]
   strh r5, [r6, r0]
   strb r0, [r1, r2]
   strb r3, [r4, r5]
   strb r5, [r6, r7]
   ldrsb r0, [r3, r4]
   ldrsb r1, [r5, r2]
   ldrsb r6, [r7, r1]
   ldr r1, [r2, r3]
   ldr r0, [r4, r5]
   ldr r6, [r7, r4]
   ldrh r0, [r1, r2]
   ldrh r3, [r4, r5]
   ldrh r6, [r7, r1]
   ldrb r0, [r1, r2]
   ldrb r3, [r4, r5]
   ldrb r6, [r7, r3]
   ldrsh r0, [r1, r2]
   ldrsh r3, [r4, r5]
   ldrsh r6, [r7, r5]
   movs r0, r1
   movs r5, r7
   movs r7, r6
   bx r0
   bx r3
   bx r9
   bx r15
   blx r1
   blx r7
   blx r10
   blx r14
   str r1, [r3, 31]
   str r0, [r2, 16]
   str r5, [r7, 15]
   str r6, [sp, #255]
   str r4, [sp, #128]
   str r7, [sp, #80]
