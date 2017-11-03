DIRS := $(filter-out Makefile makefile README module.mk, $(wildcard *))
DIRS_CLEAN := $(DIRS:=_clean)

.PHONY: all ${DIRS} clean

all: ${DIRS}

${DIRS}:
	@echo -n "Building $@ ... "
	@${MAKE} -C $@
	@echo "done"

clean: ${DIRS_CLEAN}

%_clean:
	@echo -n "Cleaning $* ... "
	@${MAKE} -C $* clean > /dev/null
	@echo "done"
