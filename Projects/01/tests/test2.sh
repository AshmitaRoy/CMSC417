#!/bin/sh          

# Makes code
make

# Reading CSV file
csv_file="./config.csv"
while IFS="," read host port data name
do
    echo "HOST  : $host"
    echo "PORT  : $port"
    echo "DATA  : $data"
    echo "NAME  : $name"
    
    # Run Program with specified variables, pump output to file
    $data | ../p1 $host $port > $name

done < "$csv_file"
