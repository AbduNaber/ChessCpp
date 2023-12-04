CXX = g++
CXXFLAGS = -std=c++11 -I. # Added -Iheader to include the header directory

SRC_DIR = src
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TARGET = chess

.PHONY: all clean

all: compile run

compile: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^

run:
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
