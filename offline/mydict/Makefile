SRCS:=$(wildcard *.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))

CXX:=g++

CXXFLAGS:= -w -g -std=c++11

EXE:=main

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
