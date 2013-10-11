DEBUG=yes
ifeq ($(DEBUG), yes)
    CFLAGS=-lcurl -ljson -g -std=c99
else
    CFLAGS=-lcurl -ljson -std=c99
endif
TESTFLAGS=-lcunit


all: analyseur_requete.o executeur_requete.o interpreteur.o resultat_utils.o analyseur_json.o afficheur.o
	gcc -o interpreteur analyseur_requete.o executeur_requete.o interpreteur.o resultat_utils.o analyseur_json.o afficheur.o $(CFLAGS)

test: test_analyseur_requete.o analyseur_requete.o tests.o test_analyseur_json.o resultat_utils.o analyseur_json.o test_resultat_utils.o mocks.o test_afficheur.o afficheur.o
	gcc -o tests test_analyseur_json.o test_analyseur_requete.o analyseur_requete.o resultat_utils.o analyseur_json.o test_resultat_utils.o mocks.o test_afficheur.o afficheur.o tests.o $(CFLAGS) $(TESTFLAGS)

clean:
	rm *.o tests interpreteur

resultat_utils.o: src/resultat_utils.c
	gcc -c src/resultat_utils.c -o resultat_utils.o $(CFLAGS)

analyseur_json.o: src/analyseur_json.c
	gcc -c src/analyseur_json.c -o analyseur_json.o $(CFLAGS)

analyseur_requete.o: src/analyseur_requete.c
	gcc -o analyseur_requete.o -c src/analyseur_requete.c $(CFLAGS)

executeur_requete.o: src/executeur_requete.c
	gcc -o executeur_requete.o -c src/executeur_requete.c $(CFLAGS)

interpreteur.o: src/interpreteur.c
	gcc -o interpreteur.o -c src/interpreteur.c $(CFLAGS)

test_analyseur_requete.o: test/test_analyseur_requete.c
	gcc -o test_analyseur_requete.o -c test/test_analyseur_requete.c $(CFLAGS) $(TESTFLAGS)

test_analyseur_json.o: test/test_analyseur_json.c
	gcc -o test_analyseur_json.o -c test/test_analyseur_json.c $(CFLAGS) $(TESTFLAGS)

tests.o: test/tests.c
	gcc -o tests.o -c test/tests.c $(CFLAGS) $(TESTFLAGS)

test_resultat_utils.o: test/test_resultat_utils.c
	gcc -c test/test_resultat_utils.c -o test_resultat_utils.o $(CFLAGS) $(TESTFLAGS)

mocks.o: test/mocks.c
	gcc -c test/mocks.c -o mocks.o $(CFLAGS) $(TESTFLAGS)

test_afficheur.o: test/test_afficheur.c
	gcc -c test/test_afficheur.c -o test_afficheur.o $(CFLAGS) $(TESTFLAGS)

afficheur.o: src/afficheur.c
	gcc -c src/afficheur.c -o afficheur.o  $(CFLAGS)
