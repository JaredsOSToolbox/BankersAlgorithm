OBJS_DIR = .objs
OBJS =  $(OBJS_DIR)/customer_t.o $(OBJS_DIR)/reader_t.o $(OBJS_DIR)/banker_t.o $(OBJS_DIR)/utils.o

COMPILER = clang++
CFLAGS = -Wall -g -lpthread -std=c++17
# TODO : I can forsee this causing issues when attempting to debug code
ECFLAGS = -Os -fdata-sections -ffunctions-sections -Wl,-dead_strip
OUTPUT = bankruptcy

all: $(OBJS) main.cpp
	$(COMPILER) $(CFLAGS) main.cpp $(OBJS) -o $(OUTPUT)
	./$(OUTPUT)

$(OBJS_DIR)/banker_t.o: src/banker_t.cpp includes/banker_t.hpp
	$(COMPILER) $(CFLAGS) -c src/banker_t.cpp -o $(OBJS_DIR)/banker_t.o

$(OBJS_DIR)/customer_t.o: src/customer_t.cpp includes/customer_t.hpp
	$(COMPILER) $(CFLAGS) -c src/customer_t.cpp -o $(OBJS_DIR)/customer_t.o

$(OBJS_DIR)/reader_t.o: src/reader_t.cpp includes/reader_t.hpp
	$(COMPILER) $(CFLAGS) -c src/reader_t.cpp -o $(OBJS_DIR)/reader_t.o

$(OBJS_DIR)/utils.o: src/utils.cpp includes/utils.hpp
	$(COMPILER) $(CFLAGS) -c src/utils.cpp -o $(OBJS_DIR)/utils.o

clean:
	rm -rf $(OBJS_DIR)/* $(OUTPUT)

