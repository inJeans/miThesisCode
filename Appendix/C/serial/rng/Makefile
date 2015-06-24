#  Makefile.sh
#  CUDADSMC
#
#  Created by Christopher Watkins on 1/08/2014.
#  Copyright (c) 2014 WIJ. All rights reserved.

# Colour coding the makfile :-)
NO_COLOR=\033[0m
OK_COLOR=\033[32m
ERROR_COLOR=\033[31m
WARN_COLOR=\033[35m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

# Common binaries
GCC   ?= g++-5
CLANG ?= /usr/bin/clang

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin) #If building on an OSX system
	CUDA_PATH= /Developer/NVIDIA/CUDA-6.5
	CUDA_INC = -I/Developer/NVIDIA/CUDA-6.5/include
	CUDA_LIB = -L/Developer/NVIDIA/CUDA-6.5/lib
	NVCC     = $(CUDA_PATH)/bin/nvcc -ccbin $(CLANG)
	INCLUDE = -I /usr/local/hdf5/include
	LIB = -L /usr/local/hdf5/lib
else                     #If building on a Linux system
	CUDA_INC = -I/usr/local/cuda-5.5/include
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)  #If 64 bit
		CUDA_LIB = -L/usr/local/cuda-5.5/lib64
	else
		CUDA_LIB = -L/usr/local/cuda-5.5/lib
	endif
	NVCC = nvcc
	INCLUDE = -I /usr/local/hdf5/1.8.5/include
	LIB = -L /usr/local/hdf5/1.8.5/lib
endif

#NVCCFLAGS = -m 64 --relocatable-device-code=true -arch=compute_30 -code=sm_30,compute_30
NVCCFLAGS = -m 64 --relocatable-device-code=false -arch=compute_30 -code=sm_30,compute_30

OMPFLAGS = -fopenmp

BUILDDIR = bin/
OBJDIR   = $(BUILDDIR)obj/
SRCDIR   = src/

EXEC = $(BUILDDIR)serialrng

INCLUDE += -I include/ -I ../../common-C/include

all: $(EXEC)

debug: NVCCFLAGS += -g -G
#debug: clean
debug: $(EXEC)

profile: NVCCFLAGS += -pg
profile: $(EXEC)

$(EXEC): $(addprefix $(OBJDIR), rng-serial.o rngTest-serial.o )
	@echo 'Building file: $<'
	@echo 'Invoking: C Linker'
	$(GCC) -o $@ $^ $(INCLUDE) -ltestu01 -lmylib $(LIB)
	@echo "Finished building: $< $(OK_STRING)"
	@echo ' '

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo 'Building file: $<'
	@echo 'Invoking: OpenMP Compiler'
	$(GCC) $(OMPFLAGS) -o $@ -c $? $(INCLUDE)
	@echo "Finished building: $< $(OK_STRING)"
	@echo ' '

run:
	make
	{ time ./$(BUILDDIR)serialrng ; } | tee output.txt
	@echo "" >> output.txt
	@echo "----------------------------------------" >> output.txt
	@echo "" >> output.txt
	tput bel

clean:
	rm -rf $(OBJDIR)*.o $(BUILDDIR)serialrng
