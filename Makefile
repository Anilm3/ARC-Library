SHELL = /bin/sh
CC    = gcc

SOURCE_DIR = src
TEST_DIR   = test

all:
	$(MAKE) -C $(SOURCE_DIR)
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) clean -C $(SOURCE_DIR)
	$(MAKE) clean -C $(TEST_DIR)