g++ bench_c++_mt_nomutex.cpp -O3 -lpthread
echo -e "1\n1" | ./a.out > c++T1V.txt
echo -e "1\n2" | ./a.out > c++T2V.txt
echo -e "1\n4" | ./a.out > c++T4V.txt
echo -e "1\n8" | ./a.out > c++T8V.txt
echo -e "1\n16" | ./a.out > c++T16V.txt
echo -e "1\n32" | ./a.out > c++T32V.txt
echo -e "1\n50" | ./a.out > c++T50V.txt
echo -e "1\n100" | ./a.out > c++T100V.txt
echo -e "1\n200" | ./a.out > c++T200V.txt
echo -e "1\n400" | ./a.out > c++T400V.txt
echo -e "1\n800" | ./a.out > c++T800V.txt
echo -e "1\n1600" | ./a.out > c++T1600V.txt
echo -e "1\n3200" | ./a.out > c++T3200V.txt