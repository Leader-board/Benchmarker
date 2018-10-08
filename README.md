# Benchmarker

INTRODUCTION

This is a simple benchmark program which is designed to compare CPU performance between different CPUs. This is single-threaded, please see the MT version for the multi-threaded version.
This is a linear-scored test - the baseline is 1000, and a score of 2000 indicates that the particular computer completed the test twice as fast as the reference computer.

BENCHMARKING

This test runs 5 loops of finding triplets between 1 and n (n = 100, 200, 300, 500 and 1000). Note that the time complexity of the process is exponential - the time taken to complete the process when n = 200 is more than twice the time taken when n = 100.

Each run is weighed equally, and the time taken for each stage is mapped against a reference value while calculating the scores.

NOTES

This test does not scale linearly while compiled on Visual Studio 2017. For instance, a i5-6300U (2.9 - 3 GHz) scores only 40% more than a Core2Duo T7200 (2 GHz), despite Geekbench reporing a nearly three-fold increase. It appears to scale purely with CPU clock speed irrespective of the architecture.
The highest ever recorded score was on an i7-7700K (4.5 GHz), where it scored about 2100 points.

However, this is not the case on Visual Studio 2008, where it scales linearly (260 and 83 points respectively).

