#!/bin/bash
mkdir flat_fs_repo
chown -R flat_fs flat_fs_repo
chmod 700 -R flat_fs_repo

FILE=$1
while IFS=" " read -r -a input; do
	user="${input[0]}"
    useradd $user
    for i in "${input[@]:1}"
    do
    	groupadd $i
    	echo "Added group $i"
    	usermod -a -G $i $user 
    	echo "Added $user to $i"
     done

done < $FILE

