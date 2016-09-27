# Makefile for a RISA Device Driver
#

CC = gcc
#FTL := ../../ftl
#INCLUDE := ../../include
#COMMON := ../../common
#DM_COMMON := ../../devices/common

CFLAGS := -Wall -g -D_LARGEFILE64_SOURCE -D_GNU_SOURCE 
LIBS += -lm -lpthread -lrt

#INCLUDES = -I$(PWD)/$(INCLUDE) \
		   #-I$(PWD)/$(COMMON)/utils \
		   #-I$(PWD)/$(COMMON)/3rd \
		   #-I$(PWD)/$(FTL) \
		   #-I$(PWD)/$(DM_COMMON) \

#CFLAGS += -D HASH_BLOOM=20 \
		  #-D CONFIG_ENABLE_MSG \
		  #-D CONFIG_ENABLE_DEBUG \
		  #-D USER_MODE \
		  #-D USE_PMU \
	#	  -D USE_NEW_RMW \

#DMLIB := ../../devices/libramdrive/libramdrive.a
#LIBFTL := libftl.a

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

