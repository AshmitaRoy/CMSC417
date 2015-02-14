CMSC417 Computer Networks
===========================================

Ashok K. Agrawala
- 4149 avw
- agrawala@cs.umd.edu
- http://www.cs.umd.edu/class/spring2015/cmsc417/
TA andrew Pachulski

piazza page


thinking of a network as a computer. 
distances on a computer are very short. but it is the same idea.
moving thinigs back and forth, sometimes through a filter though it is just that.
networks have greater distances

![Memory Sizes](https://mandalaygazette.com/wp-content/uploads/2014/01/prefixestableel3.jpg)


## course expectations
understande network protocols
- protocol layering, basic medium access including wireless protocols, routing, addtessing, congestion control
- understand principals behind the internet protocols and some application layer protocols such as http, ftp, and DNS, and a few peer-to-peer systems protocols such as Gnutella and Chord
- understand some of the limitations of the current internet and its service model
- Understand the causes behind network congestion, and explain the basic methods for alleviating congestion
- Design, implement, and test substantial parts of the network


## Books



tcp/ip sockets in c: 2nd edition

computer networks 5th edition


## Computer networking
- Computer Bus: is a communication system that transfers data between components inside a computer, or between computers. This expression covers all related hardware components (wire, optical fiber, etc.) and software, including communication protocols.

- most of the time in connections over internet are made by serial connections. 


### uses of networks
- Networks are a collection of autonomous computers
- many uses
 - business applications
 - home applications
 - mobile users
- they raise social uses

#### Business applications
- client server model, resource sharing
- email, VoIP, and e-commerce
![](http://clientservicesupport.com/wp-content/uploads/2014/11/11fig01.jpg)

#### Home applications
- Homes contain many networked devices, computers tvs etc
- social networks

#### Mobile Users
- Tablets, laptops, smart phones are popular devices; wifi, 3g cellular provide wireless connectivity
- Mobile users communicate via voice text consume conent, video and web, and use sensors


# Lecture 02
02-03-2015


## Reference Models
![](http://1.bp.blogspot.com/-XxGg1fOQ-mo/T8zFKiUiNcI/AAAAAAAAB1o/EXDIjbc1QuU/s1600/OSI-TCP.png)
![](http://3.bp.blogspot.com/_wH4q7agRmuY/SwWKBPIHUhI/AAAAAAAAAG8/mg9xDu3ICrw/s1600/TCP+IP1.bmp)

# Lecture 03
02-05-2015

## Clients are not always humans
- Ex Spider client
- Ex Web Crawler (or spider)

## Server side
- Always on
- Needs address
- need to know the service process (address)

- sending data
    - ssize_twrite(int sock ...
- Receving data
    - ssize_tread(int sock ...
- Closing the socket 
    - int close(int
    
# Lecture 03
02-10-2015



# Lecture 04
02-12-2015

##IP Packet Structure
![IP Packet Structure](http://www.eg.bucknell.edu/~cs363/2014-spring/labs/ip-pkt-header.jpg)
-IP packet size 2^16 bytes of payload, 64 Gig!
- Fragmentation Info (32bits) (Splits packet into smaller ones, in case the link cannot handle large ones, this is transparent to the end computer)
 - Packet identifier, flags, and fragement offset
 - supports dividing a large IP packet into fragments
 - ... in case a link cannot hande a large IP packet
- Time-To-Live(TTL  - 8bits)
 - Used to identify packets stuck in forwarding loops
 - ...and eventually discard them from the network.
 - Each router along the path decrements the TTL
 - "TTL exceeded" sent when TTL reaches 0.
- Protocol (8bits)
 - identifies the higher-level protocol
  - eg. 6 for TCP (Transmission Control Protocol)
  - eg 17 for UDP (User Datagram Protocol)
- Checksum (16 bits)
 - Sum of all 16-bit words in the IP packet header
 - if any bits of the header are corrupted in transit
 - ..the check sum won't match at receiving host
- Two IP Addresses
 - Source IP address (32bits)
  - Unique identifier for the sending host
  - Recipient can decide wheither to accept the packet
  - Enables recipiant to send a reply back to source
 - Destination Address (32bits)
  - Unique identifier for the receving host 
  - allows each node to make forwarding decisions. 
 
### Are 32-bit address enough
- not all that many unique addresses
 - 2^32 = 4,294,967,296 (just over four billion)
 - Plus, some reserved for special purposes
 - and, addresses are allocated in larger blocks
- And many devices need IP addresses
 - Computers, PDA's, routers, tanks, toasters
- Long-term solution: a larger address space
 - IPv6 has 128-bit addresses
  
## Hop-by-hop Packet Forwarding
- Each router has a forwarding table
 - maps destination addresses to outgoing interfaces
## 
