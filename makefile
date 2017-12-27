CFLAGS = -Wall -pedantic  
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJS   = init.o load_media.o my_texture.o my_timer.o variables.o heli.o arena.o delete_and_close.o main.o
PROG = copter
CXX = gcc

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
%.o: src/%.c src/%.h src/defs.h
	$(CXX) $(CFLAGS) -c -s $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm $(PROG) *.o
