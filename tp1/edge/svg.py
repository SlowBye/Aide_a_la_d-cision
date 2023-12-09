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
  P = {}
  with open(fn) as f:
    for line in f:
      if line:
        E.append(tuple(int(x) for x in line.split()))
      for v in E[-1]:
        P[v] = (v // 100000, v % 100000)
  return E,P

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
  err = set()
  
  for v in I:
    if v not in G:
      print("Erreur sommet inexistant:", v)
      sys.exit(1)
      
  for u,v in E:
    if u in I and v in I:
      print("Erreur sommets adjacents:", u, v)
      err.add((u,v))
      
  return err

def writeSVG(fn, E, P, I, conf):
  imgsz = 1000.0
  x0 = min([p[0] for p in P.values()])
  y0 = min([p[1] for p in P.values()])
  x1 = max([p[0] for p in P.values()])
  y1 = max([p[1] for p in P.values()])
  sz = max(x1-x0, y1-y0)
  r2 = 10.0

  with open(fn, "w") as fsvg:
    fsvg.write('<?xml version="1.0" encoding="utf-8"?>\n')
    fsvg.write(f'<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="{imgsz+2*r2}" height="{imgsz+2*r2}">\n')
    
    fsvg.write(f' <text x="0" y="20">|I|={len(I)}</text>\n')

    for e in E:
      q1 = (r2 + (P[e[0]][1]-y0) * imgsz / sz, r2 + (x1-P[e[0]][0]) * imgsz / sz)
      q2 = (r2 + (P[e[1]][1]-y0) * imgsz / sz, r2 + (x1-P[e[1]][0]) * imgsz / sz)
      fsvg.write(f' <polygon stroke="black" stroke-width="1" fill="none" points="{q1[0]},{q1[1]} {q2[0]},{q2[1]}"/>\n')

    for i,p in P.items():
      q = (r2 + (p[1]-y0) * imgsz / sz, r2 + (x1-p[0]) * imgsz / sz)
      if i in I:
        fsvg.write(f' <circle stroke="green" fill="lightgreen" stroke-width="2" cx="{q[0]}" cy="{q[1]}" r="5">\n')
        fsvg.write(f'  <title>{i} I</title>\n')
        fsvg.write(' </circle>\n')
      else:
        fsvg.write(f' <circle stroke="blue" stroke-width="2" cx="{q[0]}" cy="{q[1]}" r="3">\n')
        fsvg.write(f'  <title>{i}</title>\n')
        fsvg.write(' </circle>\n')

    for e in conf:
      q1 = (r2 + (P[e[0]][1]-y0) * imgsz / sz, r2 + (x1-P[e[0]][0]) * imgsz / sz)
      q2 = (r2 + (P[e[1]][1]-y0) * imgsz / sz, r2 + (x1-P[e[1]][0]) * imgsz / sz)
      fsvg.write(f' <polygon stroke="red" stroke-width="2" fill="none" points="{q1[0]},{q1[1]} {q2[0]},{q2[1]}"/>\n')

    fsvg.write("</svg>\n")

E,P = readEdges(fnh[n]+".edges")
G = buildGraph(E)
I = readInd(fnh[n]+".ind")
print("La taille de I est", len(I))

err = testInd(G,I)
if err:
  print("Il y a des erreurs")
else:
  print("Pas d'erreur")
  
writeSVG(fnh[n]+".ind.svg", E, P, I, err)
print("Fichier SVG cree")

