# Nome dell'eseguibile
EXECUTABLE = inizio

# Directory
SRC_DIR = src
INCLUDE_DIR = include

# Compilatore e flags
CXX = clang++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c++17 `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`

# File sorgente
SRCS = main.cpp MainFrame.cpp PlayerPanel.cpp GamePanel.cpp $(SRC_DIR)/tessera.cpp $(SRC_DIR)/dado.cpp $(SRC_DIR)/giocatore.cpp $(SRC_DIR)/tabellone.cpp $(SRC_DIR)/proprieta.cpp $(SRC_DIR)/inconvenienti.cpp $(SRC_DIR)/opportunita.cpp $(SRC_DIR)/prigione.cpp

# Regola principale
all: $(EXECUTABLE)

# Regola per creare l'eseguibile
$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Pulizia
clean:
	rm -f $(EXECUTABLE)

# Regole di phony
.PHONY: all clean