DEBUG=yes
ifeq ($(DEBUG), yes)
    CFLAGS=-lcurl -ljson -g -std=c99
else
    CFLAGS=-lcurl -ljson -std=c99
endif
TESTFLAGS=-lcurl


all: analyseur_requete.o executeur_requete.o interpreteur.o
	gcc -o interpreteur analyseur_requete.o executeur_requete.o interpreteur.o $(CFLAGS)

analyseur_requete.o: src/analyseur_requete.c
	gcc -o analyseur_requete.o -c src/analyseur_requete.c $(CFLAGS)

executeur_requete.o: src/executeur_requete.c
	gcc -o executeur_requete.o -c src/executeur_requete.c $(CFLAGS)

interpreteur.o: src/interpreteur.c
	gcc -o interpreteur.o -c src/interpreteur.c $(CFLAGS)

test: test_analyseur_requete.o analyseur_requete.o
	gcc -o test test_analyseur_requete.o analyseur_requete.o $(CFLAGS) $(TESTFLAGS)

test_analyseur_requete.o: src/test_analyseur_requete.c
	gcc -o test_analyseur_requete.o -c test_analyseur_requete.c $(CFLAGS) $(TESTFLAGS)
