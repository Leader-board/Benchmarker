g++ bench_c++_mt_nomutex.cpp -O3 -lpthread
echo -e "1\n1" | ./a.out > c++T1.txt
echo -e "1\n2" | ./a.out > c++T2.txt
echo -e "1\n4" | ./a.out > c++T4.txt
echo -e "1\n8" | ./a.out > c++T8.txt
echo -e "1\n16" | ./a.out > c++T16.txt
echo -e "1\n32" | ./a.out > c++T32.txt
echo -e "1\n50" | ./a.out > c++T50.txt
echo -e "1\n100" | ./a.out > c++T100.txt
echo -e "1\n200" | ./a.out > c++T200.txt
echo -e "1\n400" | ./a.out > c++T400.txt
echo -e "1\n800" | ./a.out > c++T800.txt
echo -e "1\n1600" | ./a.out > c++T1600.txt
echo -e "1\n3200" | ./a.out > c++T3200.txt