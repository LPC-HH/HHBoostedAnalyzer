CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(LDFLAGS) $(shell root-config --glibs) -lMathMore
CPPFLAGS += -g -Wall -Wextra -Wno-sign-compare

TARGET = RunHHTo4BNtupler
TARGET3 = SkimNtuple

SRC = app/RunHHTo4BNtupler.cc src/HHTo4BNtupler.cc src/EventAnalyzer.cc include/Events.hh
SRC3 = app/SkimNtuple.cc

OBJ = $(SRC:.cc=.o) src/Events.o 
OBJ3 = $(SRC3:.cc=.o)

all : $(TARGET) $(TARGET3) 

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

$(TARGET3) : $(OBJ3)
	$(LD) $(CPPFLAGS) -o $(TARGET3) $(OBJ3) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o src/*.o $(TARGET) $(TARGET3) app/*.o include/*.o *~
