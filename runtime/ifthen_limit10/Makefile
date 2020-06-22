all: dynamic

dynamic: dynamic.c ../alberi10_all.c
	     gcc -O8 -o dynamic -Wl,--copy-dt-needed-entries -ffast-math -I/fftw/include -L/fftw/lib dynamic.c -lvolk -lm -lfftw3f -fopenmp
