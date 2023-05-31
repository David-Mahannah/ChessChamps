CC = gcc
CFLAGS = -g -Wall

BUILD_LIBS = -lncurses
TEST_LIBS = -lcmocka 
SRC_DIR = src
TARGET = chess
TEST_TARGET = test

INSTALL_DIR = /usr/local/bin

#TEST_SRC = unit_tests/main.c unit_tests/test1.c unit_tests/test2.c unit_tests/test3.c unit_tests/test4.c unit_tests/test5.c unit_tests/test6.c

TEST_SRC = $(wildcard unit_tests/*.c)

REQUIRED_LIBRARIES := ncurses cmocka

CHECK_LIBRARIES := $(foreach lib,$(REQUIRED_LIBRARIES),$(shell pkg-config --exists $(lib) && echo 1 || echo 0))
MISSING_LIBRARIES := $(foreach lib,$(REQUIRED_LIBRARIES),$(shell if [ $$(pkg-config --exists $(lib) && echo 1 || echo 0) -eq 0 ]; then echo $(lib); fi))

ifeq ($(strip $(MISSING_LIBRARIES)),)
    # All required libraries are installed
    $(info All required libraries are installed.)
else
    $(error The following required libraries are not installed: $(MISSING_LIBRARIES))
endif


$(TARGET):
	@echo "*** BUILDING ***"
	$(CC) -o bin/$(TARGET) $(SRC_DIR)/main.c $(CFLAGS) $(SRC_DIR)/chess.c $(BUILD_LIBS)
	@echo "*** BUILD COMPLETE ***"

test:
	$(CC) -o bin/$(TEST_TARGET) $(CFLAGS) $(TEST_SRC) $(SRC_DIR)/chess.c $(TEST_LIBS)
	@./bin/test

install: $(TARGET)
	@echo "*** INSTALLING ***"
	cp bin/$(TARGET) $(INSTALL_DIR)
	@echo "*** INSTALL COMPLETE ***"

uninstall:
	@echo "*** UNINSTALLING ***"
	rm -f $(INSTALL_DIR)/$(TARGET)
	@echo "*** UNINSTALL COMPLETE ***"

clean:
	rm -f bin/$(TARGET)
	rm -f bin/$(TEST_TARGET)
