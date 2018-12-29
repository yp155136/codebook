for ((i=0; i<100;i++))
do
    ./gen > input
    ./ac < input > out_ac
    ./wa < input > out_wa
    diff out_ac out_wa || break
done
