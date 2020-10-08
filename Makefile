CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(LDFLAGS) $(shell root-config --glibs) -lMathMore
CPPFLAGS += -g -Wall -Wextra -Wno-sign-compare

TARGET  = diHiggs
TARGET1 = NormalizeNtuple
TARGET2  = diHiggsPlots
TARGET3 = SkimNtuple
TARGET4 = RunJetNtupler
TARGET5 = RunDileptonNtupler
TARGET6 = RunHHTo4BNtupler
TARGET7 = RunJetHTTriggerNtupler
TARGET8 = RunMakeMCPileupDistribution

SRC = app/diHiggs.cc src/Events.cc src/CommandLineInput.cc
SRC1 = app/NormalizeNtuple.cc src/CommandLineInput.cc src/SimpleTable.cc
SRC2 = app/diHiggsPlots.cc src/hh_tree.cc src/CommandLineInput.cc
SRC3 = app/SkimNtuple.cc
SRC4 = app/RunJetNtupler.cc src/JetNtupler.cc src/EventAnalyzer.cc include/Events.hh
SRC5 = app/RunDileptonNtupler.cc src/DileptonNtupler.cc src/EventAnalyzer.cc include/Events.hh
SRC6 = app/RunHHTo4BNtupler.cc src/HHTo4BNtupler.cc src/JetCorrectionUncertainty.cc src/JetCorrectorParameters.cc src/SimpleJetCorrectionUncertainty.cc src/EventAnalyzer.cc include/Events.hh
SRC7 = app/RunJetHTTriggerNtupler.cc src/JetHTTriggerNtupler.cc src/EventAnalyzer.cc include/Events.hh
SRC8 = app/RunMakeMCPileupDistribution.cc src/MakeMCPileupDistribution.cc src/EventAnalyzer.cc include/Events.hh

OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)
OBJ4 = $(SRC4:.cc=.o) src/Events.o 
OBJ5 = $(SRC5:.cc=.o) src/Events.o 
OBJ6 = $(SRC6:.cc=.o) src/Events.o 
OBJ7 = $(SRC7:.cc=.o) src/Events.o 
OBJ8 = $(SRC8:.cc=.o) src/Events.o 

all : $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8)

$src/RazorEvents.o: $(SRCDIR)/RazorEvents.C $(INCLUDEDIR)/RazorEvents.h
	$(CXX) $(SRCDIR)/RazorEvents.C $(CXXFLAGS) -I$(INCLUDEDIR) -c $(LDFLAGS) $(LIBS) -o $@ $(CXX14FLAGS)

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

$(TARGET4) : $(OBJ4)
	$(LD) $(CPPFLAGS) -o $(TARGET4) $(OBJ4) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

$(TARGET5) : $(OBJ5)
	$(LD) $(CPPFLAGS) -o $(TARGET5) $(OBJ5) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

$(TARGET6) : $(OBJ6)
	$(LD) $(CPPFLAGS) -o $(TARGET6) $(OBJ6) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

$(TARGET7) : $(OBJ7)
	$(LD) $(CPPFLAGS) -o $(TARGET7) $(OBJ7) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

$(TARGET8) : $(OBJ8)
	$(LD) $(CPPFLAGS) -o $(TARGET8) $(OBJ8) $(LDFLAGS) 
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o src/*.o $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) app/*.o include/*.o *~
