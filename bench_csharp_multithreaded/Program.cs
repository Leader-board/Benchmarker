using System;
using System.Diagnostics;
using System.Threading;
namespace bench_csharp
{
    class Program
    {
        static double[] avg_stagetime = new double[5];
        static double fin_score;
        static int NUMBER_OF_THREADS = 4; // number of threads
        private static Mutex m = new Mutex();
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
            Console.WriteLine("Enter number of threads to run program with");
            NUMBER_OF_THREADS = int.Parse(Console.ReadLine());
        }
        static void printresult(double[] stagetime, double totalscore, int t_no)
        {
            // print internal thread number
            Console.WriteLine("------------------------\n");
            if (t_no != 0)
                Console.WriteLine("RESULTS FOR THREAD " + t_no);
            else
                Console.WriteLine("OVERALL RESULTS");
            Console.WriteLine("------------------------");
            for (int i = 1; i <= 5; i++)
            {
                Console.Write("Average time taken for stage " + i + " is " + stagetime[i - 1] + " seconds and average score is ");
                double r = 0;
                if (i == 1)
                    r = 0.003;
                if (i == 2)
                    r = 0.035;
                if (i == 3)
                    r = 0.273;
                if (i == 4)
                    r = 2.225;
                if (i == 5)
                    r = 7.536;
                Console.WriteLine(1000 * r / stagetime[i - 1]);
            }
            if (t_no == 0)
                Console.WriteLine("Final score: " + totalscore + " points!");
            else
            {
                // sub-thread score
                Console.WriteLine("Thread " + t_no + " score: " + totalscore + " points!");
            }
        }
        public static void mainbase(int thread_no)
        {
            int check = 2;
            double a, b, powcheck, k = 0, d, x, y;// x and y are the squares of a and b.
            int verify = 0;
            int percentage = 0;// declaring variable to update percentage
            double c;
            double[] score = new double[5];
            double totalscore = 0;
            double[] stagetime = new double[5];
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
                                if (c == Math.Pow(powcheck, 2)) // line that made the most difference on gcc
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
                    m.WaitOne();
                    Console.WriteLine(p * 4 + (q - 1) * 20 + " % complete! for thread " + thread_no);
                    Console.WriteLine("Time taken for that stage:- " + timetake[p - 1] + " for thread " + thread_no);
                    Console.WriteLine("Score obtained for that stage:- " + score[p - 1] * 5 + " for thread " + thread_no);
                    m.ReleaseMutex();
                }
            }
            m.WaitOne();
            for (int t = 0; t < 5; t++)
            {
                avg_stagetime[t] = avg_stagetime[t] + stagetime[t] / NUMBER_OF_THREADS;
            }
            fin_score = fin_score + totalscore / NUMBER_OF_THREADS;
            printresult(stagetime, totalscore, thread_no);
            m.ReleaseMutex();
        }
       
        static void Main(string[] args)
        {
            selection();
            Thread[] tr = new Thread[NUMBER_OF_THREADS];
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < tr.Length; i++)
            {
                int j = i + 1;
                tr[i] = new Thread(() => mainbase(j));
            }
            foreach (Thread t in tr)
            {
                t.Start();
            }
            foreach (Thread t in tr)
            {
                t.Join();
            }
            stopWatch.Stop();
            printresult(avg_stagetime, fin_score, 0);
            Console.WriteLine("Total time taken to run benchmark in seconds: " + stopWatch.ElapsedMilliseconds / (double)1000);
        }
    }
}
