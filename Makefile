# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Directories
ASSETFILE_DIR = assetFile
COLOR_CATEGORY_DIR = color_category
COMMUNITY_CHEST_CARD_DIR = community_chest_card
MAINCPP_DIR = maincpp
MONEY_DIR = money
USERBOARD_DIR = userboard
VIRTUAL_MONOPOLY_BOARD_DIR = virtual_monopoly_board
EXECUTABLE_DIR = executable

# Source files
SRCS =  $(MAINCPP_DIR)/mainImplementation.cpp \
        $(MONEY_DIR)/money.cpp \
        $(USERBOARD_DIR)/MonopolyBoard.cpp \
        $(ASSETFILE_DIR)/asset.cpp \
        $(COLOR_CATEGORY_DIR)/color_category.cpp \
        $(COMMUNITY_CHEST_CARD_DIR)/CommunityChestCard.cpp \
        $(VIRTUAL_MONOPOLY_BOARD_DIR)/virtual_monopoly_board.cpp

# Header files
HEADERS = $(MONEY_DIR)/money.h \
          $(USERBOARD_DIR)/MonopolyBoard.h \
          $(ASSETFILE_DIR)/asset.h \
          $(COLOR_CATEGORY_DIR)/color_category.h \
          $(COMMUNITY_CHEST_CARD_DIR)/CommunityChestCard.h \
          $(VIRTUAL_MONOPOLY_BOARD_DIR)/virtual_monopoly_board.h

# Object files
OBJS = $(SRCS:$(MAINCPP_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(MONEY_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(USERBOARD_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(ASSETFILE_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(COLOR_CATEGORY_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(COMMUNITY_CHEST_CARD_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o) \
       $(SRCS:$(VIRTUAL_MONOPOLY_BOARD_DIR)/%.cpp=$(EXECUTABLE_DIR)/%.o)

# Target executable
TARGET = $(EXECUTABLE_DIR)/monopoly_game

# Default target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile source files to object files
$(EXECUTABLE_DIR)/%.o: $(MAINCPP_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(MONEY_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(USERBOARD_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(ASSETFILE_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(COLOR_CATEGORY_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(COMMUNITY_CHEST_CARD_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE_DIR)/%.o: $(VIRTUAL_MONOPOLY_BOARD_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(EXECUTABLE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(EXECUTABLE_DIR)

# Phony targets
.PHONY: all clean

