# runs up to $1 times given in command line argument with k = $2 and sleeps for $3
for i in $(seq "$1")
do
 # gdb -ex=r --args ./a.out 1 $2 $3 & 
 ./a.out 1 $2 $3 $4 &
done
wait    