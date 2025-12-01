CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
BUILD_DIR = build

DAY ?= 01

# Normalize to two digits
DAY_PADDED := $(shell printf "%02d" $(DAY))

SRC = src/day$(DAY_PADDED).cpp
TARGET = $(BUILD_DIR)/day$(DAY_PADDED)
INPUT = inputs/day$(DAY_PADDED).txt

.PHONY: all build run clean

all: build

build: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Built $@"

run: $(TARGET)
	@if [ -f $(INPUT) ]; then \
		echo "Running day $(DAY_PADDED) with input:"; \
		$(TARGET) < $(INPUT); \
	else \
		echo "No input file found at $(INPUT)"; \
		echo "Running without input:"; \
		$(TARGET); \
	fi

clean:
	rm -rf $(BUILD_DIR)

list:
	@echo "Available days:"
	@ls -1 src/day*.cpp 2>/dev/null | sed 's/src\/day\(.*\)\.cpp/  \1/' || echo "  (none yet)"
