rm -f fileA fileB fileS prog

#make sure 'prog' is older than 'prog.cpp' for compile test:
touch prog
sleep 1
touch prog.cpp


#Set up files for move test:
dd bs=2G count=1 if=/dev/zero of=fileA
dd bs=1G count=1 if=/dev/zero of=fileB

#run copy test:
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
PATH=..:$PATH ./compare.py compile-if.sh compile-cond.sh

#run copy test:
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
PATH=..:$PATH ./compare.py copy-if.sh copy-cond.sh

#run echo test:
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
PATH=..:$PATH ./compare.py echo-if.sh echo-cond.sh
