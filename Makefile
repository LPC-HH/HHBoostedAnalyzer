CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(LDFLAGS) $(shell root-config --glibs) -lMathMore
CPPFLAGS += -g -Wall -Wextra -Wno-sign-compare

TARGET = RunHHTo4BNtupler

SRC = app/RunHHTo4BNtupler.cc src/HHTo4BNtupler.cc src/EventAnalyzer.cc include/Events.hh

OBJ = $(SRC:.cc=.o) src/Events.o 

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^


%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o src/*.o $(TARGET) app/*.o include/*.o *~
