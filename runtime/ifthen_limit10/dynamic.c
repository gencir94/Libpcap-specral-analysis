#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <fftw3.h>
// #include <omp.h>
#include <math.h>
#include <volk/volk.h>
// #include <volk/volk_32fc_magnitude_32f.h>
#include <sched.h>
#include <errno.h>

#define TREES 100
// #define CLASSES  39
#define CLASSES  25
#define MAXFLOWS 100000
#define RUNS 100
#define N 128

float feature[ MAXFLOWS ][ 256 ];
float magnitude[ N ];

/*
int tree_0 ( ) __attribute__((always_inline));
int tree_1 ( ) __attribute__((always_inline));
int tree_2 ( ) __attribute__((always_inline));
int tree_3 ( ) __attribute__((always_inline));
int tree_4 ( ) __attribute__((always_inline));
int tree_5 ( ) __attribute__((always_inline));
int tree_6 ( ) __attribute__((always_inline));
int tree_7 ( ) __attribute__((always_inline));
int tree_8 ( ) __attribute__((always_inline));
int tree_9 ( ) __attribute__((always_inline));
int tree_10 ( ) __attribute__((always_inline));
int tree_11 ( ) __attribute__((always_inline));
int tree_12 ( ) __attribute__((always_inline));
int tree_13 ( ) __attribute__((always_inline));
int tree_14 ( ) __attribute__((always_inline));
int tree_15 ( ) __attribute__((always_inline));
int tree_16 ( ) __attribute__((always_inline));
int tree_17 ( ) __attribute__((always_inline));
int tree_18 ( ) __attribute__((always_inline));
int tree_19 ( ) __attribute__((always_inline));
int tree_20 ( ) __attribute__((always_inline));
int tree_21 ( ) __attribute__((always_inline));
int tree_22 ( ) __attribute__((always_inline));
int tree_23 ( ) __attribute__((always_inline));
int tree_24 ( ) __attribute__((always_inline));
int tree_25 ( ) __attribute__((always_inline));
int tree_26 ( ) __attribute__((always_inline));
int tree_27 ( ) __attribute__((always_inline));
int tree_28 ( ) __attribute__((always_inline));
int tree_29 ( ) __attribute__((always_inline));
int tree_30 ( ) __attribute__((always_inline));
int tree_31 ( ) __attribute__((always_inline));
int tree_32 ( ) __attribute__((always_inline));
int tree_33 ( ) __attribute__((always_inline));
int tree_34 ( ) __attribute__((always_inline));
int tree_35 ( ) __attribute__((always_inline));
int tree_36 ( ) __attribute__((always_inline));
int tree_37 ( ) __attribute__((always_inline));
int tree_38 ( ) __attribute__((always_inline));
int tree_39 ( ) __attribute__((always_inline));
int tree_40 ( ) __attribute__((always_inline));
int tree_41 ( ) __attribute__((always_inline));
int tree_42 ( ) __attribute__((always_inline));
int tree_43 ( ) __attribute__((always_inline));
int tree_44 ( ) __attribute__((always_inline));
int tree_45 ( ) __attribute__((always_inline));
int tree_46 ( ) __attribute__((always_inline));
int tree_47 ( ) __attribute__((always_inline));
int tree_48 ( ) __attribute__((always_inline));
int tree_49 ( ) __attribute__((always_inline));
int tree_50 ( ) __attribute__((always_inline));
int tree_51 ( ) __attribute__((always_inline));
int tree_52 ( ) __attribute__((always_inline));
int tree_53 ( ) __attribute__((always_inline));
int tree_54 ( ) __attribute__((always_inline));
int tree_55 ( ) __attribute__((always_inline));
int tree_56 ( ) __attribute__((always_inline));
int tree_57 ( ) __attribute__((always_inline));
int tree_58 ( ) __attribute__((always_inline));
int tree_59 ( ) __attribute__((always_inline));
int tree_60 ( ) __attribute__((always_inline));
int tree_61 ( ) __attribute__((always_inline));
int tree_62 ( ) __attribute__((always_inline));
int tree_63 ( ) __attribute__((always_inline));
int tree_64 ( ) __attribute__((always_inline));
int tree_65 ( ) __attribute__((always_inline));
int tree_66 ( ) __attribute__((always_inline));
int tree_67 ( ) __attribute__((always_inline));
int tree_68 ( ) __attribute__((always_inline));
int tree_69 ( ) __attribute__((always_inline));
int tree_70 ( ) __attribute__((always_inline));
int tree_71 ( ) __attribute__((always_inline));
int tree_72 ( ) __attribute__((always_inline));
int tree_73 ( ) __attribute__((always_inline));
int tree_74 ( ) __attribute__((always_inline));
int tree_75 ( ) __attribute__((always_inline));
int tree_76 ( ) __attribute__((always_inline));
int tree_77 ( ) __attribute__((always_inline));
int tree_78 ( ) __attribute__((always_inline));
int tree_79 ( ) __attribute__((always_inline));
int tree_80 ( ) __attribute__((always_inline));
int tree_81 ( ) __attribute__((always_inline));
int tree_82 ( ) __attribute__((always_inline));
int tree_83 ( ) __attribute__((always_inline));
int tree_84 ( ) __attribute__((always_inline));
int tree_85 ( ) __attribute__((always_inline));
int tree_86 ( ) __attribute__((always_inline));
int tree_87 ( ) __attribute__((always_inline));
int tree_88 ( ) __attribute__((always_inline));
int tree_89 ( ) __attribute__((always_inline));
int tree_90 ( ) __attribute__((always_inline));
int tree_91 ( ) __attribute__((always_inline));
int tree_92 ( ) __attribute__((always_inline));
int tree_93 ( ) __attribute__((always_inline));
int tree_94 ( ) __attribute__((always_inline));
int tree_95 ( ) __attribute__((always_inline));
int tree_96 ( ) __attribute__((always_inline));
int tree_97 ( ) __attribute__((always_inline));
int tree_98 ( ) __attribute__((always_inline));
int tree_99 ( ) __attribute__((always_inline));
*/

#include "../alberi10_all.c"

int main( int argc, char * * argv ) {

  // Read the command line arguments
  int run_for;
  if ( argc > 2 ) {
    run_for = RUNS;
  } else {
    run_for = 1;
  }
  char filename[ 200 ];
  strcpy( filename,"../flussi_puliti_test_set.csv" );
  if ( argc != 1 ) {
    sscanf( argv[ 1 ], "%s", filename );
  }
  // Set the number of flows

  FILE * fp;
  char label[ 200 ];
  fprintf( stderr, "Reading file: %s\n", filename );
  fp = fopen( filename, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "Can't open input file %s!\n", filename );
    exit( 1 );
  }
  fprintf( stderr, "Main: reading flows\n" );
  int t = 0;
  while ( !feof( fp ) ) {
    if ( t % 10000 == 0 ) fprintf( stderr, "..%d ", t );
    for ( int j = 0; j < 256; j++ ) {
      int bytes = fscanf( fp, "%f\t", &feature[ t ][ j ] );
      if ( bytes != 1 ) fprintf( stderr, "Error at line %d, bytes = %d\n", t, bytes );
    }
    // Read the label
    int bytes = fscanf( fp, "%s\t\n", label );
    if ( bytes == 1 ) t++;
  }
  fprintf( stderr, "Read %d flows.\n", t );
  int TESTFLOWS = t;

  /*
  for ( t = 0; t < TESTFLOWS; t++ ) {
    if ( t % 10000 == 0 ) fprintf( stderr, "..%d ", t );
    for ( int j = 0; j < 256; j++ ) {
      int bytes = fscanf( fp, "%f\t", &feature[ t ][ j ] );
    }
    // Read the label
    int bytes = fscanf( fp, "%s\t\n", label );
  }
  fprintf( stderr, "\n" );
  */

  // Check the priority of this task
  int max_priority_fifo = sched_get_priority_max( SCHED_FIFO );
  int min_priority_fifo = sched_get_priority_min( SCHED_FIFO );
  fprintf( stderr, "max_priority_fifo: %d\n", max_priority_fifo );
  fprintf( stderr, "min_priority_fifo: %d\n", min_priority_fifo );

  int scheduler = sched_getscheduler( 0 );
  fprintf( stderr, "scheduler: %d\n", scheduler );
  fprintf( stderr, "schedulers: SCHED_OTHER %d, SCHED_FIFO %d, SCHED_RR %d\n", SCHED_OTHER, SCHED_FIFO, SCHED_RR );

  struct sched_param parameters;
  parameters.sched_priority = 99;
  int return_value = sched_setscheduler( 0, SCHED_FIFO, &parameters );
  fprintf( stderr, "set sched return: %d\n", return_value );
  fprintf( stderr, "errno: %d\n", errno );
  fprintf( stderr, "errnos: EINVAL %d, EPERM %d, ESRCH %d\n", EINVAL, EPERM, ESRCH );

  scheduler = sched_getscheduler( 0 );
  fprintf( stderr, "scheduler: %d\n", scheduler );

  struct timespec start, done_fft, done_mag, done_tre, done_dec;
  unsigned long long timeElapsed = 0;
  unsigned long long time_cum = 0;

  int decision_aux = 0;
  int final_decision = 0;
  int decisions[ CLASSES ];
  double confidence = 1.0;
  int n_retrain = 0;

  fftwf_complex *in, *out;
  fftwf_plan p;

  in = (fftwf_complex*) fftwf_malloc( sizeof(fftwf_complex) * 256 );
  out = (fftwf_complex*) fftwf_malloc( sizeof(fftwf_complex) * 256 );

  // long long unsigned stats_fft[ TESTFLOWS ][ RUNS ];
  // long long unsigned stats_mag[ TESTFLOWS ][ RUNS ];
  // long long unsigned stats_tre[ TESTFLOWS ][ RUNS ];
  // long long unsigned stats_dec[ TESTFLOWS ][ RUNS ];
  // long long unsigned stats_all[ TESTFLOWS ][ RUNS ];
  fprintf( stderr, "Allocating statistics arrays\n" );
  double * stats_con[ TESTFLOWS ];
  long long unsigned * stats_fft[ TESTFLOWS ];
  long long unsigned * stats_mag[ TESTFLOWS ];
  long long unsigned * stats_tre[ TESTFLOWS ];
  long long unsigned * stats_dec[ TESTFLOWS ];
  long long unsigned * stats_all[ TESTFLOWS ];
  for ( int i = 0; i < TESTFLOWS; i++ ) {
    stats_con[ i ] = (double *) malloc( RUNS * sizeof( double ) );
    stats_fft[ i ] = (long long unsigned *) malloc( RUNS * sizeof( long long unsigned ) );
    stats_mag[ i ] = (long long unsigned *) malloc( RUNS * sizeof( long long unsigned ) );
    stats_tre[ i ] = (long long unsigned *) malloc( RUNS * sizeof( long long unsigned ) );
    stats_dec[ i ] = (long long unsigned *) malloc( RUNS * sizeof( long long unsigned ) );
    stats_all[ i ] = (long long unsigned *) malloc( RUNS * sizeof( long long unsigned ) );
  }

  fprintf( stderr, "Making plan\n" );
  p = fftwf_plan_dft_1d(256, in, out, FFTW_FORWARD, FFTW_MEASURE);
  int result0, result1, result2, result3, result4, result5, result6, result7, result8, result9, result10, result11, result12, result13, result14, result15, result16, result17, result18, result19, result20, result21, result22, result23, result24, result25, result26, result27, result28, result29, result30, result31, result32, result33, result34, result35, result36, result37, result38, result39, result40, result41, result42, result43, result44, result45, result46, result47, result48, result49, result50, result51, result52, result53, result54, result55, result56, result57, result58, result59, result60, result61, result62, result63, result64, result65, result66, result67, result68, result69, result70, result71, result72, result73, result74, result75, result76, result77, result78, result79, result80, result81, result82, result83, result84, result85, result86, result87, result88, result89, result90, result91, result92, result93, result94, result95, result96, result97, result98, result99;

  fprintf( stderr, "Starting runs\n" );
  for ( int k = -1; k < run_for; k++ ) {
  // The first run iteration is a warm up run, we do not store information for
  // statistics
  fprintf( stderr, "doing run iteration %d\n", k );
  n_retrain = 0;
  confidence = 1.0;
  for ( int i = 0; i < TESTFLOWS; i++ ) {

    // Initialize input to FFT
    for ( int ii = 0; ii < 256; ii++ ) {
      in[ ii ][ 0 ] = feature[ i ][ ii ];
    }

    // Take the time
    clock_gettime( CLOCK_MONOTONIC, &start );

    fftwf_execute(p);
    clock_gettime( CLOCK_MONOTONIC, &done_fft );

    // Compute the magnitude
    // for ( int ii = 0; ii < N; ii++ ) {
    //   magnitude[ ii ] = hypotf( out[ ii ][ 0 ], out[ ii ][ 1 ] );
    //   printf( "%f ", magnitude[ ii ] );
    //   // magnitude[ ii ] = sqrt( ( (float) out[ ii ][ 0 ] ) * ((float)out[ ii ][ 1 ]) );
    // }
    // for ( int ii = 0; ii < N; ii++ ) {
    //   magnitude[ ii ] = 0.0;
    // }
    volk_32fc_magnitude_32f( magnitude, out, 128 );
    // printf( "\n" );
    // for ( int ii = 0; ii < N; ii++ ) {
    //   printf( "%f ", magnitude[ ii ] );
    // }
    // printf( "\n" );

    clock_gettime( CLOCK_MONOTONIC, &done_mag );

    // Compute the tree results
    result0 = tree_0();
    result1 = tree_1();
    result2 = tree_2();
    result3 = tree_3();
    result4 = tree_4();
    result5 = tree_5();
    result6 = tree_6();
    result7 = tree_7();
    result8 = tree_8();
    result9 = tree_9();
    result10 = tree_10();
    result11 = tree_11();
    result12 = tree_12();
    result13 = tree_13();
    result14 = tree_14();
    result15 = tree_15();
    result16 = tree_16();
    result17 = tree_17();
    result18 = tree_18();
    result19 = tree_19();
    result20 = tree_20();
    result21 = tree_21();
    result22 = tree_22();
    result23 = tree_23();
    result24 = tree_24();
    result25 = tree_25();
    result26 = tree_26();
    result27 = tree_27();
    result28 = tree_28();
    result29 = tree_29();
    result30 = tree_30();
    result31 = tree_31();
    result32 = tree_32();
    result33 = tree_33();
    result34 = tree_34();
    result35 = tree_35();
    result36 = tree_36();
    result37 = tree_37();
    result38 = tree_38();
    result39 = tree_39();
    result40 = tree_40();
    result41 = tree_41();
    result42 = tree_42();
    result43 = tree_43();
    result44 = tree_44();
    result45 = tree_45();
    result46 = tree_46();
    result47 = tree_47();
    result48 = tree_48();
    result49 = tree_49();
    result50 = tree_50();
    result51 = tree_51();
    result52 = tree_52();
    result53 = tree_53();
    result54 = tree_54();
    result55 = tree_55();
    result56 = tree_56();
    result57 = tree_57();
    result58 = tree_58();
    result59 = tree_59();
    result60 = tree_60();
    result61 = tree_61();
    result62 = tree_62();
    result63 = tree_63();
    result64 = tree_64();
    result65 = tree_65();
    result66 = tree_66();
    result67 = tree_67();
    result68 = tree_68();
    result69 = tree_69();
    result70 = tree_70();
    result71 = tree_71();
    result72 = tree_72();
    result73 = tree_73();
    result74 = tree_74();
    result75 = tree_75();
    result76 = tree_76();
    result77 = tree_77();
    result78 = tree_78();
    result79 = tree_79();
    result80 = tree_80();
    result81 = tree_81();
    result82 = tree_82();
    result83 = tree_83();
    result84 = tree_84();
    result85 = tree_85();
    result86 = tree_86();
    result87 = tree_87();
    result88 = tree_88();
    result89 = tree_89();
    result90 = tree_90();
    result91 = tree_91();
    result92 = tree_92();
    result93 = tree_93();
    result94 = tree_94();
    result95 = tree_95();
    result96 = tree_96();
    result97 = tree_97();
    result98 = tree_98();
    result99 = tree_99();

    clock_gettime( CLOCK_MONOTONIC, &done_tre );

    // Determine the class
    decisions[result0] += 1;
    decisions[result1] += 1;
    decisions[result2] += 1;
    decisions[result3] += 1;
    decisions[result4] += 1;
    decisions[result5] += 1;
    decisions[result6] += 1;
    decisions[result7] += 1;
    decisions[result9] += 1;
    decisions[result9] += 1;
    decisions[result10] += 1;
    decisions[result11] += 1;
    decisions[result12] += 1;
    decisions[result13] += 1;
    decisions[result14] += 1;
    decisions[result15] += 1;
    decisions[result16] += 1;
    decisions[result17] += 1;
    decisions[result19] += 1;
    decisions[result19] += 1;
    decisions[result20] += 1;
    decisions[result21] += 1;
    decisions[result22] += 1;
    decisions[result23] += 1;
    decisions[result24] += 1;
    decisions[result25] += 1;
    decisions[result26] += 1;
    decisions[result27] += 1;
    decisions[result29] += 1;
    decisions[result29] += 1;
    decisions[result30] += 1;
    decisions[result31] += 1;
    decisions[result32] += 1;
    decisions[result33] += 1;
    decisions[result34] += 1;
    decisions[result35] += 1;
    decisions[result36] += 1;
    decisions[result37] += 1;
    decisions[result39] += 1;
    decisions[result39] += 1;
    decisions[result40] += 1;
    decisions[result41] += 1;
    decisions[result42] += 1;
    decisions[result43] += 1;
    decisions[result44] += 1;
    decisions[result45] += 1;
    decisions[result46] += 1;
    decisions[result47] += 1;
    decisions[result49] += 1;
    decisions[result49] += 1;
    decisions[result50] += 1;
    decisions[result51] += 1;
    decisions[result52] += 1;
    decisions[result53] += 1;
    decisions[result54] += 1;
    decisions[result55] += 1;
    decisions[result56] += 1;
    decisions[result57] += 1;
    decisions[result59] += 1;
    decisions[result59] += 1;
    decisions[result60] += 1;
    decisions[result61] += 1;
    decisions[result62] += 1;
    decisions[result63] += 1;
    decisions[result64] += 1;
    decisions[result65] += 1;
    decisions[result66] += 1;
    decisions[result67] += 1;
    decisions[result69] += 1;
    decisions[result69] += 1;
    decisions[result70] += 1;
    decisions[result71] += 1;
    decisions[result72] += 1;
    decisions[result73] += 1;
    decisions[result74] += 1;
    decisions[result75] += 1;
    decisions[result76] += 1;
    decisions[result77] += 1;
    decisions[result79] += 1;
    decisions[result79] += 1;
    decisions[result80] += 1;
    decisions[result81] += 1;
    decisions[result82] += 1;
    decisions[result83] += 1;
    decisions[result84] += 1;
    decisions[result85] += 1;
    decisions[result86] += 1;
    decisions[result87] += 1;
    decisions[result89] += 1;
    decisions[result89] += 1;
    decisions[result90] += 1;
    decisions[result91] += 1;
    decisions[result92] += 1;
    decisions[result93] += 1;
    decisions[result94] += 1;
    decisions[result95] += 1;
    decisions[result96] += 1;
    decisions[result97] += 1;
    decisions[result99] += 1;
    decisions[result99] += 1;
    for ( int y = 0; y < CLASSES; y++ ) {
      if ( decisions[ y ] > decision_aux ) {
        final_decision = y;
        decision_aux = decisions[ y ];
      }
    }
    double probability = ( (double) decision_aux ) / ( (double) TREES );
    confidence = 0.999 * confidence + 0.001 * probability;
    // if ( k >= 0 ) printf( "%f\n", confidence );
    if ( confidence < 0.9 ) {
      n_retrain++;
    }

    clock_gettime( CLOCK_MONOTONIC, &done_dec );

    // Compute the delays
    unsigned long long time_fft = (( done_fft.tv_sec * 1000000000) + done_fft.tv_nsec) - ((start.tv_sec * 1000000000) + start.tv_nsec);
    unsigned long long time_mag = (( done_mag.tv_sec * 1000000000) + done_mag.tv_nsec) - ((done_fft.tv_sec * 1000000000) + done_fft.tv_nsec);
    unsigned long long time_tre = (( done_tre.tv_sec * 1000000000) + done_tre.tv_nsec) - ((done_mag.tv_sec * 1000000000) + done_mag.tv_nsec);
    unsigned long long time_dec = (( done_dec.tv_sec * 1000000000) + done_dec.tv_nsec) - ((done_tre.tv_sec * 1000000000) + done_tre.tv_nsec);
    unsigned long long time_all = (( done_dec.tv_sec * 1000000000) + done_dec.tv_nsec) - ((start.tv_sec * 1000000000) + start.tv_nsec);
    // Output the delays
    /*
    printf( "Dec: %d, ", final_decision );
    printf( "FFT: %lld ns, ", time_fft );
    printf( "MAG: %lld ns, ", time_mag );
    printf( "TREE: %lld ns, ", time_tre );
    printf( "DEC: %lld ns, ", time_dec );
    printf( "TOTAL: %lld ns, ", time_all );
    */
    time_cum += time_all;
    // printf( "Cumulative: %lld ns\n", time_cum );
    if ( k >= 0 ) {
      stats_con[ i ][ k ] = confidence;
      stats_fft[ i ][ k ] = time_fft;
      stats_mag[ i ][ k ] = time_mag;
      stats_tre[ i ][ k ] = time_tre;
      stats_dec[ i ][ k ] = time_dec;
      stats_all[ i ][ k ] = time_all;
    }

    // clean results
    memset( decisions, 0, sizeof(decisions) );
    decision_aux = 0;
  }
  }

  fftwf_destroy_plan(p);


  fftwf_free(in); fftwf_free(out);

  // Compute min, max, average and standard deviation for the execution times of
  // all runs
  double min_con, max_con, mean_con, std_con;
  long long unsigned min_fft, max_fft, mean_fft, std_fft;
  long long unsigned min_mag, max_mag, mean_mag, std_mag;
  long long unsigned min_tre, max_tre, mean_tre, std_tre;
  long long unsigned min_dec, max_dec, mean_dec, std_dec;
  long long unsigned min_all, max_all, mean_all, std_all;

  max_con = stats_con[ 0 ][ 0 ];
  min_con = stats_con[ 0 ][ 0 ];
  max_fft = stats_fft[ 0 ][ 0 ];
  min_fft = stats_fft[ 0 ][ 0 ];
  max_mag = stats_mag[ 0 ][ 0 ];
  min_mag = stats_mag[ 0 ][ 0 ];
  max_tre = stats_tre[ 0 ][ 0 ];
  min_tre = stats_tre[ 0 ][ 0 ];
  max_dec = stats_dec[ 0 ][ 0 ];
  min_dec = stats_dec[ 0 ][ 0 ];
  max_all = stats_all[ 0 ][ 0 ];
  min_all = stats_all[ 0 ][ 0 ];

  for ( int k = 0; k < run_for; k++ ) {
    for ( int i = 0; i < TESTFLOWS; i++ ) {
      if ( max_con < stats_con[i][k] ) { max_con = stats_con[i][k]; }
      if ( min_con > stats_con[i][k] ) { min_con = stats_con[i][k]; }
      if ( max_fft < stats_fft[i][k] ) { max_fft = stats_fft[i][k]; }
      if ( min_fft > stats_fft[i][k] ) { min_fft = stats_fft[i][k]; }
      if ( max_mag < stats_mag[i][k] ) { max_mag = stats_mag[i][k]; }
      if ( min_mag > stats_mag[i][k] ) { min_mag = stats_mag[i][k]; }
      if ( max_tre < stats_tre[i][k] ) { max_tre = stats_tre[i][k]; }
      if ( min_tre > stats_tre[i][k] ) { min_tre = stats_tre[i][k]; }
      if ( max_dec < stats_dec[i][k] ) { max_dec = stats_dec[i][k]; }
      if ( min_dec > stats_dec[i][k] ) { min_dec = stats_dec[i][k]; }
      if ( max_all < stats_all[i][k] ) { max_all = stats_all[i][k]; }
      if ( min_all > stats_all[i][k] ) { min_all = stats_all[i][k]; }

      mean_con += stats_con[i][k];
      mean_fft += stats_fft[i][k];
      mean_mag += stats_mag[i][k];
      mean_tre += stats_tre[i][k];
      mean_dec += stats_dec[i][k];
      mean_all += stats_all[i][k];
    }
  }

  mean_con = mean_con / (TESTFLOWS * run_for);
  mean_fft = mean_fft / (TESTFLOWS * run_for);
  mean_mag = mean_mag / (TESTFLOWS * run_for);
  mean_tre = mean_tre / (TESTFLOWS * run_for);
  mean_dec = mean_dec / (TESTFLOWS * run_for);
  mean_all = mean_all / (TESTFLOWS * run_for);

  for ( int k = 0; k < run_for; k++ ) {
    for ( int i = 0; i < TESTFLOWS; i++ ) {
      std_con += (stats_con[i][k] - mean_con) * (stats_con[i][k] - mean_con);
      std_fft += (stats_fft[i][k] - mean_fft) * (stats_fft[i][k] - mean_fft);
      std_mag += (stats_mag[i][k] - mean_mag) * (stats_mag[i][k] - mean_mag);
      std_tre += (stats_tre[i][k] - mean_tre) * (stats_tre[i][k] - mean_tre);
      std_dec += (stats_dec[i][k] - mean_dec) * (stats_dec[i][k] - mean_dec);
      std_all += (stats_all[i][k] - mean_all) * (stats_all[i][k] - mean_all);
    }
  }

  double std_con_tot = sqrt( std_con / (TESTFLOWS * run_for));
  double std_fft_tot = sqrt( std_fft / (TESTFLOWS * run_for));
  double std_mag_tot = sqrt( std_mag / (TESTFLOWS * run_for));
  double std_tre_tot = sqrt( std_tre / (TESTFLOWS * run_for));
  double std_dec_tot = sqrt( std_dec / (TESTFLOWS * run_for));
  double std_all_tot = sqrt( std_all / (TESTFLOWS * run_for));

  printf( "max con: %f, min con: %fs, ave con: %f, std con: %f, n_retrain: %d\n", max_con, min_con, mean_con, std_con_tot, n_retrain );
  printf( "max fft: %6lld ns, min fft: %5lld ns, ave fft: %4lld ns, std ftt: %5.6f\n", max_fft, min_fft, mean_fft, std_fft_tot );
  printf( "max mag: %6lld ns, min mag: %5lld ns, ave mag: %4lld ns, std mag: %5.6f\n", max_mag, min_mag, mean_mag, std_mag_tot );
  printf( "max tre: %6lld ns, min tre: %5lld ns, ave tre: %4lld ns, std tre: %5.6f\n", max_tre, min_tre, mean_tre, std_tre_tot );
  printf( "max dec: %6lld ns, min dec: %5lld ns, ave dec: %4lld ns, std dec: %5.6f\n", max_dec, min_dec, mean_dec, std_dec_tot );
  printf( "max all: %6lld ns, min all: %5lld ns, ave all: %4lld ns, std all: %5.6f\n", max_all, min_all, mean_all, std_all_tot );

  // Output the confidence curve
  FILE * con_file = fopen( "confidence.data", "w" );
  for ( int i = 0; i < TESTFLOWS; i++ ) {
    fprintf( con_file, "%d %f\n", i, stats_con[ i ][ 0 ] );
  }
  fclose( con_file );

  // Perform a binning process for the statistics of all runs
#define bin_size 1
#define total_bins 30000 / bin_size + 1
  unsigned long long bin_fft[ total_bins ];
  unsigned long long bin_mag[ total_bins ];
  unsigned long long bin_tre[ total_bins ];
  unsigned long long bin_dec[ total_bins ];
  unsigned long long bin_all[ total_bins ];
  // Initialize the arrays
  for ( int k = 0; k < total_bins; k++ ) {
    bin_fft[ k ] = 0;
    bin_mag[ k ] = 0;
    bin_tre[ k ] = 0;
    bin_dec[ k ] = 0;
    bin_all[ k ] = 0;
  }

  for ( int k = 0; k < run_for; k++ ) {
    for ( int i = 0; i < TESTFLOWS; i++ ) {
      unsigned long long bin = stats_fft[ i ][ k ] / bin_size;
      if ( bin < total_bins - 1 ) bin_fft[ bin ]++;
      else bin_fft[ total_bins - 1 ]++;
      bin = stats_mag[ i ][ k ] / bin_size;
      if ( bin < total_bins - 1 ) bin_mag[ bin ]++;
      else bin_mag[ total_bins - 1 ]++;
      bin = stats_tre[ i ][ k ] / bin_size;
      if ( bin < total_bins - 1 ) bin_tre[ bin ]++;
      else bin_tre[ total_bins - 1 ]++;
      bin = stats_dec[ i ][ k ] / bin_size;
      if ( bin < total_bins - 1 ) bin_dec[ bin ]++;
      else bin_dec[ total_bins - 1 ]++;
      bin = stats_all[ i ][ k ] / bin_size;
      if ( bin < total_bins - 1 ) bin_all[ bin ]++;
      else bin_all[ total_bins - 1 ]++;
    }
  }
  // Output the data
  // Probability distribution function of run-times
  FILE * fft_file = fopen( "fft_pdf.data", "w" );
  FILE * mag_file = fopen( "mag_pdf.data", "w" );
  FILE * tre_file = fopen( "tre_pdf.data", "w" );
  FILE * dec_file = fopen( "dec_pdf.data", "w" );
  FILE * all_file = fopen( "all_pdf.data", "w" );
  printf( "Run-time distributions\n" );
  for ( int i = 0; i < total_bins; i++ ) {
    fprintf( fft_file, "%d %8lld\n", i, bin_fft[ i ] );
    fprintf( mag_file, "%d %8lld\n", i, bin_mag[ i ] );
    fprintf( tre_file, "%d %8lld\n", i, bin_tre[ i ] );
    fprintf( dec_file, "%d %8lld\n", i, bin_dec[ i ] );
    fprintf( all_file, "%d %8lld\n", i, bin_all[ i ] );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );
  // Output the same, with values truncated at a limit
  fft_file = fopen( "fft_pdf_truncated.data", "w" );
  mag_file = fopen( "mag_pdf_truncated.data", "w" );
  tre_file = fopen( "tre_pdf_truncated.data", "w" );
  dec_file = fopen( "dec_pdf_truncated.data", "w" );
  all_file = fopen( "all_pdf_truncated.data", "w" );
  long long unsigned limit = 10000;
  for ( int i = 0; i < total_bins; i++ ) {
    if ( bin_fft[ i ] < limit ) fprintf( fft_file, "%d %8lld\n", i, bin_fft[ i ] );
    else fprintf( fft_file, "%d %8lld\n", i, limit );
    if ( bin_mag[ i ] < limit ) fprintf( mag_file, "%d %8lld\n", i, bin_mag[ i ] );
    else fprintf( mag_file, "%d %8lld\n", i, limit );
    if ( bin_tre[ i ] < limit ) fprintf( tre_file, "%d %8lld\n", i, bin_tre[ i ] );
    else fprintf( tre_file, "%d %8lld\n", i, limit );
    if ( bin_dec[ i ] < limit ) fprintf( dec_file, "%d %8lld\n", i, bin_dec[ i ] );
    else fprintf( dec_file, "%d %8lld\n", i, limit );
    if ( bin_all[ i ] < limit ) fprintf( all_file, "%d %8lld\n", i, bin_all[ i ] );
    else fprintf( all_file, "%d %8lld\n", i, limit );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );
  // Output the same using a moving average.
  for ( int maspan = 10; maspan < 110; maspan += 10 ) {
    char fft_str[64];
    char mag_str[64];
    char tre_str[64];
    char dec_str[64];
    char all_str[64];
    sprintf( fft_str, "fft_pdf_ma%d.data", maspan );
    sprintf( mag_str, "mag_pdf_ma%d.data", maspan );
    sprintf( tre_str, "tre_pdf_ma%d.data", maspan );
    sprintf( dec_str, "dec_pdf_ma%d.data", maspan );
    sprintf( all_str, "all_pdf_ma%d.data", maspan );
    fft_file = fopen( fft_str, "w" );
    mag_file = fopen( mag_str, "w" );
    tre_file = fopen( tre_str, "w" );
    dec_file = fopen( dec_str, "w" );
    all_file = fopen( all_str, "w" );
    for ( int i = maspan; i < total_bins; i++ ) {
      double dec_fft = 0;
      double dec_mag = 0;
      double dec_tre = 0;
      double dec_dec = 0;
      double dec_all = 0;
      for ( int k = 0; k < maspan; k++ ) {
        dec_fft += bin_fft[ i - k ];
        dec_mag += bin_mag[ i - k ];
        dec_tre += bin_tre[ i - k ];
        dec_dec += bin_dec[ i - k ];
        dec_all += bin_all[ i - k ];
      }
      dec_fft /= maspan;
      dec_mag /= maspan;
      dec_tre /= maspan;
      dec_dec /= maspan;
      dec_all /= maspan;
      fprintf( fft_file, "%d %f\n", i, dec_fft );
      fprintf( mag_file, "%d %f\n", i, dec_mag );
      fprintf( tre_file, "%d %f\n", i, dec_tre );
      fprintf( dec_file, "%d %f\n", i, dec_dec );
      fprintf( all_file, "%d %f\n", i, dec_all );
    }
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );
  // Also output a truncated version which saturates the numbers to a limit,
  // e.g., 5000
  for ( int maspan = 10; maspan < 110; maspan += 10 ) {
    char fft_str[64];
    char mag_str[64];
    char tre_str[64];
    char dec_str[64];
    char all_str[64];
    sprintf( fft_str, "fft_pdf_ma%d_truncated.data", maspan );
    sprintf( mag_str, "mag_pdf_ma%d_truncated.data", maspan );
    sprintf( tre_str, "tre_pdf_ma%d_truncated.data", maspan );
    sprintf( dec_str, "dec_pdf_ma%d_truncated.data", maspan );
    sprintf( all_str, "all_pdf_ma%d_truncated.data", maspan );
    fft_file = fopen( fft_str, "w" );
    mag_file = fopen( mag_str, "w" );
    tre_file = fopen( tre_str, "w" );
    dec_file = fopen( dec_str, "w" );
    all_file = fopen( all_str, "w" );
    for ( int i = maspan; i < total_bins; i++ ) {
      double dec_fft = 0;
      double dec_mag = 0;
      double dec_tre = 0;
      double dec_dec = 0;
      double dec_all = 0;
      for ( int k = 0; k < maspan; k++ ) {
        dec_fft += bin_fft[ i - k ];
        dec_mag += bin_mag[ i - k ];
        dec_tre += bin_tre[ i - k ];
        dec_dec += bin_dec[ i - k ];
        dec_all += bin_all[ i - k ];
      }
      dec_fft /= maspan;
      dec_mag /= maspan;
      dec_tre /= maspan;
      dec_dec /= maspan;
      dec_all /= maspan;
      double limit = 5000;
      if ( dec_fft > limit ) dec_fft = limit;
      if ( dec_mag > limit ) dec_mag = limit;
      if ( dec_tre > limit ) dec_tre = limit;
      if ( dec_dec > limit ) dec_dec = limit;
      if ( dec_all > limit ) dec_all = limit;
      fprintf( fft_file, "%d %f\n", i, dec_fft );
      fprintf( mag_file, "%d %f\n", i, dec_mag );
      fprintf( tre_file, "%d %f\n", i, dec_tre );
      fprintf( dec_file, "%d %f\n", i, dec_dec );
      fprintf( all_file, "%d %f\n", i, dec_all );
    }
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );

  // Decimated Probability distribution function of run-times
  fft_file = fopen( "fft_pdf_dec.data", "w" );
  mag_file = fopen( "mag_pdf_dec.data", "w" );
  tre_file = fopen( "tre_pdf_dec.data", "w" );
  dec_file = fopen( "dec_pdf_dec.data", "w" );
  all_file = fopen( "all_pdf_dec.data", "w" );
  int decspan = 10;
  for ( int i = decspan; i < total_bins; i += decspan ) {
    long long unsigned dec_fft = 0;
    long long unsigned dec_mag = 0;
    long long unsigned dec_tre = 0;
    long long unsigned dec_dec = 0;
    long long unsigned dec_all = 0;
    for ( int k = 0; k < decspan; k++ ) {
      dec_fft += bin_fft[ i - k ];
      dec_mag += bin_mag[ i - k ];
      dec_tre += bin_tre[ i - k ];
      dec_dec += bin_dec[ i - k ];
      dec_all += bin_all[ i - k ];
    }
    fprintf( fft_file, "%d %8lld\n", i, dec_fft );
    fprintf( mag_file, "%d %8lld\n", i, dec_mag );
    fprintf( tre_file, "%d %8lld\n", i, dec_tre );
    fprintf( dec_file, "%d %8lld\n", i, dec_dec );
    fprintf( all_file, "%d %8lld\n", i, dec_all );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );

  // Build the cumulative curve
  printf( "Cumulative distributions\n" );
  for ( int i = 1; i < total_bins; i++ ) {
    bin_fft[ i ] += bin_fft[ i - 1 ];
    bin_mag[ i ] += bin_mag[ i - 1 ];
    bin_tre[ i ] += bin_tre[ i - 1 ];
    bin_dec[ i ] += bin_dec[ i - 1 ];
    bin_all[ i ] += bin_all[ i - 1 ];
  }
  // Cumulative distribution function
  fft_file = fopen( "fft_cdf.data", "w" );
  mag_file = fopen( "mag_cdf.data", "w" );
  tre_file = fopen( "tre_cdf.data", "w" );
  dec_file = fopen( "dec_cdf.data", "w" );
  all_file = fopen( "all_cdf.data", "w" );
  for ( int i = 0; i < total_bins; i++ ) {
    fprintf( fft_file, "%d %8lld\n", i, bin_fft[ i ] );
    fprintf( mag_file, "%d %8lld\n", i, bin_mag[ i ] );
    fprintf( tre_file, "%d %8lld\n", i, bin_tre[ i ] );
    fprintf( dec_file, "%d %8lld\n", i, bin_dec[ i ] );
    fprintf( all_file, "%d %8lld\n", i, bin_all[ i ] );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );
  // Decimated Cumulative distribution function of run-times
  fft_file = fopen( "fft_cdf_10.data", "w" );
  mag_file = fopen( "mag_cdf_10.data", "w" );
  tre_file = fopen( "tre_cdf_10.data", "w" );
  dec_file = fopen( "dec_cdf_10.data", "w" );
  all_file = fopen( "all_cdf_10.data", "w" );
  for ( int i = 0; i < total_bins; i += 10 ) {
    fprintf( fft_file, "%d %8lld\n", i, bin_fft[ i ] );
    fprintf( mag_file, "%d %8lld\n", i, bin_mag[ i ] );
    fprintf( tre_file, "%d %8lld\n", i, bin_tre[ i ] );
    fprintf( dec_file, "%d %8lld\n", i, bin_dec[ i ] );
    fprintf( all_file, "%d %8lld\n", i, bin_all[ i ] );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );

  // Normalized Cumulative distribution function
  fft_file = fopen( "fft_cdf_norm.data", "w" );
  mag_file = fopen( "mag_cdf_norm.data", "w" );
  tre_file = fopen( "tre_cdf_norm.data", "w" );
  dec_file = fopen( "dec_cdf_norm.data", "w" );
  all_file = fopen( "all_cdf_norm.data", "w" );
  for ( int i = 0; i < total_bins; i++ ) {
    fprintf( fft_file, "%d %f\n", i, ((double) bin_fft[ i ]/(double) TESTFLOWS) );
    fprintf( mag_file, "%d %f\n", i, ((double) bin_mag[ i ]/(double) TESTFLOWS) );
    fprintf( tre_file, "%d %f\n", i, ((double) bin_tre[ i ]/(double) TESTFLOWS) );
    fprintf( dec_file, "%d %f\n", i, ((double) bin_dec[ i ]/(double) TESTFLOWS) );
    fprintf( all_file, "%d %f\n", i, ((double) bin_all[ i ]/(double) TESTFLOWS) );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );
  // Decimated Normalized Cumulative distribution function of run-times
  fft_file = fopen( "fft_cdf_10_norm.data", "w" );
  mag_file = fopen( "mag_cdf_10_norm.data", "w" );
  tre_file = fopen( "tre_cdf_10_norm.data", "w" );
  dec_file = fopen( "dec_cdf_10_norm.data", "w" );
  all_file = fopen( "all_cdf_10_norm.data", "w" );
  for ( int i = 0; i < total_bins; i += 10 ) {
    fprintf( fft_file, "%d %f\n", i, ((double) bin_fft[ i ]/(double) TESTFLOWS) );
    fprintf( mag_file, "%d %f\n", i, ((double) bin_mag[ i ]/(double) TESTFLOWS) );
    fprintf( tre_file, "%d %f\n", i, ((double) bin_tre[ i ]/(double) TESTFLOWS) );
    fprintf( dec_file, "%d %f\n", i, ((double) bin_dec[ i ]/(double) TESTFLOWS) );
    fprintf( all_file, "%d %f\n", i, ((double) bin_all[ i ]/(double) TESTFLOWS) );
  }
  fclose( fft_file );
  fclose( mag_file );
  fclose( tre_file );
  fclose( dec_file );
  fclose( all_file );

  // Compute statistics across runs
  printf( "Output statistics\n" );
  if ( argc > 2 ) {
    // For each metric compute the mean and std deviation for each flow
    for ( int i = 0; i < TESTFLOWS; i++ ) {
      printf( "%d, ", i );
      double average = 0;
      for ( int k = 0; k < run_for; k++ ) {
        average += stats_tre[ i ][ k ];
        printf( "%lld, ", stats_tre[ i ][ k ] );
      }
      // Take the average
      average /= run_for;

      // Normalize the values
      // double normalized[ RUNS ];
      // for ( int k = 0; k < run_for; k++ ) {
      //   normalized[ k ] = ( stats_tre[ i ][ k ] - average ) / average;
      // }
      // Compute standard deviation
      double std = 0;
      for ( int k = 0; k < run_for; k++ ) {
        std += ( stats_tre[ i ][ k ] - average ) * ( stats_tre[ i ][ k ] - average );
      }
      // Take the average
      std = (double) ( ( (double) std ) / ( (double) run_for ) );
      std = sqrt( std );
      // Print it
      printf( "%d, %f, %f, %f\n", i, average, std, std/average );
    }
  }

  return 0;

}
