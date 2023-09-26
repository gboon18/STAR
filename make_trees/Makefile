#!/bin/bash

all: configure

counter=0

RootFile="FXT7p7.root"
cdir=`pwd`
configure: 
	@cd Data ; \
		for dir in `ls`;do \
		cp ../subq.con $${dir} ;\
		echo $${dir}' generating' ;\
		cd $${dir} ;\
		awk  '{if($$3=="run.csh") $$3="'$(cdir)/$${dir}.csh'"; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.log") $$3="'$(cdir)'/job.log"; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.out") $$3="'$(cdir)'/job.out"; print > "subq.con"}' subq.con ; \
		awk  '{if($$3=="job.err") $$3="'$(cdir)'/job.err"; print > "subq.con"}' subq.con ; \
		cd .. ;\
		echo "#!/bin/csh" > $${dir}/$${dir}.csh ;\
		echo "root4star -q -b -l 'readPicoDst.C(\"$(cdir)/$${dir}/file.list\",\"$(cdir)/$${dir}/FXT7p7\")'" >> $${dir}/$${dir}.csh;\
		echo 'echo $$? '"> $(cdir)/$${dir}/exitcode" >> $${dir}/$${dir}.csh ;\
		chmod 755 $${dir}/$${dir}.csh ;\
	done ; \
	cd ../ ; \
	mkdir merged/ ; \
	mkdir merged/incomplete/



submit:
	@for dir in `ls Data` ; do \
		if [ ! -d Data/$${dir}/Data ];then \
			echo $${dir} ;\
			condor_submit Data/$${dir}/subq.con; \
		fi ;\
	done ; \
	python periodic_check.py "make check" 10

check:
	@cd Data ; \
	for dir in `ls` ; do \
		if [ -e "$${dir}/exitcode" ];then \
			exitcode=`cat $${dir}/exitcode` ; \
			if [ $${exitcode} -ne 0 ]; then \
				echo "$${dir} failed" ; \
			# elif [ $${exitcode} -e 1 ]; then \
			# 	echo "$${dir} has anal warning|error" ; \
			fi; \
			c=$$(( $${c:-$(COUNT)}+0 )); \
		else \
			echo "$${dir} not finished" ; \
			c=$$(( $${c:-$(COUNT)}+1 )); \
			# echo "count $$c"; \
		fi ; \
	done ; \
	echo "Unfished jobs: $$c" ; \
	cd ../ ; \
	echo "$$c" > unfi.txt

clean:
	for dir in `ls Data`;do \
		rm Data/$${dir}/$${dir}.csh ; \
	done

clearRoot:
	for dir in `ls Data`;do \
		rm Data/$${dir}/${RootFile} ; \
	done
	
merge: #use mer for now
	cd Data ; \
	mkdir merge ; \
	rootfiles=(`find * -name '*.root'`) ; \

	for file in $${rootfiles[@]}; do \
		roots=() ; \
		for dir in `ls`; do \
			if [ -d $${dir} ];then \
				roots=($${roots[@]} $${dir}/$${file}) ; \
			fi ; \
		done ; \
		echo hadd Data/merge/$${file} $${roots[@]} ; \
		hadd Data/$${file} $${roots[@]} ; \
	done

chec:
	@for dir in `ls Data` ;do\
		ls -hl Data/$${dir}/*.root ;\
	done

mer:
	cd Data ; \
	mkdir merge ; \
	hadd merge/final.root `find . -name '*.root'`

clearMergedRoot:
	cd merged ; \
	find . -name "*root" -exec rm -vr "{}" \;
	
clearEmpty:
	find Data -name "*" -type f -size 0c | xargs -n 1 rm -f

submitEmpty:
	for dir in `ls Data` ;do\
		if [ ! -f Data/$${dir}/${RootFile} ];then \
			condor_submit Data/$${dir}/subq.con ;\
		fi ; \
	done

clearlog:
	for dir in `ls Data`;do \
		rm Data/$${dir}/job.log ;\
		rm Data/$${dir}/job.err ;\
		rm Data/$${dir}/job.out ;\
		rm Data/$${dir}/exitcode ;\
		# rm Data/$${dir}/file.list ;\
		rm Data/$${dir}/subq.con ;\
		rm Data/$${dir}/*.csh ;\
	done
