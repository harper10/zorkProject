#------------------------------------------------------------------------------

SOURCE=Main.cpp Zork_GameEngine.cpp Zork_ResourceManager.cpp Trigger.cpp Room.cpp Item.cpp Creature.cpp Container.cpp Condition.cpp
MYPROGRAM=zork_executable


CC=g++

FLAGS= -w -std=c++0x

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(FLAGS) $(SOURCE) -o$(MYPROGRAM) 

clean:

	rm -f $(MYPROGRAM)



