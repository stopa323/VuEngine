CFLAGS = -std=c++11 -I./Engine
LDFLAGS = 

OBJS = main.o FEngine.o

.PHONY: test clean

# build and run
test : $(OBJS)
	g++ -g $(OBJS) -o main $(LDFLAGS)
	rm *.o
	
clean :
	rm -f main
	
main : main.o
	g++ $(CFLAGS) $(OBJS) -o main $(LDFLAGS)
	
main.o : main.cpp 
	g++ $(CFLAGS) -c main.cpp
	
FEngine.o : 
	g++ $(CFLAGS) -c ./Engine/FEngine.cpp
	