NOTE: If you're seeing this, I'm 180029456.

# INTRODUCTION

This is a simple benchmark program which is designed to compare CPU performance between different CPUs. This is single-threaded, please see the MT version for the multi-threaded version.
This is a linear-scored test - the baseline is 1000, and a score of 2000 indicates that the particular computer completed the test twice as fast as the reference computer.

# BENCHMARKING

This test runs 5 loops of finding triplets between 1 and n (n = 100, 200, 300, 500 and 1000). Note that the time complexity of the process is exponential - the time taken to complete the process when n = 200 is more than twice the time taken when n = 100.

Each run is weighed equally, and the time taken for each stage is mapped against a reference value while calculating the scores.

# NOTES

This test does not scale linearly while compiled on Visual Studio 2017. For instance, a i5-6300U (2.9 - 3 GHz) scores only 40% more than a Core2Duo T7200 (2 GHz), despite Geekbench reporing a nearly three-fold increase. It appears to scale purely with CPU clock speed irrespective of the architecture.
The highest ever recorded score was on an i7-7700K (4.5 GHz), where it scored about 2100 points.

However, this is not the case on Visual Studio 2008, where it scales linearly (260 and 83 points respectively).
 
This program can also be recompiled on Mac/Linux with some changes. I tested this program on a Mac on both Windows and macOS(ReSharper and XCode on the Mac), and the scores were mostly comparable, with a very slight edge for macOS.

# SCORE REFERENCES
(Compiled on Visual Studio 2017, Windows 10 on Release config. Scores may vary based on compiler configurations)
## Between different computers

*Where applicable, the turbo (not base) clockspeed (s) is (are) given, as a computer can be expected to use its turbo clockspeed. All computers (except the RM) were tested on Windows 10.*

|Device| Processor | Clockspeed (GHz)| Core/Thread count| Benchmarker score |
|--|--|--|--|--
|RM Education |Intel Atom  |1.8|2/4|122.3
|Acer Iconia W3-810  |Intel Atom Z2760  |1.8|2/4|136.7
|Surface Pro 4 | Core i5-6300U |2.9 - 3|2/4|1407.4
|MacBook Air 2013  |Core i5-4250U  |2.3 - 2.6|2/4|1169.7
|Dell Inspiron 6400 **(reference)**|Core2 Duo T7200|2|2/2|1050
|School computer 1|Core i7-6700|3.7-4|4/8|2013
|University computer 1|Core i5-6500|3.3-3.6|4/4|1744.8

## Between different compilers
The code between each compiler was kept as similar as possible; the only changes (if any) were solely to keep the compiler happy.
### PC 1: Dell Inspiron 6400 
| (Stage)  | VS 2017 (Release) |VS2017 (Debug)|VS2010 (Release)|VS2008 (Release)|VS2008 (Debug)|VS6|Turbo C++ (v4.0)
|--|--|--|--|--|--|--|--|
| 1 | 0.003 |0.07|0.028 |0.028 |0.145|0.192|0.18
|2|0.035|1.1|0.434|0.434|2.4|3.064|2.91
|3|0.285|8.8|3.45|3.546|18.3|24.188|23.5
|4|2.233|70.622|28|29|143.5|202.193|185.6
|5|7.512|236.864|95.1|93.5|486.1|657|644.6
|**Points**|1050|33.4|83.3|83|16.27|12.3|12.46

The difference between the VS 2008/2010 compliers and the VS2017 one is truly staggering - with a massive difference of nearly 13 times. 
### PC 2: MacBook Air 2013
| (Stage) | VS 2017 (Release) |VS2008 (Release)|XCode (release)|CLion (Release)|CLion (Debug)|VS6
|--|--|--|--|--|--|--|
|1|0.0025|0.012|0.0021|0.00195|0.028|0.117
|2|0.03|0.189|0.028|0.028|0.47|1.9
|3|0.24|1.45|0.23|0.25|3.75|15.5
|4|1.9|11.6|1.84|1.91|29.52|123.1
|5|6.3|39.4|6.2|6.35|98.8|419.2
|**Points**|1169.7|202.4|1212|1214|80.2|19.4

The VS2008 score scales linearly with performance, but the others don't do so well - giving only a 15-20% improvement over the Dell - despite the massive differences in CPU.
The scores on the Mac have a slight edge over their Windows counterparts for some reason.

### PC 3: Acer tablet

|Stage|VS2017 (Release) |VS2008 (Release)|
|--|--|--|
|1  |0.0019|0.075
|2|0.268|1.11
|3|2.133|8.9
|4|17.04|70.2
|5|57.345|236.3
|**Points**|136.7|33.2

The VS2017 scores show a sharp drop this time - inconsistent - considering that Geekbench reports only a 50% decrease over the Dell Inspiron 6400. 
