CFLAGS = -std=c++11
LDFLAGS = `pkg-config --cflags --libs xcb`

OBJS = main.o FEngine.o FWindow.o FInputManager.o FEngineLoop.o DummyPlayerController.o

.PHONY: test clean

# build and run
test : $(OBJS)
	g++ -g $(OBJS) -o main $(LDFLAGS)
	rm *.o
	
clean :
	rm -f main
	rm *.o
	
main : main.o
	g++ $(CFLAGS) $(OBJS) -o main $(LDFLAGS)
	
main.o : main.cpp 
	g++ $(CFLAGS) -c main.cpp
	
FEngine.o : FWindow.o FInputManager.o
	g++ $(CFLAGS) -c ./Engine/FEngine.cpp
	
FWindow.o : 
	g++ $(CFLAGS) -c ./Engine/Window/FWindow.cpp
	
FInputManager.o : 
	g++ $(CFLAGS) -c ./Engine/InputManager/FInputManager.cpp

FEngineLoop.o : FInputManager.o
	g++ $(CFLAGS) -c ./Engine/FEngineLoop.cpp
	
DummyPlayerController.o : FInputManager.o
	g++ $(CFLAGS) -c ./Engine/DummyPlayerController.cpp