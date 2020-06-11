@echo off
FOR /L %%A IN (1,1,%1) DO (
  start /b .\bench_c++_mt_nomutex_sleep.exe 1 %2 %3
)
@echo on