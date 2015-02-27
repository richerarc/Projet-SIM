DEBUG=yes
CC=g++
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -pedantic -g
	LDFLAGS=
else
	CFLAGS=-W -Wall -pedantic
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
