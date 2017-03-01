VULKAN_SDK_PATH = /opt/VulkanSDK/1.0.37.0/x86_64
CFLAGS = -std=c++11 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --cflags --libs xcb` -lvulkan 

OBJS = main.o UObject.o FActor.o FPawn.o FController.o STransform.o FFPSMeter.o FChrono.o FEngine.o FWindow.o FInputManager.o FEngineLoop.o FSimpleRenderer.o DummyPlayerController.o FShaderManager.o

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

FSimpleRenderer.o : FShaderManager.o
	g++ $(CFLAGS) -c ./Engine/Renderer/FSimpleRenderer.cpp	

FShaderManager.o :
	g++ $(CFLAGS) -c ./Engine/Renderer/FShaderManager.cpp	

FChrono.o :
	g++ $(CFLAGS) -c ./Engine/Physics/Timing/FChrono.cpp	

FFPSMeter.o :
	g++ $(CFLAGS) -c ./Engine/Game/FFPSMeter.cpp

STransform.o :
	g++ $(CFLAGS) -c ./Engine/Game/Entity/STransform.cpp

UObject.o :
	g++ $(CFLAGS) -c ./Engine/Game/Entity/UObject.cpp

FActor.o :
	g++ $(CFLAGS) -c ./Engine/Game/Entity/FActor.cpp

FPawn.o :
	g++ $(CFLAGS) -c ./Engine/Game/Entity/FPawn.cpp

FController.o :
	g++ $(CFLAGS) -c ./Engine/Game/Controller/FController.cpp
	
DummyPlayerController.o : FInputManager.o
	g++ $(CFLAGS) -c ./Engine/DummyPlayerController.cpp