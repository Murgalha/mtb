CC ?= gcc
SRCPATH=src
INCLUDEPATH=include
incl := -I${INCLUDEPATH}
out=mtb
libs=
std=-std=c99
warn=-Wall -Wextra -Werror
test=test
WRKDIR=build/
LIBPATH := ${WRKDIR}lib/
WRKINCLUDE := ${WRKDIR}include/
OBJPATH := ${WRKDIR}obj/

all: prepare mtb_str.so mtb_file.so

%.o: $(SRCPATH)/%.c ${INCLUDEPATH}/%.h
	cp $(filter %.h, $?) ${WRKINCLUDE}
	$(CC) -c -fpic $(warn) $< -Iinclude -o ${OBJPATH}$@

%.so: %.o
	$(CC) -shared -o ${LIBPATH}lib$@ ${OBJPATH}$<

install:
	cp ${LIBPATH}*.so /usr/lib/
	cp ${WRKINCLUDE}*.h /usr/include/

prepare:
	@if [ ! -d "${WRKDIR}" ]; then mkdir ${WRKDIR}; fi
	@if [ ! -d "${OBJPATH}" ]; then mkdir ${OBJPATH}; fi
	@if [ ! -d "${LIBPATH}" ]; then mkdir ${LIBPATH}; fi
	@if [ ! -d "${WRKINCLUDE}" ]; then mkdir ${WRKINCLUDE}; fi

clear:
	rm -rf ${WRKDIR}

mtb_str: prepare mtb_str.so
mtb_file: prepare mtb_file.so

# TEST STUFF
# Should be only used for dev purposes, and only the 'test' target should be used
test: test/compile test/run test/clear

test/compile:
	@$(CC) -o $(test) tests/*.c -Itests/*.h -Iinclude src/*.c -g

test/run:
	@valgrind --error-exitcode=1 --leak-check=full -q ./$(test)

test/clear:
	@rm -f ./$(test)
