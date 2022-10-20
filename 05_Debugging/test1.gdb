set pagination off
set logging overwrite on
set logging redirect on
set logging debugredirect on
set logging file ./test1.log
set logging enabled off
set logging enabled on
b range_get if rng.cur % 5 == 0
command 1
        echo @@@
        output {rng->start, rng->stop, rng->step, rng->cur}
        cont
end

tty /dev/pts/5
run
quit
