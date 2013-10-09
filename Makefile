ifeq ($(DEBUG), yes)
    CFLAGS=-lcurl -ljson -g -std=c99
else
    CFLAGS=-lcurl -ljson -std=c99
endif
TESTFLAGS=-lcunit


all: analyseur_requete.o executeur_requete.o interpreteur.o dict_utils.o analyseur_json.o
	gcc -o interpreteur analyseur_requete.o executeur_requete.o interpreteur.o dict_utils.o analyseur_json.o $(CFLAGS)

test: test_analyseur_requete.o analyseur_requete.o tests.o test_analyseur_json.o dict_utils.o analyseur_json.o test_dict_utils.o
	gcc -o tests test_analyseur_json.o test_analyseur_requete.o analyseur_requete.o dict_utils.o analyseur_json.o test_dict_utils.o tests.o $(CFLAGS) $(TESTFLAGS)

clean:
	rm *.o tests interpreteur

dict_utils.o: src/dict_utils.c
	gcc -c src/dict_utils.c -o dict_utils.o $(CFLAGS)

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

test_dict_utils.o: test/test_dict_utils.c
	gcc -c test/test_dict_utils.c -o test_dict_utils.o