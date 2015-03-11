"""
Python Helper file
CMSC 417: Project 2 
Author: Dylan Zingler
Purpose: Reads CSV files and invokes servers or clients
Date: 3-12-2015

"""

import time
from threading import Thread
import csv
import sys
import subprocess

servers_threads = []
clients_threads = []

# Dictionaries of Info from CSV file
servers_dict = {}
clients_dict = {} 

def read_server_csv(server_csv="./server_csv.csv"):
    #f = open(sys.argv[1], 'rt') ## Good line '''sys.argv[1]'''
    f = open('./servers_csv.csv', 'rt')
    try:
        reader = csv.reader(f)
        for row in reader:
            print row
            servers_dict[row[1]] = row 
    finally:
        f.close()
    
def read_client_csv(client_csv="./client_csv.csv"):    
    #f = open(sys.argv[1], 'rt') ## Good line '''sys.argv[1]'''
    f = open('./clients_csv.csv', 'rt')
    try:
        reader = csv.reader(f)
        for row in reader:
            print row
            clients_dict[row[3]] = row # Key = firstname
    finally:
        f.close()    
 
def runcommand(cmd):
    ''' Runs a command in subprocess'''
    print "THIS JUST FAKE RAN: " + cmd
    #return subprocess.call(cmd)
   
def start_servers():
    
    # each server
    for srvr in servers_dict.keys():
        
        # Command invokes server with port
        command_string = "./server " + servers_dict[srvr][0]        
        
        # Creates thread that runs command
        s = Thread(target=runcommand, args=(command_string,))
        
        # Adds to list of Server Threads
        servers_threads.append(s)
        
        # Starts Thread
        s.start()     
        
def start_clients():
    
    for clnt in clients_dict.keys():
        
        command_string = "./client " + clients_dict[clnt][0] + " " + clients_dict[clnt][1] + " " + clients_dict[clnt][2] + " " + clients_dict[clnt][3] 
                
        # Creates thread that runs command
        c = Thread(target=runcommand, args=(command_string,))
    
        # Adds to list of Client Threads
        clients_threads.append(c)
    
        # Starts Thread
        c.start() 
    
if __name__=="__main__":
    read_server_csv()
    read_client_csv()
    
    print servers_dict
    print clients_dict
    
    start_clients()
    start_servers()
    
    print servers_threads
    print clients_threads