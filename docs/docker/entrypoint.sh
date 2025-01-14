#!/bin/sh

cp /Doxyfile /Doxyfile_copy
echo "OUTPUT_DIRECTORY = /output" >> /Doxyfile_copy

exec "$@"