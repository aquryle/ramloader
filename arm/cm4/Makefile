# ----------------------------
# Makefile for Cortex-M33 RAM execution
# ----------------------------

# ツールチェイン
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
DUMP = arm-none-eabi-objdump
CFLAGS  = -mcpu=cortex-m33 -mthumb -O0 -ffreestanding -nostdlib -Wall
LDFLAGS = -Tlink_ram.ld -nostartfiles -Wl,-Map=$(BUILD_DIR)/prog.map

# ソースとビルドディレクトリ
SRC_DIR = src
BUILD_DIR = build
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 出力ファイル
TARGET  = $(BUILD_DIR)/prog.elf
BIN     = $(BUILD_DIR)/prog.bin

# デフォルトターゲット
all: $(BIN)

# オブジェクトファイルのビルド
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ELF のリンク
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	$(SIZE) $@
# 	$(DUMP) -h $@

# raw binary の生成
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# build ディレクトリの作成
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# クリーン
clean:
	rm -rf $(BUILD_DIR)
