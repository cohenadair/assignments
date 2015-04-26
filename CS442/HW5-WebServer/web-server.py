#!/usr/bin/python

from collections import namedtuple
from socket import *
import re
import logging
import time
import os
import sys

SOCKET = 7002

RE_FILE = "^.*GET \/(.*) HTTP"
RE_HTTP_VER = "^.*HTTP\/(.{3})"

logging.basicConfig(filename = "log.log", level = logging.DEBUG)

# Reply Header

class HTTPHeader:
    def reset(self):
        self.ver = "1.1"
        self.response = 200
        self.responseDescription = "OK"
        self.contentType = "text/html"
        self.numOfBytes = 0;
        self.dataToSend = ""
        
    def __init__(self):
        self.reset()
        
header = HTTPHeader()

# Utilities

def matchRegex(s, exp):
    match = re.search(exp, s)
    if (match is not None):
        return match.group(1)
    else:
        return ""

def log(data, addr):
    date = time.strftime("%d/%B/%Y:%H:%M:%S") + " -0400"

    get = re.search("GET.*", data)
    if get is not None:
        get = get.group()[:-1]
    else:
        get == ""

    referrer = matchRegex(data, "Referrer: (.*)")
    if referrer != "":
        referrer = referrer[:-1]
    else:
        referrer = ""

    agent = matchRegex(data, "User-Agent: (.*)")[:-1]
    if agent != "":
        agent = agent[:-1]
    else:
        agent = ""

    try:
        msg = ('%s - [%s] %s %d %d %s %s' %
              (addr[0],
               date,
               "" if get == "" else '"' + get + '"',
               header.response,
               header.numOfBytes,
               "" if referrer == "" else '"' + referrer + '"',
               "" if agent == "" else '"' + agent + '"'));
    except:
        pass
    
    logging.info(msg)

def sendData(client):
    try:
        client.send("HTTP/%s %d %s\nContent-Type: %s\n\n" %
                    (header.ver,
                     header.response,
                     header.responseDescription,
                     header.contentType))

        if header.dataToSend != "":
            client.send(header.dataToSend)

        client.send("%s: %s" % (header.response, header.responseDescription))
        
        header.reset()
    except:
        pass

# HTTP Version

def handleHTTPVersion(data, client):
    header.ver = matchRegex(data, RE_HTTP_VER)

# File

def handleFile(data, client):
    path = matchRegex(data, RE_FILE)
    if (not path == ""):
        try:
            sendReply = False
            if path.endswith(".png"):
                mimetype = "image/png"
                sendReply = True
            elif path.endswith(".jpg"):
                mimetype = "image/jpg"
                sendReply = True
            elif path.endswith(".html"):
                mimetype = "text/html"
                sendReply = True
            
            if sendReply:
                f = open(path)
                header.dataToSend = f.read()
                f.close()

                header.contentType = mimetype;
                header.response = 200
                header.responseDescription = "OK"
                header.numOfBytes = os.path.getsize(path)
            else:
                header.response = 415
                header.responseDescription = "Unsupported Media Type"
        except:
            header.response = 404
            header.responseDescription = "File Not Found"
    else:
        header.contentType = "text/html"
        header.response = 200
        header.responseDescription = "OK"

def handleGET(client, addr):
    data = client.recv(4096)
    header = HTTPHeader()
    handleFile(data, client)
    handleHTTPVersion(data, client)
    log(data, addr)

def doAll(client, addr):
    handleGET(client, addr)
    sendData(client)

# Main

def main():
    s = socket()
    s.bind(('localhost', SOCKET))
    s.listen(5)
    while(True):
        c, addr = s.accept()
        pid = os.fork()
        if (pid == 0):
            doAll(c, addr)
            sendReply = True;
            c.close()
            sys.exit(0)
        c.close()

main()
