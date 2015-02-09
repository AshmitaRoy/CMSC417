CMSC417 Computer Networks
===========================================

Ashok K. Agrawala
- 4149 avw
- agrawala@cs.umd.edu

TA andrew Pachulski

piazza page


thinking of a network as a computer. 
distances on a computer are very short. but it is the same idea.
moving thinigs back and forth, sometimes through a filter though it is just that.
networks have greater distances


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
