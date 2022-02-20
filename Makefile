CC ?= gcc
SRCPATH=src/
INCLUDEPATH=include/
STD=-std=c99
WARNFLAGS=-Wall -Wextra -Werror
WRKDIR=build/
LIBPATH := ${WRKDIR}lib/
WRKINCLUDE := ${WRKDIR}include/
OBJPATH := ${WRKDIR}obj/

all: prepare mtb_str.so mtb_file.so

%.o: $(SRCPATH)%.c ${INCLUDEPATH}%.h
	cp $(filter %.h, $?) ${WRKINCLUDE}
	$(CC) -c -fpic ${WARNFLAGS} $< -I${INCLUDEPATH} -o ${OBJPATH}$@ ${STD}

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

uninstall:
	rm -f /usr/lib/libmtb_str.so
	rm -f /usr/lib/libmtb_file.so
	rm -f /usr/include/mtb_str.h
	rm -f /usr/include/mtb_file.h

# TEST STUFF
# Should be only used for dev purposes, and only the 'test' target should be used
TESTEXE=test
TESTPATH=tests/

test: test/compile test/run test/clear

test/compile:
	@${CC} -o ${TESTEXE} ${TESTPATH}*.c -I${TESTPATH}*.h -I${INCLUDEPATH} ${SRCPATH}*.c -g

test/run:
	@valgrind --error-exitcode=1 --leak-check=full -q ./${TESTEXE}

test/clear:
	@rm -f ./${TESTEXE}
