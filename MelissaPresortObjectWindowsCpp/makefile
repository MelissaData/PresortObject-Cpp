# Melissa Presort Object Windows C++

CXX=cl
CXXFLAGS=-Zi -EHsc
LDLIBS=mdPresort.lib
RM=del /q /f

all: MelissaPresortObjectWindowsCpp.exe clean

MelissaPresortObjectWindowsCpp.exe:	Main.cpp mdPresort.h mdPresortEnums.h
	$(CXX) $(CXXFLAGS) Main.cpp PresortObject.cpp $(LDLIBS) /Fe:.\Build\MelissaPresortObjectWindowsCpp.exe

clean:
	$(RM) *.obj *.ilk *.pdb *.h.hash *.lib.hash 

