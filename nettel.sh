#!/bin/bash
echo "Ecris la commande a rentrer :"
read command
echo -n $command > log_files/last_input
echo -n " HTTP/1.0" > log_files/last_input
echo -e -n "\r\n\r\n" > log_files/last_input
telnet localhost 80 > log_files/log80 < log_files/last_input
telnet localhost 18000 > log_files/log18000 < log_files/last_input

