CC := gcc
CFLAGS := -Wall -Wextra -Iinclude
LDFLAGS := -lcurl

SRCDIR := src
OBJDIR := obj

MAIN := main.c
SOURCES := $(filter-out $(MAIN), $(wildcard $(SRCDIR)/*.c))
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE := scanner

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(OBJDIR)/$(MAIN:.c=.o)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(MAIN:.c=.o): $(MAIN)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
