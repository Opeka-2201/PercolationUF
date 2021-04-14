OFILESLIST = main.o UnionFindList.o Threshold.o Percolation.o
OFILESTREE = main.o UnionFindTree.o Threshold.o Percolation.o
TARGETLIST = threshold_list
TARGETTREE = threshold_tree

CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

.PHONY: all clean run

LDFLAGS = -lm

all: $(TARGETLIST) $(TARGETTREE)
clean:
	rm -f $(OFILESLIST) $(OFILESTREE) $(TARGETLIST) $(TARGETTREE)
run: $(TARGETLIST) $(TARGETTREE)
	./$(TARGETLIST)
	./$(TARGETTREE)
$(TARGETLIST): $(OFILESLIST)
	$(CC) -o $(TARGETLIST) $(OFILESLIST) $(LDFLAGS)
$(TARGETTREE): $(OFILESTREE)
	$(CC) -o $(TARGETTREE) $(OFILESTREE) $(LDFLAGS)

Threshold.o: Threshold.c Threshold.h Percolation.h
UnionFindList.o: UnionFindList.c UnionFind.h
UnionFindTree.o: UnionFindTree.c UnionFind.h
main.o: main.c Threshold.h
maincurves.o: maincurves.c Threshold.h
