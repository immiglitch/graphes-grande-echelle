#Compilation générique avec makefile 

CC=gcc

CC = gcc

main: 		main.o matriceadj.o brin.o fifo.o heap.o triplets.o
	$(CC) main.o matriceadj.o brin.o heap.o fifo.o triplets.o -o main


#matriceadj:	matriceadj.o affichage.o fifo.o matriceadj.h fifo.h affichage.h
#		$(CC) matriceadj.o affichage.o fifo.o -o matriceadj
		
#listeadj:	listeadj.o affichage.o heap.o listeadj.h heap.h affichage.h
#		$(CC) listeadj.o affichage.o fifo.o -o listeadj

clean:
	@rm -f *.o
	@rm -f core
	@rm -f *~

