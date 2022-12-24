import scapy.all as scapy

def main():
    scapy.send(scapy.IP()/scapy.ICMP(id=1, seq=1, unused=1337))

if __name__ == '__main__':
    main()
