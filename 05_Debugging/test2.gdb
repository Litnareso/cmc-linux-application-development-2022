set pagination off
set logging overwrite
set logging redirect
set logging file ./test2.log
set logging enabled off
set logging enabled on
set $range_get_Counter = 0
b range_get if $range_get_Counter <= 35 - 28
command 1
        echo @@@
        output {rng->start, rng->stop, rng->step, rng->cur}
        set $range_get_Counter = $range_get_Counter + 1
        cont
end
ignore 1 27

tty /dev/pts/5
run
quit
