# NDN vs. TCP/IP

## Problem statement:
Named Data Networking (NDN) is a proposed data-centric internet architecture. Its premise is that the internet is primarily used as an information distribution network, and hence the users must be allowed to focus on the data, named content, rather than the location from where the data is to be retrieved from, a feature which defines contemporary host-centric architectures like TCP/IP. A quantitative comparison between these two architectures is to be drawn.

## Proposed solution:
A comparison between NDN and TCP/IP will be drawn by simulating both architectures on the same network topologies (e.g. 5x5 grid). Simulation results will be obtained in the form of PCAP (Packet Capture) files, which will be analyzed using a packet analyzer (e.g. Wireshark).

## Technologies used:
ndnSIM - Named Data Networking simulator based on ns-3
NetAnim - Animator for ns-3 simulations
Wireshark - Packet analyzer
R - Language and environment for statistical computing and graphics

## Methodology:
Phase 1: Understanding TCP/IP and NDN concepts  
TCP/IP concepts were covered by referring [1]. NDN concepts were covered by referring [2]. Numerous meetings were held between the mentors and the team members to clarify doubts in these concepts.

Phase 2: Attempt to work on NDN-RTC  
The ideas involved in the development of NDN-RTC were covered by studying [3]. Attempts were then made to install the NDN-RTC library. The process was tedious, and required hours to download. Due to network issues, the download did not complete. It was then decided to move forward with ndnSIM.

Phase 3: Drawing comparisons between NDN and TCP/IP  
ndnSIM was downloaded, compiled, and run by following [4]. NetAnim was installed and configured by following [5]. Different NDN topologies were studied and run by referring [6]. To contrast between NDN and TCP/IP, both architectures were simulated on the same network topologies, and their performances were compared. This comparison was drawn by generating PCAP files for each simulation, and analyzed using Wireshark. To generate PCAP files, the ‘Simple scenario with pcap dump’ section of [6], and the ‘PCAP Tracing’ section of [7] were referred. Furthermore, plots were generated which showed the variation of the rate (in Kbits/s) of the Interest/Data packets forwarded by each node with time, for the NDN example topologies, using R.
## Results:
The simulations of both architectures on the 5x5 grid topology show a difference in the route taken by the packets in each architecture. Following are the screenshots of the simulations:  
<br><br>
  
![ndn-grid Simulation](https://github.com/manasdtrivedi/NDN-vs-TCP-IP/blob/master/Screenshots/NDN/ndn-grid%20simulation.png)
<p align="center">Simulation of ndn-grid</p>  
<br><br>
  
![grid-animation Simulation](https://github.com/manasdtrivedi/NDN-vs-TCP-IP/blob/master/Screenshots/TCP-IP/grid-animation%20simulation.png)
<p align="center">Simulation of grid-animation (TCP/IP)</p>  
<br><br>
  
From the above screenshots, it becomes evident that in NDN, Data packets follow the route which was taken by the corresponding Interest packets, while in TCP/IP, upstream and downstream packets may take different routes based on factors like congestion.

Both simulations were run for a time span of 1.491 s. PCAP files were generated for each simulation, and the following results were obtained upon analyzing these files:

Following are the screenshots of the results:  
<br><br>
  
![](https://github.com/manasdtrivedi/NDN-vs-TCP-IP/blob/master/Screenshots/NDN/ndn-grid%20Capture%20File%20Properties.png)
<p align="center">NDN Simulation Results</p>  
<br><br>
  
![](https://github.com/manasdtrivedi/NDN-vs-TCP-IP/blob/master/Screenshots/TCP-IP/grid-animation%20Capture%20File%20Properties%200-0.png)
<p align="center">TCP/IP Simulation Results</p>  
<br><br>

## Future work:
The initial plan of working with the NDN-RTC library can be resumed, upon resolving network-related issues. Ideas for developing other applications which can use NDN, such as a text-messaging app, can also be worked upon.

## Key Learnings:
The following concepts dealing with the NDN architecture were studied:
1. Interest and Data packets - Sent by a consumer and producer respectively, for the exchange of data across a named data network.
2. Pending Interest Table (PIT): A table present in each NDN router, which stores the Interests which haven’t been satisfied with a corresponding Data packet yet.
3. Forwarding Information Base (FIB): A data structure in each router which contains prefixes and corresponding interfaces for forwarding data,
4. Forwarding Strategy: A module which decides the interface along which an Interest must be forwarded, based on longest-prefix-matching in the FIB.
5. Content Store: A cache of Data packets, which can satisfy incoming Interests.

The following key differences were noted and appreciated between the NDN and TCP/IP architectures:
1. In NDN, Interests are forwarded based on prefix-matching, and Data packets are forwarded along the interface where the Interest came from. There is no requirement of knowing the destination or source of the packets, unlike the IP end-to-end packet delivery model.
2. Address exhaustion, which is a problem in the IP architecture, is not an issue in NDN, since packets are routed and forwarded based on names, which are unbounded.
3. Connections between consumers and producers don’t exist in NDN, since packets are routed and forwarded based on names instead of addresses. This solves the NAT traversal problem faced in TCP/IP.
4. NDN provides a major improvement in privacy protection, compared to IP, as in IP networks, one may analyze packet headers and discover the person/entity consuming the packets, whereas in NDN, only the data in each packet can be examined, and not the destination, since the concept of addressing packets does not exist.
  
## References:  
[1] Kurose, J. & Ross, K., Computer Networking: A Top-Down Approach, 6th ed., Pearson  
[2] [https://named-data.net/publications/named_data_networking_ccr/](https://named-data.net/publications/named_data_networking_ccr/)  
[3] [http://conferences2.sigcomm.org/acm-icn/2015/proceedings/p117-gusev.pdf](http://conferences2.sigcomm.org/acm-icn/2015/proceedings/p117-gusev.pdf)  
[4] [https://ndnsim.net/current/getting-started.html](https://ndnsim.net/current/getting-started.html)  
[5] [https://www.nsnam.org/wiki/NetAnim_3.105](https://www.nsnam.org/wiki/NetAnim_3.105)  
[6] [https://ndnsim.net/current/examples.html](https://ndnsim.net/current/examples.html)  
[7] [https://www.nsnam.org/docs/release/3.9/tutorial/tutorial_23.html](https://www.nsnam.org/docs/release/3.9/tutorial/tutorial_23.html)  
  
## Team:  
Chinmay Gupta      <chinmaygupta61@gmail.com>  
Manas Trivedi		   <manasdtrivedi@gmail.com>  
Paranjay Saxena	   <paranjayasaxena@gmail.com>  
  
#### Mentors:  
Shreyansh Shrivastava  
Tushar Dubey
