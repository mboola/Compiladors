#! /bin/bash

# Can recieve the following arguments:
#   L: lexer verbose option
#   l: test only the lexer
#   P: parser verbose option
#   file_name: name of the test to run

result=frontend.output
compiler=compiler_program
c3a_output=c3a.output

lexer_verbose=0
parser_verbose=0
exe_only_lexer=0

while getopts ":LlP" opt; do
    case ${opt} in
        L)
            lexer_verbose=1
            ;;
        P)
            parser_verbose=1
            ;;
        l)
            exe_only_lexer=1
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
    echo "ERROR: Execute script with file to test."
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

if [ ! -f "$c3a_output" ]; then
    touch $c3a_output
fi

if [ ! -f "$compiler" ]; then
    make > /dev/null
fi

echo "Input file test:"
cat ${test_file}
echo ""

./${compiler} ${lexer_verbose} ${parser_verbose} ${exe_only_lexer} ${test_file} ${result} ${c3a_output}
make clean
