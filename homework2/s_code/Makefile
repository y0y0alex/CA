.PHONY: clean

include ../../mk/toolchain.mk

CFLAGS = -march=rv32i_zicsr_zifencei -mabi=ilp32
ASFLAGS = -march=rv32i_zicsr_zifencei -mabi=ilp32
LDFLAGS = --oformat=elf32-littleriscv

%.o: %.S
	$(CROSS_COMPILE)as $(ASFLAGS) -o $@ $<

all: handwrite.elf 

handwrite.elf: handwrite.o
	 $(CROSS_COMPILE)ld -o $@ -T handwrite.ld $(LDFLAGS) $<

clean:
	$(RM) handwrite.elf handwrite.o