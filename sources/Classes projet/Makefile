DEBUG=yes
CC=g++
ifeq ($(DEBUG),yes)
	CFLAGS= -std=c++11 -W -Wall -pedantic -L/usr/local/lib -lsdl2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf -g
	LDFLAGS=
else
	CFLAGS=-std=c++11 -W -Wall -pedantic -L/usr/local/lib -lsdl2
	LDFLAGS=
endif


EXEC=Hello
SRC= $(wildcard *.cpp)
HEAD= $(wildcard *.h)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: $(HEAD)

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

exec :
ifdef SystemRoot
	@$(EXEC)
else
	@./$(EXEC)
endif

mrproper: clean
	@rm -rf $(EXEC)
clean:
	@rm -rf *.o
