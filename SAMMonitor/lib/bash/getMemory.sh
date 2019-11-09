#!/bin/bash
#Constants for the data construction
separator=":"
extension=".txt"
file="../results/"$2$extension
prefixPer="%MEM"
prefixBytes="RSS"
prefixCPU="PSR"
suffixBytes="K"
now="date"
#echo "Saving memory of Process: $1"
#Function that get the memory usage percentage
checkMemPer(){
   memoryPer=$(ps -p $1 -o %mem)
   memoryPer=$(echo $memoryPer | sed -e s/^$prefixPer//)
}
#Function that get the memory usage bytes
checkMemBytes(){
   memoryBytes=$(ps -p $1 -o rss)
   memoryBytes=$(echo $memoryBytes | sed -e s/^$prefixBytes//)
}

#Function that get the memory usage bytes
checkCPUId(){
   cpu=$(ps -p $1 -o psr)
   cpu=$(echo $cpu | sed -e s/^$prefixCPU//)
}
checkMAXCPU(){
   max=$(nproc --all)
   max=$(echo $max)
}

#Function that concatenate all the information
checkMem(){
    checkMAXCPU
    checkMemPer $1
    checkMemBytes $1
    checkCPUId $1
    result=$1$separator$memoryBytes$separator$memoryPer$separator$cpu$separator$max$separator$($now)
    echo "$result">>"$file"
}
checkMem $1




