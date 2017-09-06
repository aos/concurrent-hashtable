CC=gcc
CFLAGS=-Wall -Wextra -Werror

SRCS = table.c table_funcs.c worker.c
OBJS = $(SRCS:.c=.o)
EXE = table

all: $(EXE) 

debug: DEBUG = -DDEBUG -g
debug: $(EXE) 

$(EXE): $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $(EXE) -lpthread

clean:
	rm -f table *.o 
