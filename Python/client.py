import socket
import sys

def main():
    s = socket.socket(
        socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('', 21356))

    while(True):
        move = sys.stdin.readline()
        s.send(move)
        stri = s.recv(100)
        print 'Message Received ' + stri

if __name__ == '__main__':
    main()