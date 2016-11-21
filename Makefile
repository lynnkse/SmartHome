CC = g++ -pthread

CFLAGS = -g -c -std=gnu++11  -fPIC 

INC_PATH = ./inc
SRC_PATH = ./src

OBJC = Agent.o Event.o PubSubHub.o AgentFactory.o app.o AgentLifecycleManager.o Config.o Configurator.o LogConfig.o 

.PHONY : clean rebuild clean_so rebuild_so

app : $(OBJC) 
	$(CC) $(OBJC) $(SRC_PATH)/Parser_t.cpp $(SRC_PATH)/Tokenizer_t.cpp -o app  -ldl -rdynamic 

Agent.o : $(SRC_PATH)/Agent.cpp $(INC_PATH)/Agent.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/Agent.cpp  -pthread 

Event.o : $(INC_PATH)/Event.h $(SRC_PATH)/Event.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)/Event.cpp

PubSubHub.o : $(INC_PATH)/PubSubHub.h $(SRC_PATH)/PubSubHub.cpp $(INC_PATH)/Event.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Agent.h
	$(CC) $(CFLAGS) $(SRC_PATH)/PubSubHub.cpp

AgentFactory.o : $(INC_PATH)/AgentFactory.h $(SRC_PATH)/AgentFactory.cpp $(INC_PATH)/AgentCreator.h $(INC_PATH)/Agent.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/AgentFactory.cpp

AgentLifecycleManager.o : $(INC_PATH)/AgentLifecycleManager.h $(SRC_PATH)/AgentLifecycleManager.cpp $(INC_PATH)/Agent.h $(INC_PATH)/AgentFactory.h $(INC_PATH)/PubSubHub.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/AgentLifecycleManager.cpp

Config.o : $(SRC_PATH)/Config.cpp $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/Config.cpp

LogConfig.o : $(SRC_PATH)/LogConfig.cpp $(INC_PATH)/LogConfig.h	
	$(CC) $(CFLAGS) $(SRC_PATH)/LogConfig.cpp

Configurator.o : $(SRC_PATH)/Configurator.cpp $(INC_PATH)/Configurator.h $(SRC_PATH)/Parser_t.cpp $(INC_PATH)/Parser_t.h $(SRC_PATH)/Tokenizer_t.cpp $(INC_PATH)/Tokenizer_t.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/Configurator.cpp 

app.o : $(SRC_PATH)/app.cpp $(INC_PATH)/Configurator.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/app.cpp 

# Agent Dynamic Libraries

LiveLogCreator.o : $(INC_PATH)/LiveLogCreator.h $(SRC_PATH)/LiveLogCreator.cpp $(INC_PATH)/LiveLog.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/LiveLogCreator.cpp

LiveLog.o : $(SRC_PATH)/LiveLog.cpp $(INC_PATH)/LiveLog.h $(INC_PATH)/LogConfig.h $(INC_PATH)/Config.h $(INC_PATH)/PubSubHub.h $(INC_PATH)/SafeDeque.h $(INC_PATH)/Event.h 
	$(CC) $(CFLAGS) $(SRC_PATH)/LiveLog.cpp

LiveLog.so : LiveLog.o LiveLogCreator.o
	$(CC) LiveLog.o LiveLogCreator.o -o LiveLog.so -shared 

ElevatorAgent.o : $(SRC_PATH)/ElevatorAgent.cpp $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Agent.h $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Event.h
	$(CC) $(CFLAGS) $(SRC_PATH)/ElevatorAgent.cpp -pthread -std=gnu++11 

ElevatorAgentCreator.o : $(INC_PATH)/ElevatorAgentCreator.h $(SRC_PATH)/ElevatorAgentCreator.cpp $(INC_PATH)/ElevatorAgent.h $(INC_PATH)/Config.h
	$(CC) $(CFLAGS) $(SRC_PATH)/ElevatorAgentCreator.cpp

ElevatorAgent.so : ElevatorAgent.o ElevatorAgentCreator.o
	$(CC) ElevatorAgent.o ElevatorAgentCreator.o -o ElevatorAgent.so -shared 

clean :
	rm -f *.o
	rm -f *.o

clean_so :
	rm -f *.o
	rm -f *.so

rebuild : clean app

rebuild_so : clean_so LiveLog.so ElevatorAgent.so

 


