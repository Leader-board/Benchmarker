using System;
using System.Diagnostics;
namespace bench_csharp
{
    class Program
    {
        static double a, b, powcheck, k, d, x, y;// x and y are the squares of a and b.
        static int percentage = 0;// declaring variable to update percentage
        static double c;
        static double[] score = new double[5];
        static double totalscore = 0;
        static double[] stagetime = new double[5];
        public static void selection()
        {
            int choose;
            Console.WriteLine("Type 1 to start benchmarking");
            choose = int.Parse(Console.ReadLine());
            while (choose != 1 && choose != 0)
            {
                Console.WriteLine("Type 1 to start benchmarking");
                choose = int.Parse(Console.ReadLine());
            }
            if (choose == 0)
                Environment.Exit(0);
            // start benchmarking routine
        }
        public static void mainbase()
        {
            long count;
            double[] timetake = new double[5];
            // D will represent C for greatest pythagorean triplet purposes.
            // k is the number which the user will enter. This value limits the value of a and b through which the program can search.
            for (int q = 1; q <= 5; q++)
            {
                for (int p = 1; p <= 5; p++)
                {
                    Stopwatch stopWatch = new Stopwatch();
                    stopWatch.Start();
                    a = 1;
                    b = 1;
                    c = 1;
                    d = 1;
                    count = 0;// a and b are the base/height.
                    if (p == 1)
                        k = 100;
                    else if (p == 2)
                        k = 250;
                    else if (p == 3)
                        k = 500;
                    else if (p == 4)
                        k = 1000;
                    else if (p == 5)
                        k = 1500;
                    while (b <= k)
                    {
                        while (a <= k)
                        {
                            x = a * a;
                            y = b * b;
                            c = x + y;
                            powcheck = b;    // b as starting point. Meant to speed up execution
                            while (powcheck <= Math.Ceiling(1.42 * k)) // Max value of c with relation to a and b is c = root2 of a,b
                            {
                                if (c == powcheck * powcheck) // line that made the most difference on gcc
                                {
                                    if (c >= d)
                                        d = c;
                                    ++count;
                                    powcheck = 2 * k + 1;
                                }
                                else
                                    ++powcheck;
                            }
                            ++a;
                        }
                        a = 1;
                        ++b;
                    }
                    stopWatch.Stop();
                    double elapsed_secs = stopWatch.ElapsedMilliseconds / (double)1000;
                    timetake[p - 1] = elapsed_secs;
                    double r = 0;
                    if (p == 1)
                        r = 0.003;
                    if (p == 2)
                        r = 0.035;
                    if (p == 3)
                        r = 0.273;
                    if (p == 4)
                        r = 2.225;
                    if (p == 5)
                        r = 7.536;
                    score[p - 1] = 200 * (r / timetake[p - 1]);
                    totalscore = totalscore + (0.2 * (score[p - 1]));
                    stagetime[p - 1] = stagetime[p - 1] + 0.2 * elapsed_secs;
                    Console.WriteLine(p * 4 + (q - 1) * 20 + " % complete!");
                    Console.WriteLine("Time taken for that stage:- " + timetake[p - 1]);
                    Console.WriteLine("Score obtained for that stage:- " + score[p - 1] * 5);
                }
            }
        }
        static void Main(string[] args)
        {
            selection();
            mainbase();
            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Average time taken for stage " + (i + 1) + " is " + stagetime[i] + " seconds \n");
            }
            Console.WriteLine("Your system has scored a total of " + totalscore + " points!");
        }
    }
}
