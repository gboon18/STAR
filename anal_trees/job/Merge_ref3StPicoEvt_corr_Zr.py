#!/usr/bin/env python
import os, time, datetime, sys
import glob
import ROOT

#Zr_EPD_mean
#start time
start = time.time()

dca_cut=int(sys.argv[1])
nhitsfit_cut=int(sys.argv[2])
nsp_cut=int(sys.argv[3])
m2low_cut=int(sys.argv[4])
m2up_cut=int(sys.argv[5])
ptmax_cut=int(sys.argv[6])
ymax_cut=int(sys.argv[7])
detefflow_err=int(sys.argv[8])
deteffhigh_err=int(sys.argv[9])

print dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err

file_paths = [
    "/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/"
]

list_Zr = []
for file_path in file_paths:

        # Define the file name pattern with placeholders for variable values
        file_pattern = "Zr_mTerms_f_*_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root"

        # Substitute the variable values into the file name pattern using str.format()
        file_pattern = file_pattern.format(dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err)

        # Use glob to find files that match the pattern in the given path
        root_files = glob.glob(os.path.join(file_path, file_pattern))
	
	# Exclude corrupted files
	corrupted_files = []
	for file_name in root_files:
	    file_size = os.path.getsize(os.path.join(file_path, file_name))
	    try:
	        with open(os.path.join(file_path, file_name), 'rb') as f:
	            f.read(100)
	    except:
	        print("Warning: file " + file_name + " is corrupted, skipping.")
	        corrupted_files.append(file_name)
	        continue
	    if file_size == 0:
	        print("Warning: file " + file_name + " has size 0, skipping.")
	        corrupted_files.append(file_name)
                continue
                
            Rfile = ROOT.TFile.Open(os.path.join(file_path, file_name))
            if not Rfile:
                print("Error: could not open file")
                corrupted_files.append(file_name)
                continue

            elif Rfile:
                Rfile.Close()
	
	root_files = list(set(root_files) - set(corrupted_files))
	
	line_Zr = None
	with open("./Zr_GoodRunNumbers.list") as f_zr:
	    i = 0;
	    line = ''
	    for line in f_zr:
	        line_Zr = line.split("\t")
	
	for A in root_files:
	    for line in line_Zr:
	        if A.find(line) != -1:
	            list_Zr.append(os.path.join(file_path, A))

n=0
while( len(list_Zr) != 1 ):
    n+=1
    print(str(n)+" times hadd")
    A=list_Zr.pop()
    B=list_Zr.pop()
    command="hadd -f /star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/merged_mTerms_f_Zr_good123/incomplete/"+str(n)+"_mTerms_f_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root ".format(dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err) + A + " " +B
    os.system(command)
    list_Zr.append("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/merged_mTerms_f_Zr_good123/incomplete/"+str(n)+"_mTerms_f_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root".format(dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err))
    if n > 1:
        os.system("rm -f /star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/merged_mTerms_f_Zr_good123/incomplete/"+str(n-1)+"_mTerms_f_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root".format(dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err));

os.system("mv /star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/merged_mTerms_f_Zr_good123/incomplete/"+str(n)+"_mTerms_f_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root /star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/test_output/merged_mTerms_f_Zr_good123/Zr_mTerms_f_mergedFile_dca_{}_nhitsfit_{}_nsp_{}_m2low_{}_m2up_{}_ptmax_{}_ymax_{}_detefflow_err_{}_deteffhigh_err_{}.root".format(dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err, dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err))
# ###############################################


#end time
end = time.time()

#total time taken
duration = end - start
print "hadd time taken: "
print datetime.timedelta(seconds=duration)
#send email
os.system('python haddDone.py')
sys.exit()
