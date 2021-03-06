# C++ Implementation of Temporal-Clique

<a href="https://en.wikipedia.org/wiki/Clique_(graph_theory)">*Clique*</a> is a famous graph structure, which could be used to retrieve density-related information from graphs. 

Viard et al. in their paper [Computing maximal cliques in link streams](http://xueshu.baidu.com/s?wd=paperuri%3A%284991a123abacd545d865d8af3fde2718%29&filter=sc_long_sign&tn=SE_xueshusource_2kduw22v&sc_vurl=http%3A%2F%2Fwww.sciencedirect.com%2Fscience%2Farticle%2Fpii%2FS0304397515008701&ie=utf-8&sc_us=8166764464584671087) first introduced the concept of △-clique.

Then Himmel, Anne Sophie, et al. in their paper *"Enumerating Maximal Cliques in Temporal Graphs."* proposed a improved algorithm to mine △-clique.

This project is a C++ implementation for *"Enumerating Maximal Cliques in Temporal Graphs."*

## Quick Start
1. Download and install <a href="https://www.visualstudio.com/downloads/">Visual Studio 2013 or higher version</a>

2. Run the program in VS2013 or cmd

### Input Select
1. Directly input data. The format is  
The first line has two numbers, which means node number and edge number.  
The other line has two labels A and B, which means there is one edge A->B  
3 2  
1 3  
2 3  
      
2. Read test dataset
The dataset has format:   
1     2    
3     222  
29    51  
...  
Each line contains two nodes, representing one edge 1->2.  
  
3. Read a local dataset. Format is the same as 2  

### Parameter Select
Set delta  
delta: the minimum durable time of a clique  

Choose pivoting methods

