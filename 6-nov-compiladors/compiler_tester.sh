#! /bin/bash

# Can recieve the following arguments:
#   v: verbose option
#   l: test only the lexer
#   file_name: name of the test to run

result=result.txt
compiler=compiler_program

verbose=0
execution_option=0

while getopts ":vl" opt; do
    case ${opt} in
        v)
            verbose=1
            ;;
        l)
            execution_option=1
            ;;
        ?)
            echo "Invalid option: -${OPTARG}."
            exit 1
    esac
done

shift $((OPTIND - 1))

# Now $1 will be 'test_file'
if [ "$#" -eq 1 ]; then
    test_file=$1
else
    echo "ERROR: Argument number not correct."
    exit 1
fi

# Test if $test exists
if [ ! -f "$test_file" ]; then
    echo "ERROR: Test file $test_file does not exits."
    exit 1
fi

if [ ! -f "$result" ]; then
    touch $result 
fi

if [ ! -f "$compiler" ]; then
    make > /dev/null
fi

echo "Input file test:"
cat ${test_file}
echo ""

./${compiler} ${verbose} ${execution_option} ${test_file} ${result}
make clean
