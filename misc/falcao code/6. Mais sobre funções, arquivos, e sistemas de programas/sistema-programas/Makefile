OBJ=./obj
LIB=./lib
INCLUDE=./include
SRC=./src
BIN=.
FLAGS=  -O3 -Wall -Wno-unused-result -fPIC -std=gnu99 -pedantic

libmc202: $(LIB)/libmc202.a
	echo "libmc202.a construída..."

$(LIB)/libmc202.a: \
$(OBJ)/cadeias.o \
$(OBJ)/banda.o \
$(OBJ)/imagem.o \
$(OBJ)/circulos.o \

	ar csr $(LIB)/libmc202.a \
$(OBJ)/cadeias.o \
$(OBJ)/banda.o \
$(OBJ)/imagem.o \
$(OBJ)/circulos.o \

$(OBJ)/cadeias.o: $(SRC)/cadeias.c
	gcc $(FLAGS) -c $(SRC)/cadeias.c -I$(INCLUDE) \
	-o $(OBJ)/cadeias.o 

$(OBJ)/banda.o: $(SRC)/banda.c
	gcc $(FLAGS) -c $(SRC)/banda.c -I$(INCLUDE) \
	-o $(OBJ)/banda.o 

$(OBJ)/circulos.o: $(SRC)/circulos.c
	gcc $(FLAGS) -c $(SRC)/circulos.c -I$(INCLUDE) \
	-o $(OBJ)/circulos.o 

$(OBJ)/imagem.o: $(SRC)/imagem.c
	gcc $(FLAGS) -c $(SRC)/imagem.c -I$(INCLUDE) \
	-o $(OBJ)/imagem.o 

$@.c: libmc202 $@.c 
	make
	gcc $(FLAGS) $@.c -I$(INCLUDE) -o $(BIN)/$@ $(FLAGS) -L$(LIB) -lmc202 -lm; \

clean: 
	rm $(LIB)/lib*.a; rm $(OBJ)/*.o; rm $(BIN)/testa_imagem;





