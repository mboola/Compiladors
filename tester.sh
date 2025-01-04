#! /bin/bash

# Can recieve the following arguments:
#	l: only execute the lexer
#	L: lexer verbose option
#	P: parser verbose option
#	test_name: test to run

verbose_result=verbose_result.txt
calculator_result=calc_result.txt
compiler=compiler_program
c3a_output=c3a.output

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

if [ ! -f "$verbose_result" ]; then
	touch $verbose_result 
fi

if [ ! -f "$calculator_result" ]; then
	touch $calculator_result
fi

if [ ! -f "$c3a_output" ]; then
    touch $c3a_output
fi

if [ ! -f "$compiler" ]; then
	make > /dev/null
fi

echo "###Printing input file test###"
cat ${test_file}
echo ""
echo "###Ended printing file###"
echo ""

./${compiler} "${lexer_verbose}" "${parser_verbose}" "${exe_only_lexer}" "${test_file}" "${verbose_result}" "${calculator_result}" "${c3a_output}"
make clean
