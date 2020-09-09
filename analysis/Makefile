CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(LDFLAGS) $(shell root-config --glibs) -lMathMore
CPPFLAGS += -g -Wall -Wextra -Wno-sign-compare

TARGET  = PlotROC
TARGET1 = SelectHHTo4B_PNet
TARGET2 = SelectHHTo4B_OptimizeCuts
TARGET3 = MakeAlphabetInputs

SRC  = PlotROC.cc
SRC1 = SelectHHTo4B_PNet.cc
SRC2 = SelectHHTo4B_OptimizeCuts.cc
SRC3 = app/SelectHHTo4B_PassFailAlphabet.cc

OBJ  = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)

all : $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET1) : $(OBJ1)
	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET2) : $(OBJ2)
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET3) : $(OBJ3)
	$(LD) $(CPPFLAGS) -o $(TARGET3) $(OBJ3) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

# $(TARGET4) : $(OBJ4)
# 	$(LD) $(CPPFLAGS) -o $(TARGET4) $(OBJ4) $(LDFLAGS)
# 	@echo $@
# 	@echo $<
# 	@echo $^
#
# $(TARGET5) : $(OBJ5)
# 	$(LD) $(CPPFLAGS) -o $(TARGET5) $(OBJ5) $(LDFLAGS)
# 	@echo $@
# 	@echo $<
# 	@echo $^
#
# $(TARGET6) : $(OBJ6)
# 	$(LD) $(CPPFLAGS) -o $(TARGET6) $(OBJ6) $(LDFLAGS)
# 	@echo $@
# 	@echo $<
# 	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<


%.o : %.C
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<

clean :
	rm -f *.o $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) *~
