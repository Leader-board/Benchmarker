import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.concurrent.Semaphore;

public class bench_MT {
    static double[] avg_stagetime = new double[5];
    static double fin_score;
    static FastReader keyboard = new FastReader();
    static int NUMBER_OF_THREADS = 16; // number of threads
    static Semaphore mutex = new Semaphore(1);
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new
                    InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

    public static void selection() {
        int choose;
        System.out.println("Type 1 to start benchmarking");
        choose = keyboard.nextInt();
        while (choose != 1 && choose != 0) {
            System.out.println("Type 1 to start benchmarking");
            choose = keyboard.nextInt();
        }
        if (choose == 0)
            System.exit(0);
        // start benchmarking routine
       System.out.println("Enter number of threads to run program with");
       NUMBER_OF_THREADS = keyboard.nextInt();
    }

    static void printresult(double stagetime[], double totalscore, int t_no) {
        // print internal thread number
        System.out.print("------------------------\n");
        if (t_no != 0)
            System.out.println("RESULTS FOR THREAD " + t_no);
        else
            System.out.println("OVERALL RESULTS");
        System.out.println("------------------------");
        for (int i = 1; i <= 5; i++) {
            System.out.print("Average time taken for stage " + i + " is " + stagetime[i - 1] + " seconds and average score is ");
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
            System.out.println(1000 * r / stagetime[i - 1]);
        }
        if (t_no == 0)
            System.out.println("Final score: " + totalscore + " points!");
        else {
            // sub-thread score
            System.out.println("Thread " + t_no + " score: " + totalscore + " points!");
        }
    }

    static class progcore extends Thread {
        int thread_no;
        public progcore(int tr_no)
        {
            thread_no = tr_no;
        }
        public void run() {
            try {
                mainbase();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        public void mainbase() throws InterruptedException {
            long count;
            double[] timetake = new double[5];
            double[] stagetime = new double[5];
            double totalscore = 0;
            double[] score = new double[5];
            double c;
            double a, b, powcheck, k = 0, d, x, y; // x and y are the squares of a and b.
            int percentage = 0;// declaring variable to update percentage
            // D will represent C for greatest pythagorean triplet purposes.
            // k is the number which the user will enter. This value limits the value of a and b through which the program can search.
            for (int q = 1; q <= 5; q++) {
                for (int p = 1; p <= 5; p++) {
                    double begin = System.nanoTime();
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
                    while (b <= k) {
                        while (a <= k) {
                            x = a * a;
                            y = b * b;
                            c = x + y;
                            powcheck = b;    // b as starting point. Meant to speed up execution
                            while (powcheck <= Math.ceil(1.42 * k)) // Max value of c with relation to a and b is c = root2 of a,b
                            {
                                if (c == Math.pow(powcheck, 2)) // line that made the most difference on gcc
                                {
                                    if (c >= d)
                                        d = c;
                                    ++count;
                                    powcheck = 2 * k + 1;
                                } else
                                    ++powcheck;
                            }
                            ++a;
                        }
                        a = 1;
                        ++b;
                    }
                    double end = System.nanoTime();
                    double elapsed_secs = (end - begin) / 1000000000;
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
                    mutex.acquire();
                    System.out.println(p * 4 + (q - 1) * 20 + " % complete!");
                    System.out.println("Time taken for that stage:- " + timetake[p - 1]);
                    System.out.println("Score obtained for that stage:- " + score[p - 1] * 5);
                    mutex.release();
                }
            }
            mutex.acquire();
            for (int t = 0; t < 5; t++) {
                avg_stagetime[t] = avg_stagetime[t] + stagetime[t] / NUMBER_OF_THREADS;
            }
            fin_score = fin_score + totalscore / NUMBER_OF_THREADS;
            printresult(stagetime, totalscore, thread_no);
            mutex.release();
        }

    }

    public static void main(String[] args) throws InterruptedException {
        selection();
        progcore[] tr = new progcore[NUMBER_OF_THREADS];
        for (int i= 0; i < tr.length; i++)
            tr[i] = new progcore(i);
        double begin = System.nanoTime();
        for (progcore t : tr) {
            t.start();
        }
        for (progcore t : tr) {
            t.join();
        }
        double end = System.nanoTime();
        printresult(avg_stagetime, fin_score, 0);
        System.out.println ("Total time taken to run benchmark in seconds: " + (end - begin) / 1000000000);
    }
}
