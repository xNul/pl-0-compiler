tests="tests_grader.txt"
parser="../parser.out"
EMPH='\033[1;31m'
DEEMPH='\033[0m'

i=0
passed=0
failed=0

# check if parser.out and tests_grader.txt exists
if [[ -e $parser && -e $tests ]] ; then
    echo "$parser and $tests are found. Starting tests.."
else
    echo "$parser or $tests could not be found! Aborting.."
    exit
fi

while read inp out gt_out ; do
    # create directories if needed
    out_dir=$(dirname "$out")
    mkdir -p "$out_dir"
    
    # run the parser
    ./"$parser" "$inp" "$out"
    
    # compare the output with ground truth
    _diff="$(diff -B -w $out $gt_out)"
    
    if [[ $_diff ]] ; then
        # sad.. difference found
        echo "TEST $i FAILED"
        let failed=$failed+1
        
        echo "   There is difference between $out and $gt_out:"
        echo "==================================================="
        echo $_diff
        echo "==================================================="
        echo -e "${EMPH}Test this yourself by running the following${DEEMPH}: "
        echo "  (cd test/; ./\"$parser\" \"$inp\" \"$out\")"
        echo "The output is in \"test/$out\""
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
