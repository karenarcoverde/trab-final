CXX = g++ 
CXFLAGS = -Wall -std=c++11 -I 

LIBS = -lsqlite3

executable = programa

all: $(executable)

$(executable): library.o main.o
	$(CXX) -o $@ $^ $(CXFLAGS) -l $(LIBS)

main.o: main.cpp library.cpp library.h
	$(CXX) -c -o $@ $< $(CXFLAGS) -l $(LIBS)

library.o: library.cpp library.h
	$(CXX) -c -o $@ $< $(CXFLAGS) -l $(LIBS)


.PHONY : clean


clean:
	rm $(executable) *.o




