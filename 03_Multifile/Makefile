TRASH = *.o *~ o.* *.so *.a *.log
GENERATES = prog prog-a prog-so README
CFLAGS=-Werror -Wall -fPIC

all: README prog prog-a prog-so

liboutput_static.a: fun.o const.o
	ar -rcs liboutput_static.a const.o fun.o

liboutput.so: fun.o const.o
	cc $(CFLAGS) -shared fun.o const.o -o liboutput.so

prog: const.o fun.o prog.o
	cc $(CFLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. prog.o -loutput_static -o prog-a

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. prog.o -loutput -o prog-so

README: prog
	./$< 2> $@

test: prog prog-a prog-so
	./prog 1> prog_out_0.log 2> prog_err_0.log
	./prog-a 1> prog-a_out_0.log 2> prog-a_err_0.log
	LD_LIBRARY_PATH=`pwd` ./prog-so 1> prog-so_out_0.log 2> prog-so_err_0.log
	cmp prog_out_0.log prog-a_out_0.log
	cmp prog_out_0.log prog-so_out_0.log

	./prog 1 1> prog_out_1.log 2> prog_err_1.log
	./prog-a 1 1> prog-a_out_1.log 2> prog-a_err_1.log
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 1> prog-so_out_1.log 2> prog-so_err_1.log
	cmp prog_out_1.log prog-a_out_1.log
	cmp prog_out_1.log prog-so_out_1.log

	./prog 1 2 3 1> prog_out_3.log 2> prog_err_3.log
	./prog-a 1 2 3 1> prog-a_out_3.log 2> prog-a_err_3.log
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 1> prog-so_out_3.log 2> prog-so_err_3.log
	cmp prog_out_3.log prog-a_out_3.log
	cmp prog_out_3.log prog-so_out_3.log

fun.o: outlib.h

clean:
	rm -f $(TRASH) $(GENERATES)

distclean:      clean
	rm -rf $(GENERATES)
