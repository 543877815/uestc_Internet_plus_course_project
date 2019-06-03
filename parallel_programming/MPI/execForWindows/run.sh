#!/usr/bin/env bash

loop_count=20
process_count=20
number_to_count=10000000
executables=(main3)

for executable in ${executables[@]}; do
    echo "running ${executable}"
    total_time=0
    for (( i = 1; i <= ${process_count}; i++ )); do
        for (( j = 0; j < ${loop_count}; ++j)); do
        str=`mpiexec -np ${i} ${executable}.exe ${number_to_count} 6000000`
        str_array=(${str})
        one_run_time=${str_array[${#str_array[@]}-1]}
        echo "running ${i}th test with time cost ${one_run_time}"
        # total_time=$(echo "$total_time + $one_run_time" | bc)
        done
    done
    # average_time=`echo "scale=6; $total_time / $loop_count" | bc | awk '{printf "%.6f", $0}'`
    echo "average run time in ${loop_count} test is ${average_time}"
done



