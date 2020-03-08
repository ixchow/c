[ "prog.cpp" -nt "prog" ]
cecho "Compiling program..."
ccc prog.cpp -lstdc++ -o prog
./prog
