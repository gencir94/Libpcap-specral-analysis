//GENNARO'S MOD ENJOY :)

#define APP_NAME		"sniffex"
#define APP_DESC		"Sniffer example using libpcap"
#define APP_COPYRIGHT	        "Copyright (c) 2005 The Tcpdump Group"
#define APP_DISCLAIMER	        "THERE IS ABSOLUTELY NO WARRANTY FOR THIS PROGRAM."
#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "kiss_fftr.h"
#include <time.h>

#define N 256
#define MAX_FLOWS 10000

//Global variables

int FlowNumber;                     //Flow counter

char ip_matrix [MAX_FLOWS][N];      //Filter flows matrix

int block = 0;                     //Block variable

FILE * a;                           //Output file

char save_ip [1][20];              //save ip address
int save_mac [6];                  //save mac address

float flow_sequence[N];           //save payload sequence
float flow_sequence_INVERSE[N];   //save payload sequence inverse
long  flow_sequence_TIME[N];     //save inter-arrival time sequence

int packet_counter = 0;            //packet counter
int packet_counter_inv = 0;        //packet counter inverse

int list_mac[180] = {0xd0,0x52,0xa8,0x00,0x67,0x5e,0x44,0x65,0x0d,0x56,0xcc,
                     0xd3,0x70,0xee,0x50,0x18,0x34,0x43,0xf4,0xf2,0x6d,0x93,
                     0x51,0xf1,0x00,0x16,0x6c,0xab,0x6b,0x88,0x30,0x8c,0xfb,
                     0x2f,0xe4,0xb2,0x00,0x62,0x6e,0x51,0x27,0x2e,0xe8,0xab,
                     0xfa,0x19,0xde,0x4f,0x00,0x24,0xe4,0x11,0x18,0xa8,0xec,
                     0x1a,0x59,0x79,0xf4,0x89,0x50,0xc7,0xbf,0x00,0x56,0x39,
                     0x74,0xc6,0x3b,0x29,0xd7,0x1d,0xec,0x1a,0x59,0x83,0x28,
                     0x11,0x18,0xb4,0x30,0x25,0xbe,0xe4,0x70,0xee,0x50,0x03,
                     0xb8,0xac,0x00,0x24,0xe4,0x1b,0x6f,0x96,0x74,0x6a,0x89,
                     0x00,0x2e,0x25,0x00,0x24,0xe4,0x20,0x28,0xc6,0xd0,0x73,
                     0xd5,0x01,0x83,0x08,0x18,0xb7,0x9e,0x02,0x20,0x44,0xe0,
                     0x76,0xd0,0x33,0xbb,0x85,0x70,0x5a,0x0f,0xe4,0x9b,0xc0,
                     0x30,0x8c,0xfb,0xb6,0xea,0x45,0x08,0x21,0xef,0x3b,0xfc,
                     0xe3,0x40,0xf3,0x08,0xff,0x1e,0xda,0x74,0x2f,0x68,0x81,
                     0x69,0x42,0xac,0xbc,0x32,0xd4,0x6f,0x2f,0xb4,0xce,0xf6,
                     0xa7,0xa3,0xc2,0xd0,0xa6,0x37,0xdf,0xa1,0xe1,0xf4,0x5c,
                     0x89,0x93,0xcc,0x85};   //MAC address labels

char list_name [30][40] = { "Smart Things","Amazon Echo","Netatmo Welcome",
                            "TP-Link Day Night Cloud camera","Samsung SmartCam",
			    "Dropcam","Insteon Camera","Insteon Camera",
			    "Withings Smart Baby Monitor","Belkin Wemo switch",
			    "TP-Link Smart plug","iHome","Belkin wemo motion sensor",
	                    "NEST Protect smoke alarm","Netatmo weather station",
			    "Withings Smart scale","Blipcare Blood Pressure meter",
			    "Withings Aura smart sleep sensor","Light Bulbs LiFX Smart Bulb",
			    "Triby Speaker","PIX-STAR Photo-frame","HP Printer",
			    "Nest Dropcam","Samsung Galaxy Tab","Android Phone","Laptop",
	                    "MacBook","Android Phone","IPhone","MacBook/Iphone"
	                  }; //Devices names      

/*FFT Config files*/
kiss_fft_scalar in[N];
kiss_fft_cpx out[N / 2 + 1];
kiss_fft_cpx* spectrum;
int spectrumSize;

long NapTime;             //Seconds Timestamp
long NapTime_sec;         //Microseconds Timestamp

int restart = 0;          //Restart Variable
   
  /* default snap length (maximum bytes per packet to capture) */
#define SNAP_LEN 1518

/* ethernet headers are always exactly 14 bytes [1] */ //TROVATO ERRORE, NON SONO 14 MA 16 GENNARO!!
#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

pcap_t *pcap_open_offline(const char *fname, char *errbuf);

/* Ethernet header */
struct sniff_ethernet {
        u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
        u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
        u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* dont fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
        u_short th_sport;               /* source port */
        u_short th_dport;               /* destination port */
        tcp_seq th_seq;                 /* sequence number */
        tcp_seq th_ack;                 /* acknowledgement number */
        u_char  th_offx2;               /* data offset, rsvd */
#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
        u_char  th_flags;
        #define TH_FIN  0x01
        #define TH_SYN  0x02
        #define TH_RST  0x04
        #define TH_PUSH 0x08
        #define TH_ACK  0x10
        #define TH_URG  0x20
        #define TH_ECE  0x40
        #define TH_CWR  0x80
        #define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;                 /* window */
        u_short th_sum;                 /* checksum */
        u_short th_urp;                 /* urgent pointer */
};

void
got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

void
print_payload(const u_char *payload, int len);

void
print_hex_ascii_line(const u_char *payload, int len, int offset);

void
print_app_banner(void);

void
print_app_usage(void);

/*
 * app name/banner
 */
void
print_app_banner(void)
{

	printf("%s - %s\n", APP_NAME, APP_DESC);
	printf("%s\n", APP_COPYRIGHT);
	printf("%s\n", APP_DISCLAIMER);
	printf("\n");

return;
}

/*
 * print help text
 */
void
print_app_usage(void)
{

	printf("Usage: %s [interface]\n", APP_NAME);
	printf("\n");
	printf("Options: \n");
	printf("    interface    Listen on <interface> for packets.\n");
	printf("\n");

return;
}
void print_hex_ascii_line(const u_char *payload, int len, int offset)
{

	int i;
	int gap;
	const u_char *ch;

	/* offset */
	printf("%05d   ", offset);
	
	/* hex */
	ch = payload;
	for(i = 0; i < len; i++) {
		printf("%02x ", *ch);
		ch++;
		/* print extra space after 8th byte for visual aid */
		if (i == 7)
			printf(" ");
	}
	/* print space to handle line less than 8 bytes */
	if (len < 8)
		printf(" ");
	
	/* fill hex gap with spaces if not full line */
	if (len < 16) {
		gap = 16 - len;
		for (i = 0; i < gap; i++) {
			printf("   ");
		}
	}
	printf("   ");
	
	/* ascii (if printable) */
	ch = payload;
	for(i = 0; i < len; i++) {
		if (isprint(*ch))
			printf("%c", *ch);
		else
			printf(".");
		ch++;
	}

	printf("\n");

return;
}
void print_payload(const u_char *payload, int len)
{

	int len_rem = len;
	int line_width = 16;			/* number of bytes per line */
	int line_len;
	int offset = 0;					/* zero-based offset counter */
	const u_char *ch = payload;

	if (len <= 0)
		return;

	/* data fits on one line */
	if (len <= line_width) {
		print_hex_ascii_line(ch, len, offset);
		return;
	}

	/* data spans multiple lines */
	for ( ;; ) {
		/* compute current line length */
		line_len = line_width % len_rem;
		/* print line */
		print_hex_ascii_line(ch, line_len, offset);
		/* compute total remaining */
		len_rem = len_rem - line_len;
		/* shift pointer to remaining bytes to print */
		ch = ch + line_len;
		/* add offset */
		offset = offset + line_width;
		/* check if we have line width chars or less */
		if (len_rem <= line_width) {
			/* print last line and get out */
			print_hex_ascii_line(ch, len_rem, offset);
			break;
		}
	}

return;
}

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{

	static int count = 1;                   /* packet counter */
	/* declare pointers to packet headers */
	const struct sniff_ethernet *ethernet;  /* The ethernet header [1] */
	const struct sniff_ip *ip;              /* The IP header */
	const struct sniff_tcp *tcp;            /* The TCP header */
	const char *payload;                    /* Packet payload */

	int size_ip;
	int size_tcp;
	int size_payload;


	printf("\nPacket number %d: \n", count);
	count++;
	
	/* define ethernet header */
	ethernet = (struct sniff_ethernet*)(packet);
	
	/* define/compute ip header offset */
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length,: %u bytes\n", size_ip);
		return;
	}
	/* print source and destination IP addresses */
	printf("       From,: %s\n", inet_ntoa(ip->ip_src));
	printf("         To,: %s\n", inet_ntoa(ip->ip_dst));

        printf("Destination,: %02x:%02x:%02x:%02x:%02x:%02x\n",
        ethernet->ether_dhost[0], ethernet->ether_dhost[1], ethernet->ether_dhost[2],
        ethernet->ether_dhost[3], ethernet->ether_dhost[4], ethernet->ether_dhost[5]);
        //u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
	/* determine protocol */	
	switch(ip->ip_p) {
		case IPPROTO_TCP:
			printf("   Protocol: TCP\n");
			break;
		case IPPROTO_UDP:
			printf("   Protocol: UDP\n");
			return;
		case IPPROTO_ICMP:
			printf("   Protocol: ICMP\n");
			return;
		case IPPROTO_IP:
			printf("   Protocol: IP\n");
			return;
		default:
			printf("   Protocol: unknown\n");
			return;
	}
	
	/*
	 *  OK, this packet is TCP.
	 */
	
	/* define/compute tcp header offset */
	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}
	
	printf("   Src port: %d\n", ntohs(tcp->th_sport));
	printf("   Dst port: %d\n", ntohs(tcp->th_dport));
    	
	/* define/compute tcp payload (segment) offset */
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	
	/* compute tcp payload (segment) size */
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);
	
	/*
	 * Print payload data; it might be binary, so don't just
	 * treat it as a string.
	 */
	if (size_payload > 0) {
		printf("   Payload (%d bytes):\n", size_payload);
		print_payload(payload, size_payload);
	}
	
	if ( block == 0 ) {
            
	    char* label1 = malloc(30 * sizeof(char));
	    
	    strcpy (label1,"(src port ");	
	    
	    char label3 [20] = {" and dst port "};
	    char label5 [20] = {" and src host "};
            char label2 [20] = { "or (src port "};
	    char label4 [20] = { " and dst port "};
	    char label6 [20] = {" and src host "};
            
	    int conversione = ntohs(tcp->th_sport); 
            int conversione2 = ntohs(tcp->th_dport); 
	   
	    char label7[200];
	    char label8[200];
            
	    sprintf(label7, "%s%d", label1, conversione);
            strcat(label7,label3);
	    
	    char label9[10];
	    
	    sprintf(label9, "%d",conversione2);
            strcat(label7,label9);

	    strcat ( label7, label5 );
            strcat ( label7 , inet_ntoa ( ip->ip_src ) ) ;
            strcat ( label7 , " and dst host ");
            strcat ( label7 , inet_ntoa (ip->ip_dst) );
	    strcat ( label7 , " )" );
            
	    char label10[10];
	    
	    sprintf(label8, "%s%d", label2, conversione2);
	    strcat (label8, label4);
	    sprintf(label10, "%d",conversione);
	    strcat (label8,label10);
	    strcat (label8,label6);
            strcat ( label8 , inet_ntoa (ip->ip_dst) );
            strcat ( label8 , " and dst host ");
            strcat ( label8 , inet_ntoa (ip->ip_src) );
	    strcat ( label8 , ")" );
            strcat ( label7 , label8 );
	    strcpy ( ip_matrix[count] , label7 );
        
	}

	
	if (tcp->th_flags == 2 && block != 0 && restart==0) {
            
	    strcpy(save_ip[0],inet_ntoa(ip->ip_src));
            save_mac[0] = ethernet->ether_shost[0] ;
	    save_mac[1] = ethernet->ether_shost[1] ;
            save_mac[2] = ethernet->ether_shost[2] ;
            save_mac[3] = ethernet->ether_shost[3] ;
            save_mac[4] = ethernet->ether_shost[4] ;
            save_mac[5] = ethernet->ether_shost[5] ;
            
	    restart = 1;
	}
        
	if ( block != 0 && restart == 1 && tcp->th_flags != 2 ) {
	    
	    int re = strcmp(save_ip[0],inet_ntoa(ip->ip_src)) ;
		
	         if ( re == 0 ) {   
		   
			long prima = NapTime;
                        long prima_sec = NapTime_sec;

			NapTime = (header->ts.tv_usec);
			NapTime_sec = (header->ts.tv_sec);

			if (packet_counter == 0) {
			      
			    flow_sequence[packet_counter] = size_payload;
			    flow_sequence_TIME[packet_counter] = 0 ;
                                
			} else {
			      
			    long seconds = NapTime_sec - prima_sec;
			    long micro_seconds = NapTime - prima;
				  
			    if ( micro_seconds < 0 ) { seconds -= 1;}

		            long total_micro_seconds = (seconds * 1000000) + abs(micro_seconds);

		            flow_sequence_TIME[packet_counter] = total_micro_seconds;
			    flow_sequence[packet_counter] = size_payload ;
		                
			}
                                
		  packet_counter++;
		
		  } else {
			        
			 if(packet_counter_inv < 256) {
			        
				flow_sequence_INVERSE[packet_counter] = size_payload;
		                packet_counter_inv++;
		         }
		  }
	        
	     if ( ( tcp->th_flags == 17 )  || ( packet_counter == 256 )  || 
                ( ( packet_counter_inv == 256 ) && ( packet_counter > 128 ) ) ) {
                
		int lock = 0;
		int jj,kk;
	        float salva[256];
                long salva_tempo[256];

		for (jj = 0; jj < 256; jj++) {
		   salva[jj] = 0;
                } 

		
               	for ( jj = 0; jj < 256; jj++ ) {
                   if ( flow_sequence[jj] > 0 ) {
		      lock = 1; 
		      break;
		  }
		}
                
		if ( lock == 0 ) {
	            for ( jj = 0; jj < 256; jj++ ) {
                          if ( flow_sequence_INVERSE[jj] > 0 ) {
				  lock = 2; 
				  break;
			  }
		    }
		}
		if ( lock == 0 ) {
	            for ( jj = 0; jj < 256; jj++ ) {
                          if ( flow_sequence_TIME[jj] > 0 ) {
			          if(packet_counter > 10) {	  
				    lock = 3;
				  } 
		          break;
			  
			  }
		    }
		}
		
	        if ( lock == 1 ) {
		    
		    int i;
		    for(i = 0; i < 256; i++){
			in[i] = flow_sequence[i];
			salva[i] = flow_sequence[i];
			salva_tempo[i] = flow_sequence_TIME[i];
			flow_sequence[i] = 0;
			flow_sequence_INVERSE[i] = 0;
			flow_sequence_TIME[i] = 0;
		    
		    }
		 
		}else if (lock == 2) {
		    
	            int i;
		    for(i = 0; i < 256; i++){
			in[i] = flow_sequence_INVERSE[i];
			salva_tempo[i] = flow_sequence_TIME[i];
			salva[i] = flow_sequence_INVERSE[i];
			flow_sequence[i] = 0;
			flow_sequence_TIME[i] = 0;
			flow_sequence_INVERSE[i] = 0;
		    }
                
		} else {
		    int i;
		    for (i = 0; i < 256; i++) {
			in[i] = flow_sequence_TIME[i];
			salva[i] = flow_sequence_TIME[i];
			salva_tempo[i] = flow_sequence_TIME[i];
			flow_sequence[i] = 0;
			flow_sequence_TIME[i] = 0;
			flow_sequence_INVERSE[i] = 0;
		    }
                   
		}
               
		if ( (lock == 1 ) || ( lock == 2 ) || (lock == 3 ) ) { 
	        
	          spectrum = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx) * N);
                  spectrumSize = N/2+1;
                  kiss_fftr_cfg cfg;
         	  float mags[N];
                  if ((cfg = kiss_fftr_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
                  {
	            kiss_fftr(cfg, in, out);
                    free(cfg);
                    int i; 
		    for(i = 0; i < N / 2 + 1; i++) {
                     mags[i] = hypotf(out[i].r,out[i].i);
                  }
	       
	          for(i = 0;i < N / 2 + 1; i++){
                     fprintf(a,", %f",mags[i]);
	          } 

	          } 
	       	
		for (kk = 0 ; kk < 180; kk = kk + 6 ) {
                    
		     if ( save_mac[0] == list_mac[kk] && save_mac[1] == list_mac[kk+1] && 
		        save_mac[2] == list_mac[kk+2] && save_mac[3] == list_mac[kk+3] &&
		        save_mac[4] == list_mac[kk+4] && save_mac[5] == list_mac[kk+5] ) {
		 
                        if ( (kk == 174) || (kk == 168) || (kk == 162) || (kk == 156) || 
                             (kk == 150) || (kk == 144) || (kk == 138) ) {
		         	 fprintf(a,", %s frequency","NON_IOT");
		        }else {
		      	         fprintf(a,", %s frequency",list_name[kk/6]);
                        }
                     }
		}
                
                fprintf(a,"\n");
	    
	       }
	       
		packet_counter = 0;
		packet_counter_inv = 0;
		
		if(tcp->th_flags == 17){
		  restart = 0;
		}

	   }
   }
	FlowNumber = count;

	return;
}


/*Main function*/

int main(int argc, char *argv[]) {

   a = fopen ("flussi.csv","w");
   
   char *device; /* Name of device (e.g. eth0, wlan0) */
   char error_buffer[PCAP_ERRBUF_SIZE];
   pcap_t *handle = pcap_open_offline(argv[1], error_buffer);
   
   u_char *my_arguments = NULL;
   struct bpf_program fp;	/* The compiled filter expression */

   char filter_exp[] = "tcp[tcpflags] & tcp-syn == tcp-syn and tcp[tcpflags] & tcp-ack != tcp-ack";	/* The filter expression */
   
   bpf_u_int32 net;		/* The IP of our sniffing device */
   const u_char *packet;	/* The actual packet */
   struct pcap_pkthdr header;	/* The header that pcap gives us */

   if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		 fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		 return(2);
	 }
   if (pcap_setfilter(handle, &fp) == -1) {
		 fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		 return(2);
	 }

   pcap_loop(handle, -1, got_packet, my_arguments);

   block++;

   char** copy;
   copy = malloc((FlowNumber+1)*sizeof(char*));
  
   int iter;
   for ( iter = 0; iter < FlowNumber; iter++ ) {
       copy[iter] = malloc(N*sizeof(char));
   }
  
   strcpy ( copy[0] , ip_matrix[2] ) ;
  
   int i,j,l = 0;
   int k = 1;
   
   for (j = 2; j < FlowNumber + 1; j++ ) {
      
      for ( l = 0; l < k ; l++ ) {
         
	      int re = strcmp ( copy[l] , ip_matrix[j] ) ;
    	      if(re == 0) { break; }
	      
	      else if ( l == k - 1 ) {
	              
		      strcpy(copy[k],ip_matrix[j]); 
	              k++; 
		      break;

	      }
       }
   
   }

   char* filter_exp_2 = malloc(N * sizeof(char));

   for(i = 0; i < k; i++) {
    
     strcpy(filter_exp_2,copy[i]);
     handle = pcap_open_offline(argv[1], error_buffer);

     if (pcap_compile(handle, &fp, filter_exp_2, 0, net) == -1) {
		 fprintf(stderr, "Couldn't parse filter %s : %s\n", filter_exp_2, pcap_geterr(handle));
		 return(2);
	 }
     if (pcap_setfilter(handle, &fp) == -1) {
			fprintf(stderr, "Couldn't install filter %s : %s\n", filter_exp_2, pcap_geterr(handle));
			return(2);
		}
  
     pcap_loop(handle, -1, got_packet, my_arguments);

     pcap_freecode(&fp);  /*Free memory*/
     pcap_close(handle);  /*Free memory*/
   
     packet_counter = 0;
     packet_counter_inv = 0;

  } 

}
	


