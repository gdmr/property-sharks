# Nome dell'eseguibile
EXECUTABLE = inizio

# Directory
SRC_DIR = src
INCLUDE_DIR = include

# Compilatore e flags
CXX = clang++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c++17
LDFLAGS =

# File sorgente
SRCS = main.cpp $(SRC_DIR)/banca.cpp $(SRC_DIR)/tessera.cpp $(SRC_DIR)/dado.cpp $(SRC_DIR)/giocatore.cpp $(SRC_DIR)/gioco.cpp $(SRC_DIR)/tabellone.cpp

# Regola principale
all: $(EXECUTABLE)

# Regola per creare l'eseguibile
$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pulizia
clean:
	rm -f $(EXECUTABLE)

# Regole di phony
.PHONY: all clean