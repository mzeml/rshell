#!/bin/bash

#tests commands that append

./bin/rshell << 'EOF'

cat < input.txt

cat << input.txt

cat < input.txt && echo hello

at < input.txt && echo hello

at < input.txt || echo cat failed

(cat < input.txt && echo out) 

echo d && (cat < input.txt && echo out) 

cat <                     input.txt

< echo hello

<       echo hello

< cat < input.txt

< cat <<<< inpit.txt

< cat <

<           cat <<< input.txt

< exit

cat < input.txt && exit

cat < exit && echo hello

EOF

