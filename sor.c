#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<float.h>



int main(int argc, char** argv) 
{


  FILE *fp, *ofp;
  char *mode = "r";
  char outputFilename[] = "out.csv";

  fp = fopen("merge.arff.csv", mode);

  if (fp == NULL) {
    fprintf(stderr, "Can't open input file in.list!\n");
    exit(1);
  }

  ofp = fopen(outputFilename, "w");

  if (ofp == NULL) {
    fprintf(stderr, "Can't open output file %s!\n",
		            outputFilename);
    exit(1);
  }

  fprintf(ofp,"%s%d ","Peak",0);
  fprintf(ofp,"%s%d","Position",0);
  
  for(int n = 1 ; n<64;n++){
    fprintf(ofp," %s%d %s%d","Peak",n,"Position",n);
  }

  fprintf(ofp,"\n");

  float k[10000][129];
  char l[10000][100];

  for ( int mn = 0; mn < 15; mn++ ) {
   for ( int i = 0 ; i < 10000; i++ ) 
   {
     for(int j = 0; j < 129; j++ ) {
        fscanf(fp,"%f\t",&k[i][j]);
   }

     
  fscanf(fp,"%s\t\n",l[i]);

  float picco[64];
  int indici[64];
  for(int g = 0; g<64;g++) {
    float max = 0;
    int index=0;
    for(int f = 0; f < 129;f++){
	if ( k[i][f] > max ) { 
	    max = k[i][f]; index = f; 
	}
    }
   
  k[i][index] = 0;
  if(index == 0) {k[i][index+1] = 0;}
  else if(index == 128) {k[i][index-1] = 0;}
  else { k[i][index+1] = 0; k[i][index-1] = 0;}
  picco[g] = max;
  indici[g] = index; 
  }

 fprintf(ofp,"%f %d ",picco[0],indici[0]);
 for(int g = 1;g<64;g++){
   fprintf(ofp,"%f %d ",picco[g],indici[g]);
 }
 
 fprintf(ofp,"%s\n",l[i]);
 }

}


}
