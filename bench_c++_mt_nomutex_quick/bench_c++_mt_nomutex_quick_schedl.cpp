/*
Similar to the nomutex version except that k has been kept to 100. The purpose is to investigate whether there are any performance variances with very high threads when each
thread dies very quickly.
*/
#include <iostream>
#include <math.h>
#include <ctime>
#include <exception>
#include <thread>
#include <mutex>
#include <vector>
#include <sched.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
auto NUMBER_OF_THREADS = 16;
using namespace std;
void printresult(double*, double, int);
// This program prints all the Pythagorean triplets from 1 to k , which the user will enter.
int k_val = 0; // value of k for quick version
int policy_code;
void sched_tester()
{
	// print scheduling policy of current process
    int policy = sched_getscheduler(getpid());
    switch (policy)
    {
    case SCHED_OTHER:
        printf("Policy is normal\n"); // 0
        break;
    case SCHED_RR:
        printf("Policy is round-robin\n"); // 2
        break;
    case SCHED_FIFO:
        printf("Policy is first-in, first-out\n"); // 1
        break;
    case SCHED_BATCH:
        printf("Policy is batch\n"); // 3
        break;
    case SCHED_IDLE:
        printf("Policy is idle\n"); // reference = https://lwn.net/Articles/3866/ = 5
        break;
    case -1:
        perror("sched_getscheduler");
        break;
    default:
        fprintf(stderr, "Unknown policy!\n");
    }
}
void selection()
{
	int choose;
base:cout << "Type 1 to start benchmarking." << '\n';
	cout << "Note: " << thread::hardware_concurrency() << " threads supported" << '\n'; // number of threads available
	try
	{
		cin >> choose;
		if (cin.fail())
			throw 2;
		if (choose != 1)
		{
			throw "Invalid number, try again \n";
		}
	}
	catch (char* msg)
	{
		cout << msg << '\n';
		goto base;
	}
	catch (int x)
	{
		cout << "Invalid entry. Program will close now. \n";
		exit(1);
	}
	// ask for number of threads
	cout << "Enter number of threads to run program with\n";
	cin >> NUMBER_OF_THREADS;
	cout << "Enter value of k for every run\n";
	cin >> k_val;
	cout << "Enter scheduling policy\n";
	cin >> policy_code;
	// if necessary make the process real-time
	if (policy_code == 2)
	{
		// chrt to rr
		string s;
		s.append("sudo chrt -r --pid 50 ");
		s.append(to_string(getpid()));
		system(s.c_str());
	}
	else if (policy_code == 1)
	{
		// chrt to fifo
		string s;
		s.append("sudo chrt -f --pid 50 ");
		s.append(to_string(getpid()));
		system(s.c_str());
	}
}
void mainbase(int thread_no)
{
	// variables used for main run
	long count;
	double timetake[5];
	double stagetime[5];
	double totalscore = 0;
	double score[5];
	double c;
	double a, b, powcheck, k, d, x, y; // x and y are the squares of a and b.
	int percentage = 0;// declaring variable to update percentage
	// D will represent C for greatest pythagorean triplet purposes.
	// k is the number which the user will enter. This value limits the value of a and b through which the program can search.
	for (int q = 1; q <= 5; q++)
	{
		for (int p = 1; p <= 5; p++)
		{
			auto begin = chrono::high_resolution_clock::now();
			a = 1;
			b = 1;
			c = 1;
			d = 1;
			count = 0;// a and b are the base/height.
			// so we are keeping k fixed this time.
			k = k_val; // irrespective of run number
			while (b <= k)
			{
				while (a <= k)
				{
					x = a * a;
					y = b * b;
					c = x + y;
					powcheck = b;	// b as starting point. Meant to speed up execution
					while (powcheck <= ceil(1.42 * k)) // Max value of c with relation to a and b is c = root2 of a,b
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
			auto end = chrono::high_resolution_clock::now();
			double elapsed_secs = chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / (double)1000000000;
			timetake[p - 1] = elapsed_secs;
			double r;
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
			if (timetake[p - 1] == 0)
			{
				// handle corner case where the time is simply too little
				elapsed_secs = 0.0005;
				timetake[p - 1] = 0.0005;
			}
			score[p - 1] = 200 * (r / timetake[p - 1]);
			totalscore = totalscore + (0.2 * (score[p - 1]));
			stagetime[p - 1] = stagetime[p - 1] + 0.2 * elapsed_secs;
			// lock to avoid garbage output with multiple threads
			/*m.lock();
			cout << p * 4 + (q - 1) * 20 << " % complete for thread " << thread_no << '\n';
			cout << "Time taken for that stage:- " << timetake[p - 1] << " for thread " << thread_no << '\n';
			cout << "Score obtained for that stage:- " << score[p - 1] * 5 << " for thread " << thread_no << '\n';
			m.unlock();*/
		}
	}
	// finalise results
	/*m.lock();
	for (int t = 0; t < 5; t++)
	{
		avg_stagetime[t] = avg_stagetime[t] + stagetime[t] / NUMBER_OF_THREADS;
	}
	fin_score = fin_score + totalscore / NUMBER_OF_THREADS;
	printresult(stagetime, totalscore, thread_no);
	m.unlock();*/
}
void printresult(double* stagetime, double totalscore, int t_no)
{
	// print internal thread number
	cout << "------------------------\n";
	if (t_no != 0)
		cout << "RESULTS FOR THREAD " << t_no << '\n';
	else
		cout << "OVERALL RESULTS\n";
	cout << "------------------------\n";
	for (int i = 1; i <= 5; i++)
	{
		cout << "Average time taken for stage " << i << " is " << stagetime[i - 1] << " seconds and average score is ";
		double r;
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
		cout << (1000 * r / stagetime[i - 1]) << '\n';
	}
	if (t_no == 0)
		cout << "Final score: " << totalscore << " points!" << '\n';
	else
	{
		// sub-thread score
		cout << "Thread " << t_no << " score: " << totalscore << " points!" << '\n';
	}
}
int main()
{
	selection();
	// set scheduling policy
	struct sched_param sp;
	int ret;
    ret = sched_getparam(getpid(), &sp);
    if (ret == -1)
    perror("Getting scheduling parameters failed!\n");
	sched_tester(); // retrieve scheduling policy of current process
    ret = sched_setscheduler(getpid(), policy_code, &sp);
    if (ret == -1)
    perror("Setting scheduling parameters failed\n");
    sched_tester();
	// determine number of threads
	vector<thread> t(NUMBER_OF_THREADS);
	// find total time taken to benchmark
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		t[i] = thread(mainbase, (i + 1));
	}
	// run the threads!
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		t[i].join();
	}
	// printresult(avg_stagetime, fin_score, 0);
	auto end = chrono::high_resolution_clock::now();
	cout << "Total time taken to run benchmark in seconds: " << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / (double)1000000000;
	return 0;
}

