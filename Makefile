CFLAGS = -std=c++11 -I./Engine
LDFLAGS = `pkg-config --cflags --libs xcb`

OBJS = main.o FEngine.o FWindow.o

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
	
FEngine.o : FWindow.o
	g++ $(CFLAGS) -c ./Engine/FEngine.cpp
	
FWindow.o : 
	g++ $(CFLAGS) -c ./Engine/Window/FWindow.cpp
	