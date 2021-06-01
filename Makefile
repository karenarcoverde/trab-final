CXX = g++ 
CXFLAGS = -Wall -std=c++11 -I

OBJS = library.o main.o
LIBS = sqlite3


PROGRAM  = library
all: $(PROGRAM)


$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(CXFLAGS) -l $(LIBS)

cpp.o:
	$(CXX) -c -o $@ $< $(CXFLAGS) -l $(LIBS)  

clean:
	rm -f *.o $(PROGRAM)




