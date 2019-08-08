# Makefile for Running Unit Tests

CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra #-Werror
LDFLAGS  := -L/usr/lib -lstdc++ -lm

BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)
TARGET   := allTests

INCLUDE  := -I include/ 									\
 						-I ../include/							\

SRC      := $(wildcard *.cpp)							\
						$(wildcard unit/*.cpp)	\
						$(wildcard ../src/*.cpp)		\
						$(wildcard ../src/common/*.cpp)		\

# OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS := $(patsubst %.c,%.o,$(SRC))
all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(APP_DIR)
