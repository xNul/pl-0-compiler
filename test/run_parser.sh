tests="tests.txt"
parser="../parser.out"

i=0

while read inp out ; do
    # create directories if needed
    out_dir=$(dirname "$out")
    mkdir -p "$out_dir"
    
    # run the parser
    ./"$parser" "$inp" "$out"
    
    let i=$i+1

done < "$tests"

echo "# of test cases completed: $i"
