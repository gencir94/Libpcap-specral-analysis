all: comb

comb: comb.c ../structure_all.c
	     gcc -O8 -o comb -Wl,--copy-dt-needed-entries -ffast-math -I/fftw/include -L/fftw/lib comb.c -lvolk -lm -lfftw3f -fopenmp
