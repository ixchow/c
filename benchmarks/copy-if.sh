sizeA=`stat -c %s fileA`
sizeB=`stat -c %s fileB`
if [ $sizeA -le $sizeB ]
then
	echo "fileA is smaller"
	cp fileA fileS
else
	echo "fileB is smaller"
	cp fileB fileS
fi
