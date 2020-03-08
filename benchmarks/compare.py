#!/usr/bin/env python3

from sys import argv
from subprocess import run
from time import time_ns

shell = './csh'

devnull = open('/dev/null', 'wb')

times = []
iters = 1
for script in argv[1:]:
	#print("Testing '" + script + "'...")
	before = time_ns()
	for x in range(0,iters):
		run([shell, script], stdout=devnull, stderr=devnull)
	after = time_ns()
	ns = str(after - before)
	times.append((" " * (15 - len(script))) + script + " took " + (" " * (10 - len(ns))) + ns + "ns for " + str(iters) + " runs.")
	#print("   " + str(after - before) + " ns")
print("\n".join(times))
