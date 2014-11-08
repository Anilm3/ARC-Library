find src/ include/ -regex ".*\.\(h\|c\)" -exec sh -c 'echo "## $1 ##" ; echo ; splint -I src -I include $1 ; echo' sh {} \;  > splinter 2>&1
