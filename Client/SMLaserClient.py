import socket

SMCommands = {
    "ENABLE" : 1
}
class SMLaserClient:
    def __init__(self, servAddr, port) -> None:
        self.servSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.servSock.connect((servAddr,port))
    
    def send(self, cmd, payload = None):
        print("sending: ",SMCommands[cmd].to_bytes(4,'little'))
        self.servSock.send(SMCommands[cmd].to_bytes(4,'little'))
        if(payload != None):
            self.servSock.send(payload)

cli = SMLaserClient('192.168.0.192',6969)
cli.send("ENABLE",int(111).to_bytes(4,'little'))