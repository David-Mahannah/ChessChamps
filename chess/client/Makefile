CC = gcc
CFLAGS = -g -Wall

BUILD_LIBS = -lncurses
TEST_LIBS = -lcmocka 
SRC_DIR = src
TARGET = chess
TEST_TARGET = test

INSTALL_DIR = /usr/local/bin


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
	$(CC) -o bin/$(TARGET) $(SRC_DIR)/main.c $(SRC_DIR)/chess.c $(BUILD_LIBS)
	@echo "*** BUILD COMPLETE ***"

test:
	$(CC) -o bin/$(TEST_TARGET) unit_tests/main.c $(SRC_DIR)/chess.c $(TEST_LIBS)
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
