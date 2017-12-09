#!/bin/bash

#tests commands that utilze pipe

./bin/rshell << 'EOF'

echo "hello there" | sed "s/hello/hi/"

cat < input.txt | tr A-Z a-z

cat < input.txt | tr A-Z a-z | tr a-z A-Z

cat < input.txt | tr A-Z a-z |

cat < input.txt | |

cat < input.txt | tr A-Z a-z | | tr a-z A-Z

cat < input.txt |

cat < input.txt | | | | | 

cat < input.txt | | ||||| tr A-Z a-z

|||||

|

echo | echo

echo "|" | tr A-Z a-z

cat input.txt | exit

exit | exit

echo "|" | tr A-Z a-z | exit

(echo "|" | tr A-Z a-z) && exit

echo "|" | tr A-Z a-z ||||exit

echo "|" | tr A-Z a-z || exit

echo a | print

cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2

cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 |

EOF

