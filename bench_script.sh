# java
cd bench_java/src
javac bench_MT.java
echo -e "1\n1" | java bench_MT > javaT1.txt
echo -e "1\n2" | java bench_MT > javaT2.txt
echo -e "1\n4" | java bench_MT > javaT4.txt
echo -e "1\n8" | java bench_MT > javaT8.txt
echo -e "1\n16" | java bench_MT > javaT16.txt
echo -e "1\n32" | java bench_MT > javaT32.txt
echo -e "1\n64" | java bench_MT > javaT64.txt
cd ../../
# c++
cd bench_c++_multithreaded
g++ bench_c++_multithreaded.cpp -O3 -lpthread
echo -e "1\n1" | ./a.out > c++T1.txt
echo -e "1\n2" | ./a.out > c++T2.txt
echo -e "1\n4" | ./a.out > c++T4.txt
echo -e "1\n8" | ./a.out > c++T8.txt
echo -e "1\n16" | ./a.out > c++T16.txt
echo -e "1\n32" | ./a.out > c++T32.txt
# mono c#
cd ../bench_csharp_multithreaded
csc Program.cs
echo -e "1\n1" | mono Program.exe > monoT1.txt
echo -e "1\n2" | mono Program.exe > monoT2.txt
echo -e "1\n4" | mono Program.exe > monoT4.txt
echo -e "1\n8" | mono Program.exe > monoT8.txt
echo -e "1\n16" | mono Program.exe > monoT16.txt
echo -e "1\n32" | mono Program.exe > monoT32.txt
# netcore c#
cd ../bench_csharp_netcore_multithreaded
echo -e "1\n1" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT1.txt
echo -e "1\n2" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT2.txt
echo -e "1\n4" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT4.txt
echo -e "1\n8" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT8.txt
echo -e "1\n16" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT16.txt
echo -e "1\n32" | dotnet run --project bench_csharp_netcore_multithreaded.csproj > netcoreT32.txt
cd ../bench_python_multithreaded
# pypy
echo -e "1\n1" | pypy3 bench_python_multithreaded.py > pypyT1.txt
echo -e "1\n2" | pypy3 bench_python_multithreaded.py > pypyT2.txt
echo -e "1\n4" | pypy3 bench_python_multithreaded.py > pypyT4.txt
echo -e "1\n8" | pypy3 bench_python_multithreaded.py > pypyT8.txt
echo -e "1\n16" | pypy3 bench_python_multithreaded.py > pypyT16.txt
echo -e "1\n32" | pypy3 bench_python_multithreaded.py > pypyT32.txt
# python
echo -e "1\n1" | python3 bench_python_multithreaded.py > pythonT1.txt
echo -e "1\n2" | python3 bench_python_multithreaded.py > pythonT2.txt
echo -e "1\n4" | python3 bench_python_multithreaded.py > pythonT4.txt
cd ../