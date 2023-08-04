#########################
# customise these
CFILES := main.c syscall_1.c
PROG := main
MAP := $(PROG).map
CFLAGS := -Wall -Wextra -g
LDFLAGS := -T linker.ld -Wl,-Map,$(MAP)
########################

CC := gcc

OBJFILES := $(CFILES:.c=.o)
DEPFILES := $(CFILES:.c=.d)

$(PROG) : $(OBJFILES)
	$(LINK.o) -o $@ $^

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES) $(MAP)

-include $(DEPFILES)
