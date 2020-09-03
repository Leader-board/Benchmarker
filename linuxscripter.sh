cd bash bench_c++_mt_nomutex_sleep
./linuxscript_idle.sh
mkdir "../scores/D4a_V4/nomutex_sleep/SCHED_IDLE, 30/run1"
mv *.txt "../scores/D4a_V4/nomutex_sleep/SCHED_IDLE, 30/run1"
sleep 120
./linuxscript_rr.sh
mkdir "../scores/D4a_V4/nomutex_sleep/SCHED_RR, 30/run1"
mv *.txt "../scores/D4a_V4/nomutex_sleep/SCHED_RR, 30/run1"
sleep 120
./linuxscript_rr.sh
mkdir "../scores/D4a_V4/nomutex_sleep/SCHED_RR, 30/run3"
mv *.txt "../scores/D4a_V4/nomutex_sleep/SCHED_RR, 30/run3"
cd ../bench_c++_mt_nomutex_forker
./linuxscript.sh
mkdir "../scores/D4a_V4/nomutex_fork/linux/run2"
mv *.txt "../scores/D4a_V4/nomutex_fork/linux/run2"
sleep 120
./linuxscript.sh
mkdir "../scores/D4a_V4/nomutex_fork/linux/run3"
mv *.txt "../scores/D4a_V4/nomutex_fork/linux/run3"
sleep 120
cd ../bench_c++_mt_nomutex
./nomutexscript.sh
mkdir "../scores/D4a_V4/nomutex/linux/run2"
mv *.txt "../scores/D4a_V4/nomutex/linux/run2"
./nomutexscript.sh
mkdir "../scores/D4a_V4/nomutex/linux/run3"
mv *.txt "../scores/D4a_V4/nomutex/linux/run3"
cd ../bench_c++_mt_v2
./ver2script.sh
mkdir "../scores/D4a_V4/low_ctxsw/linux/run2"
mv *.txt "../scores/D4a_V4/low_ctxsw/linux/run2"
./ver2script.sh
mkdir "../scores/D4a_V4/low_ctxsw/linux/run3"
mv *.txt "../scores/D4a_V4/low_ctxsw/linux/run3"
cd ../bench_c++_multithreaded
./scripter.sh
mkdir "../scores/D4a_V4/standard/linux/run2"
mv *.txt "../scores/D4a_V4/standard/linux/run2"
./scripter.sh
mkdir "../scores/D4a_V4/standard/linux/run3"
mv *.txt "../scores/D4a_V4/standard/linux/run3"
cd ../