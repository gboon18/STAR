#!/bin/tcsh
#05102021(start)
# starver SL20c
starver SL19b
#05102021(finish)

#05102021(start)
# root4star -l -b -q runmakeMuDstQA.C\(\"$1\",$2,$3,\"$4\",$5\)
root4star -l -b -q runmakeMuDstQA.C\(\"$1\",$2,$3,\"$4\",$5,$6,$7,\"$8\"\)
#05102021(finish)

