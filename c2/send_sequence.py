import scapy.all as scapy

def main():
    scapy.send(scapy.IP()/scapy.ICMP(id=1, seq=1, unused=0x4141))

if __name__ == '__main__':
    main()
