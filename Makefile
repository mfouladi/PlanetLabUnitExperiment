CC=gcc
CFLAGS=-I.
DEPS = unitExperiment.h
OBJ = unitExperimentSender.o unitExperimentReceiver.o main.o  

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

unitExperiment: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@rm *.o

.PHONY: clean

clean:
	@rm -f *.o *~ core unitExperiment 
