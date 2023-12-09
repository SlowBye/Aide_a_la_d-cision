#Morais Pereira David
#!/bin/bash

# Compilation du fichier main.cpp en un exécutable main
g++ -Wall -std=c++11 -Ofast -o main main.cpp

# Vérification si la compilation a réussi
if [ $? -eq 0 ]; then
    # Exécution du programme
    ./main

    echo "Compilation et Exécution terminée avec succès."
else
    echo "Erreur de compilation."
fi
