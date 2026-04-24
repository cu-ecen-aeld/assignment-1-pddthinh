#!/bin/bash

filePath=$1
content=$2

# Validate arguments
if [ -z "${filePath}" ] || [ -z "${content}" ]; then
    echo "Usage: $0 <file_path> <content>"
    exit 1
fi

dirName=$(dirname "${filePath}")

if ! mkdir -p "${dirName}" || ! touch "${filePath}" > /dev/null 2>&1; then
    echo "Error: Could not create file"
    exit 1
fi

echo "${content}" > "${filePath}"
