CC = cc
CFLAGS = -g -Wall

PROG = regions_test
HDRS = regions.h
SRCS = main.c regions.c

OBJDIR = object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/regions.o

# compiling rules

# WARNING: *must* have a tab before each definition
$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

$(OBJDIR)/table.o: region.c $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c region.c -o $(OBJDIR)/region.o

$(OBJDIR)/main.o: main.c $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c main.c -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)



