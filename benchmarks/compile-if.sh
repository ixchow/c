if [ "prog.cpp" -nt "prog" ]
then
	cecho "Compiling program..."
	cc prog.cpp -lstdc++ -o prog
fi
./prog
