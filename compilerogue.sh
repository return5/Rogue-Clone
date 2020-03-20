#!/bin/bash
#compile script for rogue_clone
#compiles rogue_clone and creates executable named 'rogue_clone'
#defaults to using gcc, but uses clang if user supplies '-c' or '--clang' as argument to script. 
#use argumnet --help to bring up help info

#prints the help message to terminal.
printHelp() {
	printf "compile script for rogue_clone\n"
	printf "compiles rogue_clone and creates executable names 'rogue_clone'\n"
	printf "defaults to using gcc, but uses clang if user supplies '-c' to script.\n\n"
	printf "options:\n"
	printf " -c   --clang 	use clang instead of gcc\n"
	printf "-help  --help 	prints this page then exits\n"
}

#checks if GCC is installed, and if so it compiles the game with given flags.  if not installed then gives error message and exits.
useGCC() {
	(gcc -v >/dev/null 2>&1 && 
	printf "using GCC\n" &&
	gcc @src_files -orogueclone -Wall -Wextra -O2 -Iheaders -finline-functions -Wswitch-enum -lncurses -std=gnu11 -orogue_clone ) ||
	printf "error, gcc seems to not be installed.\n"
}

#compiles game using Clang
useClang() {
	printf "using Clang\n"
	clang @src_files -Iheaders -Wall -Wextra -O2 -lncurses -finline-functions -Wswitch-enum -std=gnu11 -orogue_clone   
}

main() {
	case "$1" in
		-help | --help)
			printHelp && exit
			;;
		-c | --clang)
			(clang -v >/dev/null 2>&1 && useClang) || (printf "falling back to GCC.\n" && useGCC)
			;;
		*)
			useGCC
			;;
	esac
}

#make list of all .c files to include. file paths are writtent to file 'src_files'
find  "${PWD}/src" -type f > "${PWD}/src_files"

main "$1"
rm src_files
