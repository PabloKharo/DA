#!/bin/bash

make
python3 generator.py

CompressedFile=$(mktemp)
DecompressedFile=$(mktemp)

./kp < tests/gen > $CompressedFile

DecomSize=$(stat -c%s tests/gen)
echo "Size of decompressed = $DecomSize bytes."
ComSize=$(stat -c%s $CompressedFile)
echo "Size of compressed = $ComSize bytes."

./kp < $CompressedFile > $DecompressedFile

Diff=$(diff tests/gen $DecompressedFile) 
if [ "$Diff" ] 
then
    echo "Files arenot equal"
else
    echo "Files are equal"
fi

rm $CompressedFile
rm $DecompressedFile