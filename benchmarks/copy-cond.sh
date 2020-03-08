sizeA=`stat -c %s fileA`
sizeB=`stat -c %s fileB`
[ $sizeA -le $sizeB ]
cecho "fileA is smaller"
ccp fileA fileS
[ $sizeA -gt $sizeB ]
cecho "fileB is smaller"
ccp fileB fileS
