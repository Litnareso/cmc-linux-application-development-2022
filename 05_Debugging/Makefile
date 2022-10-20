TRASH = *.o *~ o.* *.so *.a *.log
GENERATES = range
CFLAGS=-O0 -g

all: range

test: range
	gdb --batch --quiet -x test1.gdb --args ./range 1 12
	grep -Po "(?<=@@@\{).*(?=\})" test1.log | sed 's/,//g' > out_1.log
	cmp out_1.log ans_1.txt

	gdb --batch --quiet -x test2.gdb --args ./range -100 100 3
	grep -Po "(?<=@@@\{).*(?=\})" test2.log | sed 's/,//g' > out_2.log
	cmp out_2.log ans_2.txt

clean:
	rm -f $(TRASH) $(GENERATES)
