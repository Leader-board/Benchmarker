@echo off
FOR /L %%A IN (1,1,%1) DO (
  start /b .\bench_c++_mt_nomutex_forker.exe 1 %2
)
@echo on