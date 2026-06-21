inverted_search.out : main.o create_DB.o update_DB.o save_DB.o search_DB.o display.o free_DB.o validation.o
	gcc -o inverted_search.out main.o create_DB.o update_DB.o save_DB.o search_DB.o display.o free_DB.o validation.o

main.o : main.c header.h
	gcc -c main.c -o main.o

create_DB.o : create_DB.c header.h
	gcc -c create_DB.c -o create_DB.o

update_DB.o : update_DB.c header.h
	gcc -c update_DB.c -o update_DB.o

save_DB.o : save_DB.c header.h
	gcc -c save_DB.c -o save_DB.o

search_DB.o : search_DB.c header.h
	gcc -c search_DB.c -o search_DB.o

display.o : display.c header.h
	gcc -c display.c -o display.o

free_DB.o : free_DB.c header.h
	gcc -c free_DB.c -o free_DB.o

validation.o : validation.c header.h
	gcc -c validation.c -o validation.o


clean:
	rm *.o *.out