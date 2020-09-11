cd bench_c++_mt_nomutex_quick
./linuxscript.sh
mkdir "../scores/D4a_V4/nomutex_quick/linux/run1"
mv *.txt "../scores/D4a_V4/nomutex_quick/linux/run1"
sleep 120
./linuxscript.sh
mkdir "../scores/D4a_V4/nomutex_quick/linux/run2"
mv *.txt "../scores/D4a_V4/nomutex_quick/linux/run2"
sleep 120