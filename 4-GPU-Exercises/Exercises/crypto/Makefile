debug		:= 0
include		./Makefile.inc


all: clean encrypt2

encrypt2: encrypt2.cu
	$(NVCC) -c encrypt2.cu $(NVCCFLAGS) $(INCLUDES)
	$(LINKER) -o $(PROJ_BASE)/encrypt2 encrypt2.o timer.cc $(INCLUDES) $(CUDA_LIBS) $(CFLAGS) $(CUDA_LDFLAGS)


clean:
	rm -f ./encrypt2.o
	rm -f $(PROJ_BASE)/encrypt2
