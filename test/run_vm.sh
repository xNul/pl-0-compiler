tests="tests.txt"
vm="vm.out"

i=0

while read inp out vm_in vm_out ; do
    # run the input on virtual machine
    ./"$vm" "$inp" "$out" "$vm_in" "$vm_out"
    
    let i=$i+1

done < "$tests"

echo "# of test cases completed: $i"
