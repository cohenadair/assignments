CC=gcc
#CC=clang
CFLAGS=-g -O0 -DLinux64=1 -std=c99 -pthread
OBJ_FILES = \
	cpu.o \
	process.o \
	linkedList.o \
	scheduler.o	\
	syscall.o \
	semaphore.o

TEST_OBJ_FILES = \
	mt_unitTest.o \
	mtUnitTestTests.o \
	baseTypeTests.o \
	testRunner.o \
	cpuTests.o \
	processTests.o \
	linkedListTests.o \
	schedulerTests.o \
	semaphoreTests.o

all: testRunner os

clean:
	rm *.o testRunner os

testRunner: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(TEST_OBJ_FILES) -o testRunner

os: $(OBJ_FILES) os.o
	$(CC) $(CFLAGS) $(OBJ_FILES) os.o -o os

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
