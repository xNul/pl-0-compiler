name="./parser.out"

num=0
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=1
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=2
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=3
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=4
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=5
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=6
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=7
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=8
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt

num=9
echo "Checking $num..."
"$name" test/io/inputs/inp_$num.txt test/io/your_outputs/your_out_$num.txt && diff -B -w test/io/ground_truth/gt_out_$num.txt test/io/your_outputs/your_out_$num.txt