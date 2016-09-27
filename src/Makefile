# Makefile for a RISA Device Driver
#

CC = gcc
CFLAGS := -Wall -g -D_LARGEFILE64_SOURCE -D_GNU_SOURCE 
LIBS += -lm -lpthread -lrt

SRCS := \
	main.c \
	csv.c \
	detect.c \
	io.c \
	sec.c \
	util.c

ransom: $(SRCS) 
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) 

clean:
	@$(RM) *.o core *~ ransom 

