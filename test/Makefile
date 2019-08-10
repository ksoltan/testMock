# Makefile for Running Unit Tests

CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-return-type #-Werror
LDFLAGS  := -L/usr/lib -lstdc++ -lm

BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)
TARGET   := allTests

INCLUDE  := -I include/ 									\
						-I ../src/common/		\
						-I ../src/data_processor/		\
						-I ../src/instrument_adapter		\

SRC      := $(wildcard *.cpp)							\
						$(wildcard include/*.cpp)			\
						$(wildcard unit/data_processor/*.cpp)	\
						$(wildcard unit/instrument_adapter/*.cpp)	\
						$(wildcard ../src/common/*.cpp)		\
						$(wildcard ../src/data_processor/*.cpp)		\
						$(wildcard ../src/instrument_adapter/*.cpp)	\

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
