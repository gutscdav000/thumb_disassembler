#	author: David Gutsch
#	uname: dgutsch
#	date: 10/28/2017

disassembler: main.c
	rm -f disassembler test.bin test.out test.hex *.o
	gcc main.c -o disassembler
test:
	arm-none-eabi-as test.asm -o test.o
	arm-none-eabi-objcopy test.o -O binary --only-section=.text test.bin
	hexdump -x test.bin |sed -e 's/^[^ ]*//' > test.hex
	./disassembler < test.hex > test.out
	diff -y test.asm test.out || exit 0

add:
	arm-none-eabi-as add.asm -o add.o
	arm-none-eabi-objcopy add.o -O binary --only-section=.text add.bin
	hexdump -x add.bin |sed -e 's/^[^ ]*//' > add.hex
	#cat add.hex
	./disassembler < add.hex > add.out
	diff -y add.asm add.out || exit 0

clean:
	rm -f disassembler *.bin *.out *.hex *.o
