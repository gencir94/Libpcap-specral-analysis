all: parallel

parallel: parallel.c
	     gcc -O8 -o parallel -pthread -Wl,--copy-dt-needed-entries -ffast-math -I/fftw/include -L/fftw/lib parallel.c -lvolk -lm -lfftw3f -fopenmp
