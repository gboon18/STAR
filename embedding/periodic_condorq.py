#! /usr/bin/env python

# ./periodic_condorq.py "condor_q hsko | wc -l" <period in unit of second>

import time, os, sys, string, datetime, subprocess

#start time
start = time.time()

def main(cmd, inc=60):
    while 1:
        print_condor=subprocess.check_output(cmd, shell=True)
        condor=print_condor.strip()
        print condor
        time.sleep(inc)
        if condor == "10": 
            print "Job Done!"
            # end time
            end = time.time()
            #total time taken
            duration = end - start
            print "job time taken: "
            print datetime.timedelta(seconds=duration)
            #send email
            os.system('python jobDone.py')
            # #merge
            # os.system('python Merge.py')
            sys.exit()
                

if __name__ == '__main__' :
    if len(sys.argv) < 2 or len(sys.argv) > 3:
        print "usage: " + sys.argv[0] + " command [seconds_delay]"
        sys.exit(1)

    cmd = sys.argv[1]
    if len(sys.argv) < 3:
        main(cmd)
    else:
        inc = string.atoi(sys.argv[2])
        main(cmd, inc)
