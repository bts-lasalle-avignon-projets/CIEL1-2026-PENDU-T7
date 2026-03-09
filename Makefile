TARGET=pendu

DOSSIER_INCLUDE = ./src
DOSSIER_SRC = ./src
DOSSIER_TESTS = ./tests

SOURCES = $(wildcard $(DOSSIER_SRC)/*.cpp)
HEADERS := $(wildcard $(DOSSIER_INCLUDE)/*.h)
OBJS_SRC := $(patsubst $(DOSSIER_SRC)/%.cpp,$(DOSSIER_SRC)/%.o,$(wildcard $(DOSSIER_SRC)/*.cpp))
OBJS_TESTS := $(patsubst $(DOSSIER_TESTS)/%.cpp,$(DOSSIER_TESTS)/%.o,$(wildcard $(DOSSIER_TESTS)/*.cpp))

CXXFLAGS = -std=c++11 -Wall -I$(DOSSIER_INCLUDE)
LDFLAGS =
CLANG_FORMAT_STYLE = -style=file
CLANG_FORMAT_FILES = $(SOURCES) $(HEADERS)

CXX = g++ $(CXXFLAGS) -c
LD = g++ $(LDFLAGS)
RM = rm -f
CLANG_FORMAT = clang-format

all: format $(TARGET).out $(DOSSIER_TESTS)/testsUnitaires.out

# Pour le programme principal
$(TARGET).out: $(OBJS_SRC)
	$(LD) -o $@ $^

$(DOSSIER_SRC)/%.o: $(DOSSIER_SRC)/%.cpp $(HEADERS)
	$(CXX) $< -o $@

# Pour les tests unitaires
$(DOSSIER_TESTS)/testsUnitaires.out: $(OBJS_TESTS) $(filter-out $(DOSSIER_SRC)/$(TARGET).o,$(OBJS_SRC))
	$(LD) -o $@ $^

$(DOSSIER_TESTS)/%.o: $(DOSSIER_TESTS)/%.cpp $(HEADERS)
	$(CXX) $< -o $@

.PHONY: format clean cleanall

format:
	$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(CLANG_FORMAT_FILES)

clean:
	$(RM) $(DOSSIER_SRC)/*.o $(DOSSIER_SRC)/*.*~ $(DOSSIER_TESTS)/*.o $(DOSSIER_TESTS)/*.*~

cleanall:
	$(RM) $(TARGET).out $(DOSSIER_TESTS)/*.out $(DOSSIER_SRC)/*.o $(DOSSIER_SRC)/*.*~ $(DOSSIER_TESTS)/*.o $(DOSSIER_TESTS)/*.*~
