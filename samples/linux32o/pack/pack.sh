#!/bin/bash

ZIP="$1.zip"
FOLDER="$2"

zip -j $ZIP $FOLDER 
cat deliver.sh $ZIP > $1  && chmod +x $1

exit 0

