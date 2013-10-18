DEBUG=yes
ifeq ($(DEBUG), yes)
    CFLAGS=-lcurl -ljson -g -std=c99
else
    CFLAGS=-lcurl -ljson -std=c99
endif
TESTFLAGS=-lcunit


all: bin/analyseur_requete.o bin/executeur_requete.o bin/interpreteur.o bin/resultat_utils.o bin/analyseur_json.o bin/afficheur.o bin/pile_int_utils.o bin/liste_str_utils.o
	rm -f bin/tests.o; gcc -o interpreteur bin/*.o $(CFLAGS)

test: bin/test/test_analyseur_requete.o bin/analyseur_requete.o bin/test/test_post_traitement.o bin/post_traitement.o bin/test/tests.o bin/test/test_analyseur_json.o bin/resultat_utils.o bin/analyseur_json.o bin/test/test_resultat_utils.o bin/test/mocks.o bin/test/test_afficheur.o bin/afficheur.o bin/pile_int_utils.o bin/liste_str_utils.o
	rm -f bin/interpreteur.o; gcc -o tests bin/*.o bin/test/*.o $(CFLAGS) $(TESTFLAGS)

clean:
	rm -f bin/*.o bin/test/*.o tests interpreteur

bin/test/%.o: test/%.c
	gcc -c $< -o $@ $(CFLAGS) $(TESTFLAGS)

bin/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS)

