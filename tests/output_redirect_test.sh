#!/bin/bash

#tests commands that use output (overwrite)

./bin/rshell << 'EOF'

echo hello > input.txt

echo hello >

echo hello > > input.text

cat input.txt > input.txt

cat input.txt >

cat testing > 123

cat testing > | >

cat testing > && echo testing as well

cat testing > output.txt && echo tester

cat testing > output.txt && echo tester > output2.txt

(cat testing > output.txt && echo tester) > output2.txt

)cat testing > output.txt && echo tester > output2.txt)

cat testing > output.txt && echo tester > output2.txt >

cat testing > output.txt && echo tester > output2.txt > > >

> echo hello

> echo hello > input.txt

> wekvd

> > > > > > > >

>>>>>>>>>>>>>>>

echo a > input.txt && exit

echo a > input.txt exit && exit

EOF

