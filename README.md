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

# Lecture 06
02-19-2015 Tuesday we had off

## Looking up Address (forwarding tables)
###  Patricia Tree
- Stores prefixes as a tree
- one bit for each level of the tree
- Some nodes correspond to value

### Other Methods
- Can use sp Content Addressable Memories (CAMs)
- Allows Look-ups on a key rather than flat address. 


## DHCP
- Dynamic Host Configuration Protocol

## How do packets reach the end host
- Each interface has a perminent, global identifier

### MAC (Media Access Control) address (48 Bits long)
- Burned into adaptors Read-Only Memory (ROM)
- Flat Address structureff

### Address resolution table
- Mapping MAC address to/from IP address 
- Address Resolution Protocol (ARP)
- Each one also Has an IP

## Routing
- RFC 791
"A name indicates what we seek.
An Address indicates where it is
A route indicates how we get there" - Jon Postel

## Dijkstra (hes my dude. Grandpa of Compsci)
- Use his algorithm across the whole network
- Next you can create a forwarding table for the specific node

### Link-State Routing
#### Each router keeps track of its incident links
- whether the link is up or down
- the cost of the link
#### Each router broadcasts the link state
- To give every router a complete view of the graph
#### Each router runs Dijkstra's algorithm
- To compute the shortest paths
- ...and construct the forwarding table

#### Example Protocols
- Open Shortest Path First (OSPF)
- Intermediate System - Intermediate System(IS-IS)


##### Link State Routing 
- Each router must do the following:
1. Discover its neighbors, learn their network address.
2. Measurethe delay or cost of each of its neighbors
3. Construct a packet telling all it has just learned
4. Send this packet to all other routers
5. Compute the shortest path to every other node




 heartbeat is a periodic signal generated by hardware or software to indicate normal operation or to synchronize other parts of a system

# LIKE 2 Fucking Weeks later. (snow days and missed class)
### it feels like the first day of class again


jitter = varibility between packet arrival times
the higher the jitter, the larger the time buffer before playing it

traffic shaping : controls 

## Packet fragmentation
- 



