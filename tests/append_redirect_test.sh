#!/bin/bash

#tests commands that append

./bin/rshell << 'EOF'

echo hello >> input.txt

cat input.txt >> input.txt

echo hello > > input.txt

echo hello > > > input.txt

echo hello > >> input.txt

echo hello >>> input.txt

echo hello >>>>> input.txt

echo hello ><> input.txt

echo hello <> input.txt

echo hello > input.txt > echo bye

echo hello > input.txt >

echo hello > input.txt >>

echo hello >> input.txt >> echo bye

echo hello >> input.txt > echo bye

echo hello > input.txt >> echo bye

echo hello > input.txt > echo bye >>

echo hello > input.txt > echo bye >

echo >                input  >            echo bye

echo         >         input.txt

echp  >>>>>>>>>>>>>>>>>>

echo a >>>>>>>>>>>>>>>>>>>>>>>>

echo weet >>>>>>>>>>>>>>>>>>> 

echo dew >>>>>>>>>>>>>>>>> input.txt

>> echo abc >> input.txt

EOF