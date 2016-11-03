all:kruskal lcs prim

kruskal:kruskal.c
	gcc kruskal.c -o kruskal.out

lcs: lcs.c
	gcc lcs.c -o lcs.out

prim: prim.c
	gcc prim.c -o prim.out

clean:
	rm -rf *.o -f kruskal.out lcs.out prim.out

