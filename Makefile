CC=gcc
CFLAGS=-c -Wall 
OBJECTS=table.o table_funcs.o worker.o

table: $(OBJECTS)
	$(CC) $(OBJECTS) -o table -O3 -lpthread

clean:
	rm -f table *.o 
