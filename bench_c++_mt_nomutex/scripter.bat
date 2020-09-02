(echo 1) > test.txt
(echo 1) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T1_100W.txt
(echo 1) > test.txt
(echo 2) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T2_100W.txt
(echo 1) > test.txt
(echo 4) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T4_100W.txt
(echo 1) > test.txt
(echo 8) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T8_100W.txt
(echo 1) > test.txt
(echo 16) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T16_100W.txt
(echo 1) > test.txt
(echo 32) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T32_100W.txt
(echo 1) > test.txt
(echo 50) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T50_100W.txt
(echo 1) > test.txt
(echo 100) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T100_100W.txt
(echo 1) > test.txt
(echo 200) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T200_100W.txt
(echo 1) > test.txt
(echo 400) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T400_100W.txt
(echo 1) > test.txt
(echo 800) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T800_100W.txt
(echo 1) > test.txt
(echo 1600) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T1600_100W.txt
(echo 1) > test.txt
(echo 3200) >> test.txt
bench_c++_mt_nomutex.exe < test.txt > c++T3200_100W.txt