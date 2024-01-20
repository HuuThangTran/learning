CC= gcc
SOURCE=Lex.c List.c
OBJ=Lex.c List.c
HEADER=List.h
password_checker: ${OBJ} ${HEADER}
	$(CC) $(OBJ) -o List
%.o: %.c $(HEADER)
	$(CC) $< -c
clean:
	rm -rf Lex
	rm -rf *.o