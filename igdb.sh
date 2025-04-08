#!/bin/bash

filename=~/crash_$(date +%Y%m%d_%H%M%S).txt
echo "Starting INDI driver debugging for" $*
gdb -batch -ex "handle SIG33 nostop noprint" -ex "set follow-fork-mode child" -ex "run" -ex "bt" --args indiserver -r 0 -v $* > $filename 2>&1
echo "Debugging finished. Please send" $filename "file to support."

