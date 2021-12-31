all: asm-O3 asm-O2

asm-O3:
	for name in rvv_strncpy rvv_strlen rvv_strcpy rvv_strcmp; do \
		riscv64-unknown-elf-gcc -mabi=lp64 -march=rv64imacv -O3 -S -o asm/$$name.O3.s $$name.c; \
	done

asm-O2:
	for name in rvv_strncpy rvv_strlen rvv_strcpy rvv_strcmp; do \
		riscv64-unknown-elf-gcc -mabi=lp64 -march=rv64imacv -O2 -S -o asm/$$name.O2.s $$name.c; \
	done
