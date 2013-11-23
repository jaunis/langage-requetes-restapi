DEBUG=yes
ifeq ($(DEBUG), yes)
    CFLAGS=-lcurl -ljson -g -std=c99
else
    CFLAGS=-lcurl -ljson -std=c99
endif
TESTFLAGS=-lcunit

MAIN = bin/interpreteur.o

OBJECTS = bin/post_traitement.o
OBJECTS += bin/analyseur_syntaxique.o
OBJECTS += bin/executeur_requete.o
OBJECTS += bin/analyseur_json.o
OBJECTS += bin/afficheur.o
OBJECTS += bin/analyseur_lexical.o
OBJECTS += bin/utils/dict_utils.o
OBJECTS += bin/utils/pile_int_utils.o
OBJECTS += bin/utils/liste_str_utils.o
OBJECTS += bin/analyseur_semantique.o

TEST_OBJECTS = bin/test/test_analyseur_syntaxique.o
TEST_OBJECTS += bin/test/test_analyseur_lexical.o
TEST_OBJECTS += bin/test/test_post_traitement.o
TEST_OBJECTS += bin/test/tests.o
TEST_OBJECTS += bin/test/test_analyseur_json.o
TEST_OBJECTS += bin/test/test_dict_utils.o
TEST_OBJECTS += bin/test/mocks.o
TEST_OBJECTS += bin/test/test_afficheur.o
TEST_OBJECTS += bin/test/test_analyseur_semantique.o

all: $(OBJECTS) $(MAIN)
	rm -f bin/tests.o; gcc -o interpreteur $(OBJECTS) $(MAIN) $(CFLAGS)

test: $(OBJECTS) $(TEST_OBJECTS)
	rm -f $(MAIN); gcc -o tests $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS) $(TESTFLAGS)

clean:
	rm -f bin/**/*.o bin/*.o tests interpreteur

bin/test/%.o: test/%.c
	gcc -c $< -o $@ $(CFLAGS) $(TESTFLAGS)

bin/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS)

