CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)
#	$(CC) -shared -o $(OBJECTS) $@
#	$(CC) -shared $(OBJECTS) -o $@
build:
	@mkdir -p build
	@mkdir -p bin


$(TESTS): $(TARGET) $(SO_TARGET) $(TEST_SRC)
	@echo building TESTS, TEST_SRC=:$(TEST_SRC)
	@echo TESTS=$(TESTS)
	@for x in $(TESTS); do\
		echo x=$$x;\
		$(CC) $(CFLAGS) $$x.c $(TARGET) -o $$x;\
	done

.PHONY: tests 
tests: $(TESTS)
	@echo TARGET=$(TARGET)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
