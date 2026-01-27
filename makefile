# Variables
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g -Werror
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))
LIB = $(wildcard build/src/*.o)
TEST_SRCS = $(wildcard test/*.cpp)
TEST_OBJS = $(patsubst %.cpp,build/%.o,$(TEST_SRCS))
TEST_EXEC = $(patsubst test/%.cpp,%,$(TEST_SRCS))

.SECONDARY:

# Règle par défaut
all: $(OBJS) lib/libgraweditor.a bin

# Règle de compilation
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour générer les fichiers objets
build/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour générer les exécutables de test 
%: build/test/%.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour générer une blibliothèque statiqu
lib/libgraweditor.a: $(OBJS) $(TEST_OBJS)
	ar rcs $@ $^

# Règle pour génrer les executables
bin: $(TEST_OBJS)
	@for file in $^ ; do \
		testname=`basename $$file .o` ; \
		$(CC) $$file lib/libgraweditor.a -o $$testname.exe ; \
		echo "Compilation de $$testname.exe" ; \
	done

# Règle pour nettoyer les fichiers objets et l'exécutable et les fichiers svg
mrproper:
	rm -rf build $(EXEC) out/svg/*.svg out/TikZ/*.tex $(TEST_EXEC) log/*.txt out/*.ppm out/*.pam lib/*.a *.exe

launchclean:
	rm *.exe

libclean:
	rm lib/*.a

# Règle pour nettoyer les fichiers objets
objectclean:
	rm -rf build

# Règle pour nettoyer l'exécutable
execclean :
	rm $(EXEC)

# Règle pour nettoyer les fichiers svg
svgclean :
	rm -rf out/svg/*.svg

# Règle pour nettoyer les fichiers TikZ
tikzclean :
	rm -rf out/TikZ/*.tex

# Règle pour nettoyer les fichiers ppm
ppmclean :
	rm -rf out/*.ppm

# Règle pour nettoyer les fichiers pam
pamclean :
	rm -rf out/*.pam

# Règle pour nettoyer les fichiers out
outclean :
	rm -rf out/svg/*.svg out/TikZ/*.t out/*.ppm out/*.pam

# Règle pour nettoyer les fichiers log
logclean :
	rm -f log/*.txt
    
# Règle pour lancer le programme
run:
	./$(EXEC)

# Règle pour lancer le programme avec valgrind
valgrind:
	valgrind ./$(EXEC)

# Règle pour lancer le programme avec valgrind et générer un fichier de log
valgrindlog:
	valgrind --log-file="log/valgrind.log" ./$(EXEC)

# Règle pour lancer le programme et vérifier les fuites mémoires
fuite:
	valgrind --leak-check=full ./$(EXEC)

# Règle pour lancer le programme et vérifier les valeurs non initialisées
valueNoinitialized:
	valgrind --track-origins=yes ./$(EXEC)
