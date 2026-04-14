# Project Settings
TARGET_NAME = sugar
SRC = main.cpp
BUILD_DIR = build

# Added -mstackrealign here for AVX safety
COMMON_FLAGS = -O2 -march=x86-64 -ffast-math -mstackrealign

# Linux Settings
L_CXX = g++
L_LDFLAGS = -static-libgcc -static-libstdc++ \
            -Wl,-Bstatic -lraylib -Wl,-Bdynamic \
            -lGL -lSDL2 -lm -lpthread -ldl -lrt -lX11
L_OUT = $(BUILD_DIR)/$(TARGET_NAME)_linux

# Windows Settings
W_CXX = x86_64-w64-mingw32-g++
W_LDFLAGS = -L. -I. -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -lws2_32 \
            -static -static-libgcc -static-libstdc++ \
            -mwindows -s
W_OUT = $(BUILD_DIR)/$(TARGET_NAME)_win.exe

.PHONY: all clean export

all: export

export: clean
	@mkdir -p $(BUILD_DIR)
	@echo "--- Compiling Linux Binary ---"
	$(L_CXX) $(SRC) $(COMMON_FLAGS) -o $(L_OUT) $(L_LDFLAGS)
	@echo "--- Compiling Windows Binary (Static) ---"
	# Removed -flto for stability during alignment fix
	$(W_CXX) $(SRC) $(COMMON_FLAGS) -o $(W_OUT) $(W_LDFLAGS)
	@echo "--- Done! Check the /$(BUILD_DIR) folder ---"
	@ls -lh $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory."