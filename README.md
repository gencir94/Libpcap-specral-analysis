# Libpcap-spectral-analysis

This is my Research/Thesis project. This program takes in input a .pcap file and filter it identifying the TCP flows.
We extract the source and destination ip address and the related ports of the syn packets to indentify each flow.
Subsequently, we filter the pcap file with the ip address and the ports saved from every syn packet.
From each flow we extract the packets payload, creating series to take in input to compute the Fast Fourier Transform (FFT).
With this method we can analyse the packets payload frequency of the flow.
To compute the FFT we use a library called "KISS FFT" https://github.com/mborgerding/kissfft .

To compile the file, give 

gcc source.c kiss_fft.c kiss_fftr.c -lm -lpcap
 
