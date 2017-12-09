#!/bin/bash

#tests exit and commands with exit

./bin/rshell << 'EOF'
exit

exit exit

echo hello; exit

echo hello; exit; echo goodbye

;exit

ls exit

exit 123

exitexitexitexit

exit exit eeeexit exit

 exit

   exit


EOF