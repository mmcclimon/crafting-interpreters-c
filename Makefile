# mostly cribbed from somewhere online

TARGET := clox
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
DEPS := $(OBJS:.o=.d)

CFLAGS ?= -Wall -Werror --pedantic
CPPFLAGS ?= -MMD -MP

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

tags: $(wildcard *.c) $(wildcard *.h)
	ctags $^

-include $(DEPS)
