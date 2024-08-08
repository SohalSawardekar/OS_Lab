#!/bin/bash

echo "Enter the source file path: "
read source_file
echo "Enter the destination file path: "
read destination_file


if [ ! -f "$source_file" ]; then
echo "Source file does not exist."
return
fi

cp "$source_file" "$destination_file"

echo "Contents copied successfully from $source_file to $destination_file."


