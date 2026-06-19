CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = main.c

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

TARGET = sequence_generator

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)