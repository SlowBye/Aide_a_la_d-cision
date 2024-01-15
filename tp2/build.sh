g++ -Wall -c -I/opt/ibm/ILOG/CPLEX_Studio2211/cplex/include -I /opt/ibm/ILOG/CPLEX_Studio2211/concert/include main.cpp
g++ -o main -L/opt/ibm/ILOG/CPLEX_Studio2211/cplex/lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio2211/concert/lib/x86-64_linux/static_pic main.o -lilocplex -lconcert -lcplex -lpthread -ldl

if [ $? -eq 0 ]; then
    ./main
else
    echo "Erreur de compilation."
fi