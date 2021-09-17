tests="tests_grader.txt"
vm="../vm.out"

i=0
passed=0
failed=0

# check if vm_out and tests_grader.txt exists
if [[ -e $vm && -e $tests ]] ; then
    echo "$vm and $tests are found. Starting tests.."
else
    echo "$vm or $tests could not be found! Aborting.."
    exit
fi

while read inp out vm_in vm_out gt_out gt_vm_out ; do
    # create directories if needed
    out_dir=$(dirname "$out")
    mkdir -p "$out_dir"
    vm_out_dir=$(dirname "$vm_out")
    mkdir -p "$vm_out_dir"
    
    # run the input on virtual machine
    ./"$vm" "$inp" "$out" "$vm_in" "$vm_out"
    
    # compare the output with groundtruth
    _diff_simul_out="$(diff -B -w $out $gt_out)"
    _diff_vm_out="$(diff -B -w $vm_out $gt_vm_out)"
    
    if [[ $_diff_simul_out || $_diff_vm_out ]] ; then
        # sad.. difference found
        echo "TEST $i FAILED"
        let failed=$failed+1
        
        if [[ $_diff_simul_out ]] ; then
            echo "   There is difference between $out and $gt_out"
        fi
        
        if [[ $_diff_vm_out ]] ; then
            echo "   There is difference between $vm_out and $gt_vm_out"
        fi

    else
        # yay! test passed
        echo "TEST $i PASSED"
        let passed=$passed+1
    fi
    
    let i=$i+1

done < "$tests"

echo "# of tests       : $i"
echo "# of tests passed: $passed"
echo "# of tests failed: $failed"
