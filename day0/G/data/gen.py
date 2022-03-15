import random
import os
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 100000
P_LIMIT = 333
Q_LIMIT = 333

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def gen_empty():
	return

def gen_uniform(n, plim, qlim, pmin = 1, qmin = 1):
	return np.random.randint(pmin, plim + 1, n), np.random.randint(qmin, qlim + 1, n)

def gen_choice(n, plim, qlim, pchoice, qchoice):
	assert min(pchoice) >= 1 and max(pchoice) <= plim
	assert min(qchoice) >= 1 and max(qchoice) <= qlim
	return np.random.choice(pchoice, n), np.random.choice(qchoice, n)

def genTestcase(filename, gen, n, plim, qlim, **extra_param):
	log("Generating input for case {}, params: {}, {}, {}, {}".format(filename, n, plim, qlim, gen.__name__))
	# assert ..., "Parameters invalid!"
	if not extra_param:
		p, q = gen(n, plim, qlim)
	elif "p" in extra_param and "q" in extra_param:
		p = extra_param["p"]
		q = extra_param["q"]
		assert len(p) == len(q) == n and max(p) <= plim and max(q) <= qlim
	else:
		p, q = gen(n, plim, qlim, **extra_param)
	with open("{}.in".format(filename), "w") as f:
		# f.write("{} {} {}\n{}\n".format(n, l, r, " ".join(list(map(str, s)))))
		f.write("{}\n".format(n))
		f.write(" ".join(map(str, p)) + "\n")
		f.write(" ".join(map(str, q)) + "\n")
	log("Generating output for case {}".format(filename))
	os.system('(time ../infinitesynthesis/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, n, plim, qlim, **extra_param):
		self.cnt += 1
		genTestcase("{}{}".format(self.prefix, self.cnt), gen, n, plim, qlim, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += 1

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	
	for j in range(4):
		testcase.gen(gen_uniform, 1000, random.randint(30, 100), Q_LIMIT, qmin = random.randint(100, 300 + 1))
	
	for j in range(4):
		testcase.gen(gen_choice, N_LIMIT, P_LIMIT, Q_LIMIT, pchoice = list(range(1, random.randint(5, 16))) + [100, 333], qchoice = list(range(300, 333 + 1)))
	
	testcase.gen(gen_uniform, N_LIMIT - 1, 1, 1)
	testcase.gen(gen_uniform, N_LIMIT - 2, 1, 1)
	testcase.gen(gen_choice, N_LIMIT, P_LIMIT, Q_LIMIT, pchoice = [330, 331, 332, 333], qchoice = [330, 331, 332, 333])
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

sample.gen(gen_empty, 3, P_LIMIT, Q_LIMIT, p = [3, 3, 3], q = [1, 2, 3])
sample.gen(gen_empty, 3, P_LIMIT, Q_LIMIT, p = [2, 3, 3], q = [1, 2, 3])
sample.gen(gen_empty, 10, P_LIMIT, Q_LIMIT, p = [2, 1, 4, 7, 4, 8, 3, 6, 4, 8], q = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3])

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
