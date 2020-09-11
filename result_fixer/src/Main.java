import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Main {
    static TreeMap<String, Double> results;
    static String[] headers;
    static ArrayList<String> core = new ArrayList<>();
    static FileReader fr;
    static int num_dir = 0;
    static TreeMap<String, TreeMap<String, Double>> finaliser;
    static class FileReader {
        BufferedReader br;
        StringTokenizer st;
        String filename;

        public FileReader(String s) throws FileNotFoundException {
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

    public static void analyse(int num_runs){
        double time_taken = 0;
        if (core.get(0).contains("Type 1 to start benchmarking.")) {
            // returned by benchmark
            String str = core.get(core.size() - 1);
            String split[] = str.split(" ");
            time_taken = Double.parseDouble(split[split.length - 1]);

        }
        else if (core.get(1).length() < 2 && !core.get(2).contains("real")) {
            // windows
            String str = core.get(11);
            String split[] = str.replaceAll("\\s", "").split(":");
            time_taken = Double.parseDouble(split[split.length - 1]);
        }
        else {
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
        res += time_taken/num_runs; // as we'll be adding this by num_runs times
        results.put(filename, res);
    }

    public static double round(double a) {
        // perform rounding
        return Math.round(a * 10000.0) / 10000.0;
    }

    public static void fileRunner(String filepath) throws IOException {

        File f1 = new File(filepath);
        finaliser = new TreeMap<>();
        num_dir = f1.list().length;
        headers = f1.list();
        for (String adder: Objects.requireNonNull(f1.list())) {
            for (int i = 1; i <= num_dir; i++) {
                core = new ArrayList<>();
                File fp = new File(filepath + "\\" + adder);
                int num_runs = fp.list().length;
                // results
                results = new TreeMap<>((s, t1) -> {
                    // split
                    s = s.replaceAll("W", "").replaceAll("\\+\\+","").replaceAll("c","").replaceAll("C","").replaceAll("T","").replaceAll("\\.txt","");
                    t1 = t1.replaceAll("W", "").replaceAll("\\+\\+","").replaceAll("c","").replaceAll("C","").replaceAll("T","").replaceAll("\\.txt","");
                    String[] split1 = s.split("_");
                    String[] split2 = t1.split("_");
                    int n1 = Integer.parseInt(split1[0]);
                    int n2 = Integer.parseInt(split2[0]);
                    if (split1.length == 1) {
                        // no "T" involved, that is, we are not demarcating with 100/200 threads
                        return (n1 - n2);
                    } else {
                        // first split by "T"
                        int th1 = Integer.parseInt(split1[1]);
                        int th2 = Integer.parseInt(split2[1]);
                        return (th1 != th2) ? (th1 - th2) : (n1 - n2);
                    }
                });
                for (int j = 1; j <= num_runs; j++) {
                    File f = new File(filepath + "\\" + adder + "\\run" + j); // is a directory
                    String[] filenames = f.list();
                    assert filenames != null;
                    for (String s : filenames) {
                        core = new ArrayList<>();
                        fr = new FileReader(filepath + "\\" + adder + "\\run" + j + "\\" + s);
                        String str = "";
                        while ((str = fr.nextLine()) != null) {
                            core.add(str);
                        }
                        fr.close();
                        analyse(num_runs);
                    }
                }
            }
            finaliser.put(adder, results);
        }
        to_latex();
    }
    public static String stringcutter(String str)
    {
        // cut extraneous parts of the string
        // so if the input is "C++1T_100W", output is 1T100W
        if (str.contains("W"))
        return str.replaceAll("\\+\\+", "").replaceAll("C","").replaceAll("c", "").replaceAll("_","").replaceAll("\\.txt","");
        else
        return str.replaceAll("\\+\\+", "").replaceAll("C","").replaceAll("c", "").replaceAll("T","").replaceAll("\\.txt","");
    }
    public static void inittable()
    {
        // initialise the LATEX table
        System.out.print("\\begin{longtable}{");
        int n_rows = headers.length + 1;
        for (int i = 0; i < n_rows; i++)
            System.out.print("|l");
        System.out.println("|}");
        System.out.println("\\hline");
        System.out.print(" & ");
        for (int i = 0; i < headers.length; i++)
        {
            System.out.print("\\textbf{" + headers[i] + "}");
            if (i != headers.length - 1)
                System.out.print(" & ");
            else
                System.out.println("\\\\ \\hline");
        }
        System.out.println("\\endfirsthead\n" +
                "%\n" +
                "\\endhead\n" +
                "%");
    }
    public static String Tremove(String str)
    {
        return str.split("T")[0];
    }
    public static void to_latex() {
        // convert to LaTeX format
        inittable();
        // it is necessary to define a string array because only vertical filling is possible
        // also make sure that the same number of runs is used in both cases, or results may not be as expected.
        String printer[][] = new String[results.size()][finaliser.size() + 1];
        int parentindex = 1;
        for (Map.Entry O : finaliser.entrySet()) {

        TreeMap<String, Double> res = (TreeMap<String, Double>) O.getValue();
        // string goes as the 0th index
        int index = 0;
        for (Map.Entry P: res.entrySet())
        {
            printer[index][0] = Tremove(stringcutter((String) P.getKey()));
            printer[index][parentindex] = String.valueOf(round((Double) P.getValue()));
            index++;
        }
        parentindex++;
        }
        for (int i = 0; i < printer.length; i++)
        {
            for (int j = 0; j < printer[0].length; j++)
            {
                System.out.print(printer[i][j]);
                if (j != printer[0].length - 1)
                {
                    System.out.print(" & ");
                }
            }
            System.out.println(" \\\\ \\hline");
            if (printer.length == 38 && i == 18)
            {
                // stop here. We've reached the end of a table and need to get a new one
                // that is, collect data for T = 200
                // remember though not to run this routine if we do not have differing thread sizes
                System.out.println("\\end{longtable}");
                System.out.println();
                // initialise the next table
                inittable();
            }
        }
        System.out.println("\\end{longtable}");
//        for (Map.Entry O : results.entrySet()) {
//            System.out.print(O.getKey());
//            System.out.print(" & ");
//            System.out.print(round((Double) O.getValue() / num_dir));
//            System.out.print(" & ");
//            System.out.println("\\\\ \\hline");
//        }
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