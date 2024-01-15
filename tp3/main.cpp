//Morais Pereira David
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include "include/tsl/hopscotch_map.h"
#include "include/tsl/hopscotch_set.h"

using namespace std;
using namespace tsl;

struct liaison {
    unsigned long long int x;
    unsigned long long int y;
};

struct last{
    unsigned long long int x;
};

vector<last> Glouton(vector<liaison>& l, vector<last>& x) {
    vector<last> res;
    
    hopscotch_map<unsigned long long int, unsigned long long int> count;
    for (const auto& i : l) {
        ++count[i.x];
        ++count[i.y];
    }

    while (!l.empty()) {
        unsigned long long int minL = INT_MAX;
        unsigned long long int point = 0;

        for (const auto& i : l) {
            unsigned long long int lMtn = count[i.x] + count[i.y];
            if (lMtn < minL) {
                minL = lMtn;
                point = i.x;
            }
        }

        hopscotch_set<unsigned long long int> pointN;

        for (const auto& i : l) {
            if (i.x == point || i.y == point) {
                pointN.insert(i.x);
                pointN.insert(i.y);
            }
        }

        vector<liaison> newL;
        newL.reserve(l.size());
        for (const auto& i : l) {
            if (pointN.find(i.x) == pointN.end() && pointN.find(i.y) == pointN.end()) {
                newL.push_back(i);
            }
        }
        l = move(newL);
        res.push_back({point});
    }
    return res;
}

void Write(string x, vector<last> l){
    ofstream os;
    os.open(x);
    if(os.is_open()){
        for(auto i : l){
            os << i.x << endl;
        }
    }
}

void Read(string x, vector<liaison> &l) {
    ifstream is;
    is.open(x);
    string a;
    if (is.is_open()) {
        while (getline(is, a)) {
            stringstream ss(a);
            string b;
            unsigned long long int i = 0;
            liaison c;
            while (getline(ss, b, ' ')) {
                try {
                    if (i == 0)
                        c.x = stoull(b);
                    else
                        c.y = stoull(b);
                    i++;
                } catch (const invalid_argument &ia) {
                    cerr << "Invalid argument: " << ia.what() << endl;
                } catch (const out_of_range &oor) {
                    cerr << "Out of range error: " << oor.what() << endl;
                }
            }
            l.push_back(c);
        }
    }
}

int main(){
    vector<string> files={
        "00030_000109_random_udg.edges",
        "00100_001156_qatar_udg.edges",
        "00300_001484_euronight_8nn.edges",
        "01000_002980_greece_del.edges",
        "03000_010884_paris_6nn.edges",
        "10000_024317_italy_4nn.edges",
        "20000_107456_jupiter_9nn.edges",
        "30000_089977_usnight_del.edges",
        "40000_119960_protein_del.edges"
    };
    vector<string> soluce={
        "00030_000109_random_udg.ind",
        "00100_001156_qatar_udg.ind",
        "00300_001484_euronight_8nn.ind",
        "01000_002980_greece_del.ind",
        "03000_010884_paris_6nn.ind",
        "10000_024317_italy_4nn.ind",
        "20000_107456_jupiter_9nn.ind",
        "30000_089977_usnight_del.ind",
        "40000_119960_protein_del.ind"
    };
    
    for(unsigned long long int i = 0; i < files.size(); i++){
        vector<liaison> l;
        vector<last> z;
        Read("./edge/"+files[i],l);
        Write("./edge/"+soluce[i],Glouton(l, z));
    }
}