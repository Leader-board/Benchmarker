# Multi threaded Python version of Benchmarker.
import time
import math as mt
import threading
totalscore = 0
stagetime = [0.000]*5
NUMBER_OF_THREADS = 1 # number of threads to run program
mutex = threading.Lock() # mutex
avg_stagetime = [0.000] * 5
fin_score = 0.0000
# selection routine
def selection():
	global NUMBER_OF_THREADS
	print("Type 1 to start benchmarking or 0 to quit")
	t = int(input())
	if (t == 0):
		quit()
	while (t != 1):
		print("Type 1 to start benchmarking or 0 to quit")
		t = int(input())
		if (t == 0):
			quit()
	print("Enter number of threads to run program with")
	NUMBER_OF_THREADS = int(input())
# launch benchmarking routine from here
# printresult - printing result of each thread
def printresult(totalscore, t_no, stagetime):
	print("------------------------")
	if (t_no != 0):
		print("RESULTS FOR THREAD " + str(t_no))
	else:
		print("OVERALL RESULTS")
	print("------------------------")
	for i in range(1, 6):
		print("Average time taken for stage " + str(i) + " is " + str(stagetime[i - 1]) + " seconds and average score is ", end='')
		r = 0.000;
		if (i == 1):
			r = 0.003;
		if (i == 2):
			r = 0.035;
		if (i == 3):
			r = 0.273;
		if (i == 4):
			r = 2.225;
		if (i == 5):
			r = 7.536;
		print((1000 * r / stagetime[i - 1]));
	if (t_no == 0): # overall system score
		print("Final score: " + str(totalscore) + " points!")
	else: # thread score
		print("Thread " + str(t_no) + " score: " + str(totalscore) + " points!");
def mainbase(thread_no):
	global totalscore
	global stagetime
	global NUMBER_OF_THREADS
	global mutex
	global avg_stagetime
	global fin_score
	a = float()	
	b = float()
	powcheck = float()
	k = float()
	d = float()
	x = float()
	y = float()
	verify = 0
	percentage = 0
	c = float()
	score = [0.000] * 5
	totalscore = float(0)
	count = 0
	timetake = [0.000]*5
	for q in range(1, 6):
		for p in range(1, 6):
			begin = time.time()
			a = 1
			b = 1
			c = 1
			d = 1
			count = 0
			if (p == 1):
				k = 100
			elif (p == 2):
				k = 250
			elif (p == 3):
				k = 500
			elif (p == 4):
				k = 1000
			elif (p == 5):
				k = 1500
			while (b <= k):
				while (a <= k):
					x = a*a
					y = b*b
					c = x + y
					powcheck = b
					while (powcheck <= mt.ceil(1.42*k)):
						if (c == powcheck ** 2):
							if (c >= d):
								d = c
							count = count + 1
							powcheck = 2*k + 1
						else:
							powcheck = powcheck + 1
					a = a + 1
				a = 1
				b = b + 1
			end = time.time()
			elapsed_secs = float(end - begin)
			timetake[p - 1] = elapsed_secs
			r = float()
			if (p == 1):
				r = 0.003
			elif (p == 2):
				r = 0.035
			elif (p == 3):
				r = 0.273
			elif (p == 4):
				r = 2.225
			elif (p == 5):
				r = 7.536
			score[p - 1] = 200 * (r / timetake [p - 1])
			totalscore = totalscore + (0.2*(score[p - 1]))
			stagetime[p - 1] = stagetime[p - 1] + 0.2*elapsed_secs
			mutex.acquire()
			print(str(p * 4 + (q - 1) * 20) + " % complete for thread " + str(thread_no))
			print("Time taken for that stage:- " + str(timetake[p - 1]) + " for thread " + str(thread_no))
			print("Score obtained for that stage:- " + str(score[p - 1] * 5) + " for thread " + str(thread_no))
			mutex.release()
	mutex.acquire()
	for t in range(0, 5):
		avg_stagetime[t] = avg_stagetime[t] + stagetime[t] / NUMBER_OF_THREADS
	fin_score = fin_score + totalscore / NUMBER_OF_THREADS
	printresult(totalscore, thread_no, stagetime)
	mutex.release();
# main routine
selection()
# mainbase
tr = []
for i in range(0, NUMBER_OF_THREADS):
	tr.append(threading.Thread(target = mainbase, args = ((i + 1),)))
begin = time.time()
for i in range(0, NUMBER_OF_THREADS):
	tr[i].start()
for i in range(0, NUMBER_OF_THREADS):
	tr[i].join()
end = time.time()
printresult(fin_score, 0, avg_stagetime);
print("Total time taken to run benchmark in seconds: " + str(float(end - begin)))