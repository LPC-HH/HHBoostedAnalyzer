#!/bin/bash


if [ "$1" = "" ]; then
    echo "no input_list provided"
    echo "usage: source sumit_condor.sh <task_name> <input_list>"
    echo "QUIT!!"
    exit 1
fi

if [ "$2" = "" ]; then
    echo "no input_list provided"
    echo "usage: source sumit_condor.sh <task_name> <input_list>"
    echo "QUIT!!"
    exit 1
fi

##################################
###define input list and task_name
##################################
source /cvmfs/cms.cern.ch/cmsset_default.sh
input_list=$2
task_name=$1
files_per_job=5
top_directory=`git rev-parse --show-toplevel`

cd ${top_directory}
eval `scram runtime -sh`
#make clean;make -j 16
make -j 16
cd -

eos_dir=/store/group/lpcbacon/HHBoost/HHNtuple/V1p0/
executable=diHiggs

echo "top directory: "$top_directory

#################################
#obtain number of total files
#################################
nfiles=`cat ${input_list} | wc -l`

#############################################################
#compute number of jobs according to number of files_per_job
#############################################################
njobs=$((nfiles/files_per_job))
missing_file=$((nfiles%files_per_job))

echo $njobs
if (( $missing_file > 0 ));then
njobs=$((njobs+1)) 
fi

echo $njobs

##################################################
####create task directory inside condor directory
#################################################
condor_dir=${top_directory}/"condor"
scripts_dir=${top_directory}/"scripts"
task_name_dir=${top_directory}/"condor"/${task_name}
mkdir -p ${task_name_dir}
#####################################
#get run_job.sh file from scripts dir
#####################################
cp ${scripts_dir}/run_job.sh ${task_name_dir}/.
###################################################
#create output dir in eos and send the files there
##################################################
output_dir="/eos/uscms/"${eos_dir}/${task_name}
echo ${output_dir}
mkdir -p ${output_dir}

printf "\n"
printf "\n\ngfal-copy -f *.root gsiftp://cmseos-gridftp.fnal.gov//"${eos_dir}/${task_name} >> ${task_name_dir}/run_job.sh


##################################################
####create condor log directories inside task name 
#################################################
mkdir -p ${task_name_dir}/"log"
mkdir -p ${task_name_dir}/"out"
mkdir -p ${task_name_dir}/"err"

split -l $files_per_job -d -a 4 $input_list ${task_name_dir}/"input_list_"${task_name}"_"

ctr=0
for i in `ls ${task_name_dir}`; do 
    if [[ "$i" == *"input_list_"* ]]; then
	condor_submit_file=${task_name_dir}/"condor_submit_"${ctr}".condor"
	current_input_list=${task_name_dir}/$i

	printf "Universe = vanilla\n" > ${condor_submit_file}
	printf "Executable = "${task_name_dir}"/run_job.sh\n" >> ${condor_submit_file}
	printf "Should_Transfer_Files = YES \n" >> ${condor_submit_file}
	printf "WhenToTransferOutput = ON_EXIT\n" >> ${condor_submit_file}
	printf "Transfer_Input_Files = "${top_directory}/${executable}", "${current_input_list}", "${condor_dir}"/cms_setup.tar.gz\n" >> ${condor_submit_file}
	printf "notify_user = $(whoami)@cern.ch\n" >> ${condor_submit_file}
	printf "x509userproxy = \$ENV(X509_USER_PROXY)\n" >> ${condor_submit_file}
	printf "\n" >> ${condor_submit_file}
	printf "Output = "${task_name_dir}"/out/diHiggs.\$(Cluster)_\$(Process).stdout\n" >> ${condor_submit_file}
	printf "Error  = "${task_name_dir}"/err/diHiggs.\$(Cluster)_\$(Process).stderr\n" >> ${condor_submit_file}
	printf "Log    = "${task_name_dir}"/log/diHiggs.\$(Cluster)_\$(Process).log\n" >> ${condor_submit_file}
	printf "\n" >> ${condor_submit_file}
	printf "RequestMemory = 2000\n" >> ${condor_submit_file}
	
	printf "\n" >> ${condor_submit_file}
	printf "Arguments = ${i} diHiggs_output_${task_name}_${ctr}.root \n" >> ${condor_submit_file}
	printf "Queue\n" >> ${condor_submit_file}

	echo ${task_name_dir}/$i
	condor_submit $condor_submit_file
	sleep 0.01
	ctr=$((ctr+1))
    fi
done;

