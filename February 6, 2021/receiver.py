import socket
import time

host = "192.168.4.1"
port = 5555

sock = socket.socket()

sock.connect((host, port))

correctPayLoad = [0, 0, 16384, 0]


while True:
##for x in range(50):
    data = "";
    payLoad = []
    payLoadNo = 0
    isPayLoadGood = False
    correctPayLoadValues = 0
    
    while(len(data) < 128):
        data += sock.recv(1).decode("UTF-8")

    payLoad = data.split('\n')

    while not isPayLoadGood:
        try:
            if (len(payLoad[payLoadNo].split(' ')) == 4):
                for x in payLoad:
                    try:
                        int(x)
                        correctPayLoadValues += 1
                    except Exception as ex:
                        payLoadNo += 1
                        break
                if correctPayLoadValues == 4:
                    correctPayLoad = payLoad[payLoadNo]
                    isPayLoadGood = True
            else:
                payLoadNo += 1
            
        except Exception as ex:
            break

    
    print(correctPayLoad)
