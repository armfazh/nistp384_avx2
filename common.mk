############
# common.mk
############


##################
## Folders
SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
BIN=$(SELF_DIR)bin
SRC=$(SELF_DIR)src
LIB=$(SELF_DIR)lib
INCLUDE=$(SELF_DIR)include


##################
## Compilers
ifndef GCC
GCC=gcc
endif
ICC=icc
CLANG=clang

##################
## Compilers' Flags
# gcc flags
GCC_CFLAGS= -march=haswell -mtune=intel -mno-vzeroupper  
# icc flags
ICC_CFLAGS= -ipo -xHost  -funroll-loops -opt-multi-version-aggressive -restrict
# clang flags
CLANG_CFLAGS= -march=native -mavx2 -fomit-frame-pointer -fwrapv -funroll-loops -fvectorize -fslp-vectorize -fslp-vectorize-aggressive

##################
## Select Compiler
ifeq ($(CC),icc)
CC=$(ICC)
AR=xiar
CFLAGS=$(ICC_CFLAGS)
else ifeq ($(CC),clang)
CC=$(CLANG)
CFLAGS=$(CLANG_CFLAGS)
else
CC=$(GCC)
AR=gcc-ar
CFLAGS=$(GCC_CFLAGS)
endif

TARGET = nistp384_avx2

CFLAGS+=-O3 -Wall -Wextra -I$(INCLUDE) -L$(LIB)
LDFLAGS+= -l$(TARGET)_$(CC)
#ASFLAGS=--defsym IACA_MARKS_OFF=0x1
	
%.o: %.s
	$(CC) -o $@ $(CFLAGS) -c $^ $(LDFLAGS)


