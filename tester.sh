#! /bin/bash

# Can recieve the following arguments:
#	l: only execute the lexer
#	L: lexer verbose option
#	P: parser verbose option
#	test_name: test to run

result=tester_result.txt
compiler=compiler_program

lexer_verbose=0
parser_verbose=0
exe_only_lexer=0

while getopts ":lLP" opt; do
	case ${opt} in
		l)
			exe_only_lexer=1
			;;
		L)
			lexer_verbose=1
			;;
		P)
			parser_verbose=1
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
	echo "ERROR: File to test needed."
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

./${compiler} "${lexer_verbose}" "${parser_verbose}" "${exe_only_lexer}" "${test_file}" "${result}"
make clean
