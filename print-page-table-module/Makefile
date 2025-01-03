obj-m += print_page_tables.o

# Specify the path to the kernel source tree
KDIR := /lib/modules/$(shell uname -r)/build

# Use the default target to build the module
all:
	make -C $(KDIR) M=$(PWD) modules

# Clean up generated files
clean:
	make -C $(KDIR) M=$(PWD) clean
