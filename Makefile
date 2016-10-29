# Compiler, Flags, Directory Name and Executable Name
CC= gcc
EXEC= megasena
ODIR= ./obj

# Source codes and objects
SRCS= main.c

OBJS= $(patsubst %.cpp,$(ODIR)/%.o,$(SRCS))

all: $(EXEC)

# Create paste for Objects
$(ODIR):
	@mkdir -p $@

# Concatenate objects with your new directory
$(OBJS): | $(ODIR)

# Compile and create objects
$(ODIR)/%.o: %.c
	$(CC) -c $< -o $@

# Generate the executables
$(EXEC): $(OBJS)
	$(CC) $^ -o $@
	rm -rf *.settings

# Delete objects, executables and new directories
clean:
	rm -rf ./$(EXEC)