tests="tests_grader.txt"
la="../la.out"

i=0
passed=0
failed=0

# check if la.out and tests_grader.txt exists
if [[ -e $la && -e $tests ]] ; then
    echo "$la and $tests are found. Starting tests.."
else
    echo "$la or $tests could not be found! Aborting.."
    exit
fi

while read inp out gt_out ; do
    # create directories if needed
    out_dir=$(dirname "$out")
    mkdir -p "$out_dir"
    
    # run the lexical analyzer
    ./"$la" "$inp" "$out"
    
    # compare the output with ground truth
    _diff="$(diff -B -w $out $gt_out)"
    
    if [[ $_diff ]] ; then
        # sad.. difference found
        echo "TEST $i FAILED"
        let failed=$failed+1
        
        echo "   There is difference between $out and $gt_out"
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
