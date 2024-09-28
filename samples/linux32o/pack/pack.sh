#!/bin/bash

EXE=$( basename "$0" )

if [[ $# -lt 2 ]] ; then
	echo "Usage: $EXE <name> <folder>"
	exit 1
fi

FOLDER="$2"
if [[ ! -d $FOLDER ]]; then
	echo "Invalid folder: $2"
	exit 1
fi

NAME="$1"
EXEC="$FOLDER/$NAME"
if [[ ! -f $EXEC ]]; then
	echo "Invalid exec name: $NAME"
	exit 1
fi

read -r -d '' "RUN_SCRIPT" << "EOF"
#!/bin/bash
WORKDIR=$( mktemp -d )
EXE=$( basename "$0" )
 
#find last line +1
SCRIPT_END=$( awk '
  BEGIN { err=1; } 
  /^\w*___END_OF_SHELL_SCRIPT___\w*$/ { print NR+1; err=0; exit 0; } 
  END { if (err==1) print "?"; }
' "$0" )

# check for error
if [ "$SCRIPT_END" == '?' ]
then
   echo "Can't find embedded file"
   exit 1
fi

# Extract file
tail -n +$SCRIPT_END $0 >"$WORKDIR/file"

# Do something with the file
unzip -q "$WORKDIR/file" -d "$WORKDIR" && cd "$WORKDIR" && exec "./$EXE" "${@:1}" &

# Wait for finishing the execution
trap ' ' INT
wait $!

#  Cleanup and exit
rm -r "$WORKDIR"
exit 0

# Here's the end of the script followed by the embedded file
___END_OF_SHELL_SCRIPT___

EOF

ZIP="$NAME.zip"
zip -q -j $ZIP $FOLDER/* && echo "Compressing done." || exit 1
echo "$RUN_SCRIPT" > $NAME && cat $ZIP >> $NAME && chmod +x $NAME
echo "Executable file created: $NAME"

rm $ZIP
exit 0
