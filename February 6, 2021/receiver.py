import socket

host = "192.168.4.1"
port = 5555

sock = socket.socket()

sock.connect((host, port))

while True:
    data = ""
    payloadList = []
    
    while(len(data) < 128):
        data += sock.recv(1).decode("UTF-8")

    payloadList = data.split('\n')

    for payload in payloadList:
        try:
            #test if payload is complete
            ax = payload.split(' ')[0]
            ay = payload.split(' ')[1]
            az = payload.split(' ')[2]
            s = payload.split(' ')[3]

            try:
                #test each value if it is integer
                int(ax)
                int(ay)
                int(az)
                int(s)
            
                print(ax, ay, az, s)
            except:
                #print("payload not integer")
                continue
        except:
            #print("incomplete payload")
            continue
