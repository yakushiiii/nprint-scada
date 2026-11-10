from scapy.all import *
pk=[]
ctl=IP(src="10.0.0.1",dst="10.0.0.2")/TCP(sport=50000,dport=2404,flags="PA")
# I-frame: general interrogation activation: type 100, VSQ 1, COT 6, OA 0, CA 1, IOA 0, QOI 20
i_frame=bytes([0x68,14, 0,0, 0,0, 100,1,6,0, 1,0, 0,0,0, 20])
pk.append(Ether()/ctl/Raw(i_frame))
# S-frame from station
pk.append(Ether()/IP(src="10.0.0.2",dst="10.0.0.1")/TCP(sport=2404,dport=50000,flags="PA")/Raw(bytes([0x68,4,0x01,0,2,0])))
# U-frame STARTDT act
pk.append(Ether()/ctl/Raw(bytes([0x68,4,0x07,0,0,0])))
# GOOSE with VLAN
def tlv(t,v): return bytes([t,len(v)])+v
pdu=(tlv(0x80,b"IED1/LLN0$GO$gcb1")+tlv(0x81,(2000).to_bytes(2,'big'))+tlv(0x82,b"IED1/LLN0$ds1")
     +tlv(0x83,b"goID1")+tlv(0x84,bytes(range(8)))+tlv(0x85,b"\x00\x81")+tlv(0x86,b"\x05")
     +tlv(0x87,b"\x00")+tlv(0x88,b"\x01")+tlv(0x89,b"\x00")+tlv(0x8a,b"\x02")+tlv(0xab,b"\x83\x01\x01\x83\x01\x00"))
g=bytes([0x61,len(pdu)])+pdu
gh=(0x0001).to_bytes(2,'big')+(8+len(g)).to_bytes(2,'big')+b"\x00\x00\x00\x00"+g
pk.append(Ether(src="00:11:22:33:44:55",dst="01:0c:cd:01:00:01",type=0x8100)/Dot1Q(vlan=10,type=0x88b8)/Raw(gh))
# plain UDP
pk.append(Ether()/IP(src="10.0.0.3",dst="10.0.0.4")/UDP(sport=1,dport=2)/Raw(b"hi"))
wrpcap("t.pcap",pk)
