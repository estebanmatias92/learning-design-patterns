# Thin wrapper over CMake. All real build settings live in CMakeLists.txt.
# Bare 'make' shows help (the first target is the default);
# use 'make build' / 'make all' to compile.
BUILD_DIR ?= build
BUILD_TYPE ?= Release

.PHONY: help all configure build run test format format-check clean

help:
	@echo "Targets:"
	@echo "  make build               Configure + build (BUILD_DIR=$(BUILD_DIR))"
	@echo "  make run EXAMPLE=<name>  Build + run build/examples/<name> (basic_shapes|banking|document)"
	@echo "  make test                Configure + build + ctest"
	@echo "  make format              clang-format -i on src/ + examples/"
	@echo "  make format-check        Fail if clang-format would change files"
	@echo "  make clean               Remove $(BUILD_DIR)/"
	@echo ""
	@echo "Options:"
	@echo "  BUILD_DIR=<dir>"
	@echo "  BUILD_TYPE=<Release|Debug>"
	@echo "  EXAMPLE=<name>"

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	cmake --build $(BUILD_DIR)

run: build
ifndef EXAMPLE
	$(error Set EXAMPLE=<name>, e.g. 'make run EXAMPLE=basic_shapes')
endif
	@echo ""
	@echo "--- run: $(EXAMPLE) ---"
	@./$(BUILD_DIR)/examples/$(EXAMPLE)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

format:
	clang-format -i src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp examples/*/main.cpp 2>/dev/null || clang-format -i examples/*/main.cpp

format-check:
	clang-format --dry-run --Werror src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp examples/*/main.cpp 2>/dev/null || clang-format --dry-run --Werror examples/*/main.cpp

clean:
	rm -rf $(BUILD_DIR)
