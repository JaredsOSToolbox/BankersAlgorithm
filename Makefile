OBJS_DIR = .objs
#OBJS =  $(OBJS_DIR)/customer_t.o $(OBJS_DIR)/reader_t.o $(OBJS_DIR)/banker_t.o 
#OBJS =  $(OBJS_DIR)/customer_t.o $(OBJS_DIR)/reader_t.o
OBJS =  $(OBJS_DIR)/reader_t.o

COMPILER = clang++
CFLAGS = -Wall -g -lpthread
OUTPUT = bankruptcy

all: $(OBJS) main.cpp
	$(COMPILER) $(CFLAGS) main.cpp $(OBJS) -o $(OUTPUT)
	./$(OUTPUT)

#$(OBJS_DIR)/banker_t.o: src/banker_t.cpp includes/banker_t.hpp
	#$(COMPILER) $(CFLAGS) -c src/banker_t.cpp -o $(OBJS_DIR)/banker_t.o

#$(OBJS_DIR)/customer_t.o: src/customer_t.cpp includes/customer_t.hpp
	#$(COMPILER) $(CFLAGS) -c src/customer_t.cpp -o $(OBJS_DIR)/customer_t.o

$(OBJS_DIR)/reader_t.o: src/reader_t.cpp includes/reader_t.hpp
	$(COMPILER) $(CFLAGS) -c src/reader_t.cpp -o $(OBJS_DIR)/reader_t.o

#$(OBJS_DIR)/extended_vector_t.o: includes/extended_vector_t.tcc includes/extended_vector_t.hpp
	#$(COMPILER) $(CFLAGS) -v -c includes/extended_vector_t.hpp -o $(OBJS_DIR)/extended_vector_t.o

clean:
	rm -rf $(OBJS_DIR)/* $(OUTPUT)

