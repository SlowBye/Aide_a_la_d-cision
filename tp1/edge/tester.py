#!/usr/bin/python3

import sys
import math
import itertools

if len(sys.argv) != 2:
  print("./tester.py n")
  print("n = 30, 100, 300, 1000, 3000, 10000, 20000, 30000, 40000")
  exit(1)

n = int(sys.argv[1])

fnh = {
  30: '00030_000109_random_udg',
  100: '00100_001156_qatar_udg',
  300: '00300_001484_euronight_8nn',
  1000: '01000_002980_greece_del',
  3000: '03000_010884_paris_6nn',
  10000: '10000_024317_italy_4nn',
  20000: '20000_107456_jupiter_9nn',
  30000: '30000_089977_usnight_del',
  40000: '40000_119960_protein_del'
}

def readEdges(fn):
  E = []
  with open(fn) as f:
    for line in f:
      if line:
        E.append(tuple(int(x) for x in line.split()))
  return E

def buildGraph(E):
  G = {}
  for u,v in E:
    if u in G:
      G[u].add(v)
    else:
      G[u] = {v}
    if v in G:
      G[v].add(u)
    else:
      G[v] = {u}
      
  return G

def readInd(fn):
  with open(fn) as f:
    I = {int(line) for line in f if line}
  return I

def testInd(G,I):
  err = 0
  
  for v in I:
    if v not in G:
      print("Erreur sommet inexistant:", v)
      err += 1
      
  for u,v in E:
    if v in I and u in I:
      print("Erreur sommets adjacents:", u, v)
      err += 1
      
  return err

E = readEdges(fnh[n]+".edges")
G = buildGraph(E)
I = readInd(fnh[n]+".ind")
print("La taille de I est", len(I))

err = testInd(G,I)
if err:
  print("Il y a", err, "erreurs")
else:
  print("Pas d'erreur")
