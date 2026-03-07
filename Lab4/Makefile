# OpenMP на macOS (M1/Apple Silicon): brew install libomp
# Путь к libomp через brew --prefix (работает на M1 и Intel)
LIBOMP_PREFIX := $(shell brew --prefix libomp 2>/dev/null)
ifeq ($(LIBOMP_PREFIX),)
  $(error Установите libomp: brew install libomp)
endif

CC = clang
OMP = -Xpreprocessor -fopenmp -I$(LIBOMP_PREFIX)/include -L$(LIBOMP_PREFIX)/lib -lomp

CFLAGS = -Wall $(OMP)

TARGETS = task2 task3.1 task3.2 task4 task5.1 task5.2

all: $(TARGETS)

task2:   task2.c
task3.1: task3.1.c
task3.2: task3.2.c
task4:   task4.c
task5.1: task5.1.c
task5.2: task5.2.c

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

run-task2:   task2
	./task2
run-task3.1: task3.1
	echo 4 | ./task3.1
run-task3.2: task3.2
	echo 4 | ./task3.2
run-task4:   task4
	echo 4 | ./task4
run-task5.1: task5.1
	echo 10 | ./task5.1
run-task5.2: task5.2
	echo 4 10 | ./task5.2

.PHONY: all clean run-task2 run-task3.1 run-task3.2 run-task4 run-task5.1 run-task5.2
