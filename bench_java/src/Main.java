import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

// Java port of Benchmarker.

public class Main {
    static int check = 2;
    static double a, b, powcheck, k, d, x, y;// x and y are the squares of a and b.
    static int verify = 0;
    static int percentage = 0;// declaring variable to update percentage
    static double c;
    static double[] score = new double[5];
    static double totalscore = 0;
    static double[] stagetime = new double[5];
    static FastReader keyboard;

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
    }

    public static void mainbase() {
        long count;
        double timetake[] = new double[5];
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
                System.out.println(p * 4 + (q - 1) * 20 + " % complete!");
                System.out.println("Time taken for that stage:- " + timetake[p - 1]);
                System.out.println("Score obtained for that stage:- " + score[p - 1] * 5);
            }
        }
    }

    public static void main(String[] args) {
        // write your code here
        keyboard = new FastReader();
        selection();
        mainbase();
        for (int i = 0; i < 5; i++) {
            System.out.println("Average time taken for stage " + (i + 1) + " is " + stagetime[i] + " seconds \n");
        }
        System.out.println("Your system has scored a total of " + totalscore + " points!");
    }
}
