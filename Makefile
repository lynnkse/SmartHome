CC = g++

CFLAGS = -g -c -std=gnu++11

INC_PATH = ./inc
SRC_PATH = ./src

OBJC = Agent.o Event.o PubSubHub.o AgentFactory.o ElevatorAgentCreator.o app.o AgentLifecycleManager.o Config.o

app : $(OBJC) ElevatorAgent.o
	$(CC) $(OBJC) ElevatorAgent.o -o app

Agent.o : $(SRC_PATH)/Agent.cpp $(INC_PATH)/Agent.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/Agent.cpp -pthread 

Event.o : $(INC_PATH)/Event.h $(SRC_PATH)/Event.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)/Event.cpp

PubSubHub.o : $(INC_PATH)/PubSubHub.h $(SRC_PATH)/PubSubHub.cpp $(INC_PATH)/Event.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Agent.h
	$(CC) $(CFLAGS) $(SRC_PATH)/PubSubHub.cpp

AgentFactory.o : $(INC_PATH)/AgentFactory.h $(SRC_PATH)/AgentFactory.cpp $(INC_PATH)/AgentCreator.h $(INC_PATH)/Agent.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/AgentFactory.cpp

ElevatorAgentCreator.o : $(INC_PATH)/ElevatorAgentCreator.h $(SRC_PATH)/ElevatorAgentCreator.cpp $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/ElevatorAgentCreator.cpp

AgentLifecycleManager.o : $(INC_PATH)/AgentLifecycleManager.h $(SRC_PATH)/AgentLifecycleManager.cpp $(INC_PATH)/Agent.h $(INC_PATH)/AgentFactory.h $(INC_PATH)/PubSubHub.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/AgentLifecycleManager.cpp

Config.o : $(SRC_PATH)/Config.cpp $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/Config.cpp

app.o : $(SRC_PATH)/app.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)/app.cpp

# Agent Dynamic Libraries

ElevatorAgent.o : $(SRC_PATH)/ElevatorAgent.cpp $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Agent.h $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/ElevatorAgent.cpp -pthread -std=gnu++11


 


