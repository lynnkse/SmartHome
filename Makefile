CC = g++

CFLAGS = -g -c -std=gnu++11

INC_PATH = ./inc
SRC_PATH = ./src

OBJC = Agent.o

Agent.o : $(SRC_PATH)/Agent.cpp $(INC_PATH)/Agent.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/Agent.cpp -pthread 

Event.o : $(INC_PATH)/Event.h $(SRC_PATH)/Event.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)/Event.cpp

PubSubHub.o : $(INC_PATH)/PubSubHub.h $(SRC_PATH)/PubSubHub.cpp $(INC_PATH)/Event.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Agent.h
	$(CC) $(CFLAGS) $(SRC_PATH)/PubSubHub.cpp

# Agent Dynamic Libraries

ElevatorAgent.o : $(SRC_PATH)/ElevatorAgent.cpp $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Agent.h $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/ElevatorAgent.cpp -pthread -std=gnu++11


 


