# Derleyici ayarları
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -static-libgcc -static-libstdc++

# Dosya yapısı
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/main.exe

# Kaynak dosyaları
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Varsayılan hedef
all: $(BIN_DIR) $(BUILD_DIR) $(TARGET)
	$(TARGET)

# Çalıştırılabilir dosya
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Nesne dosyaları
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Windows için klasör oluşturma
$(BIN_DIR):
	@if not exist "$(subst /,\,$(BIN_DIR))" mkdir "$(subst /,\,$(BIN_DIR))"

$(BUILD_DIR):
	@if not exist "$(subst /,\,$(BUILD_DIR))" mkdir "$(subst /,\,$(BUILD_DIR))"

# Temizleme
clean:
	@if exist "$(subst /,\,$(BUILD_DIR))" rmdir /s /q "$(subst /,\,$(BUILD_DIR))"
	@if exist "$(subst /,\,$(BIN_DIR))" rmdir /s /q "$(subst /,\,$(BIN_DIR))"

.PHONY: all clean