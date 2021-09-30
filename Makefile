SRC = wordfreak.c bst.h bst.h
OBJ = wordfreak.o bst.o
PROG = wordfreak

$(PROG):$(OBJ)
	gcc $(OBJ) -o $(PROG)
$(OBJ):$(SRC)
