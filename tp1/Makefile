CC = g++ # Compilateur C++
CFLAGS = -Wall -std=c++11 -Ofast # Options du compilateur

# Règle par défaut
all: main

# Compilation du fichier main.cpp en un exécutable main
main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

# Nettoyage des fichiers générés
clean:
	rm -f main
