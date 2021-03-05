.SILENT:
.PHONY: all clean

LIB_DIR=..

CFLAGS=-Wall -I$(LIB_DIR)

all: rt_test

OBJS=\
     ${LIB_DIR}/rt_sched.o \
     rt_test.o

rt_test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	${RM} $(OBJS) rt_test
