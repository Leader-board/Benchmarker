# Single threaded Python version of Benchmarker.
import time
import math as mt
totalscore = 0
stagetime = [0.000]*5
# selection routine
def selection():
	print("Type 1 to start benchmarking or 0 to quit")
	t = int(input())
	if (t == 0):
		quit()
	while (t != 1):
		print("Type 1 to start benchmarking or 0 to quit")
		t = int(input())
		if (t == 0):
			quit()
# launch benchmarking routine
def mainbase():
	global totalscore
	global stagetime
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
						if (c == powcheck * powcheck):
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
			print(str(p * 4 + (q - 1) * 20) + " % complete!" + "\n")
			print("Time taken for that stage:- " + str(timetake[p - 1]) + "\n")
			print("Score obtained for that stage:- " + str(score[p - 1] * 5) + "\n")
# main routine
selection()
mainbase()
for i in range(0, 5):
	print("Average time taken for stage " + str(i + 1) + " is " + str(stagetime[i]) + " seconds " + "\n")
print("Your system has scored a total of " + str(totalscore) + " points!" + "\n")
