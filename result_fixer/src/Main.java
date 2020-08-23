import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Main {
    static HashMap<String, Double> results = new HashMap<>();
    static ArrayList<String> core = new ArrayList<>();
    static FastReader fr;
    static int num_dir = 0;

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        String filename;

        public FastReader(String s) throws FileNotFoundException {
            filename = s;
            br = new BufferedReader(new
                    InputStreamReader(new FileInputStream(filename)));
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

        void close() throws IOException {
            br.close();
        }
    }

    public static void analyse() {
        double time_taken = 0;
        if (core.get(0).contains("Type 1 to start benchmarking.")) {
            // returned by benchmark
            String str = core.get(core.size() - 1);
            String split[] = str.split(" ");
            time_taken = Double.parseDouble(split[split.length - 1]);

        } else if (core.get(2).equals("")) {
            // windows
            String str = core.get(22);
            String split[] = str.replaceAll("\\s", "").split(":");
            time_taken = Double.parseDouble(split[split.length - 1]);

        } else {
            // if we get bash-released data, from Linux
            String str = core.get(core.size() - 3);
            String split[] = str.split("\t");
            String timer = split[split.length - 1];
            // handle this carefully
            String timesplit[] = timer.split("m");
            time_taken = time_taken + 60d * Double.parseDouble(timesplit[0]);
            String sec = new StringBuilder(timesplit[1]).deleteCharAt(timesplit[1].length() - 1).toString();
            time_taken = time_taken + Double.parseDouble(sec);

        }
        Path p = Paths.get(fr.filename);
        String filename = p.getFileName().toString();
        Double res = results.get(filename);
        if (res == null)
            res = 0d;
        res += time_taken;
        results.put(filename, res);
    }
    public static double round(double a)
    {
        // perform rounding
        return Math.round(a * 10000.0) / 10000.0;
    }
    public static void fileRunner(String filepath) throws IOException {
        results = new HashMap<>();
        File f1 = new File(filepath);
        num_dir = f1.list().length;
        for (int i = 1; i <= num_dir; i++) {
            core = new ArrayList<>();
            File f = new File(filepath + "\\run" + i); // is a directory
            String[] filenames = f.list();
            for (String s : filenames) {
                fr = new FastReader(filepath + "\\run" + i + "\\" + s);
                String str = "";
                while ((str = fr.nextLine()) != null) {
                    core.add(str);
                }
                fr.close();
                analyse();
            }
        }
        to_latex();
    }

    public static void to_latex() {
        // convert to LaTeX format
        System.out.print("\\begin{longtable}{");
        int n_rows = 2;
        for (int i = 0; i < n_rows; i++)
            System.out.print("|1");
        System.out.println("|}");
        System.out.println("\\endfirsthead\n" +
                "%\n" +
                "\\endhead\n" +
                "%");
        for (Map.Entry O:results.entrySet())
        {
            System.out.print(O.getKey());
            System.out.print(" & ");
            System.out.print(round((Double) O.getValue()));
            System.out.print(" & ");
            System.out.println("\\\\ \\hline");
        }
        System.out.println("\\end{longtable}");
    }

    public static void main(String[] args) throws IOException {
        // write your code here
        // args = parent folder that contains all run_X values
        // fr = new FastReader("C:\\Users\\vishn\\OneDrive\\Documents\\Visual Studio 2015&17\\Projects\\Benchmarker\\scores\\D4a_V4\\nomutex_sleep\\5000\\linux\\run1\\c++T1_100.txt");
        if (args.length != 0) {
            StringBuilder sb = new StringBuilder();
            for (String s : args)
                sb.append(s + " ");
            sb.deleteCharAt(sb.length() - 1);
            fileRunner(sb.toString());
        } else
            System.out.println("Insufficient arguments!");
        System.out.println("hello");
    }

}