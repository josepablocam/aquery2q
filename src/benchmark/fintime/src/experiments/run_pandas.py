from definitions_pandas import *
from random import shuffle
from timeit import timeit
from sys import exit
import argparse

parser = argparse.ArgumentParser(description = "Time pandas benchmark")
parser.add_argument("-out",  type = str, 
 metavar = 'path', nargs = '?',  default = None,
 help = "path to file to write results in csv format"
 )
parser.add_argument("-iters", type = int,
 metavar = "n", nargs = '?', default = 10,
 help = "number of iterations for each function")
args = parser.parse_args()

# parse command line arguments
if args.out != None:
    # append to file
    filehandle = open(args.out, "a")
else:
    filehandle = None    
iters = args.iters


def timeAndWrite(f, filehandle, iters):
    funcname = f.__name__
    querynumber = funcname[1:]
    # timeit returns time in seconds, we want milliseconds
    time = (1000.0 * timeit(f, number = iters)) / iters
    # we don't care about measuring memory for pandas
    msg = "fintime,pandas," + str(iters) + "," + querynumber + "," + str(time) + ",NA\n"
    if filehandle == None:
        print(msg)
    else:
        filehandle.write(msg)


functions = [ q0, q1, q2, q3, q4, q5, q6, q7, q8, q9 ]
shuffle(functions) # randomize their execution order

# run and time each function, write to path if provided
for functionName in functions:
    timeAndWrite(functionName, filehandle, iters)

# clean up
if filehandle != None:
    filehandle.close()

exit()
    

            


