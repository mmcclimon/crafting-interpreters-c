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

-include $(DEPS)
