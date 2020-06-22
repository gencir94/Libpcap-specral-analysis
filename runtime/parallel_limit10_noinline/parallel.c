#include <pthread.h>
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
#include <locale.h>

#define TREES 100
#define CLASSES  39
#define MAXFLOWS 100000
#define RUNS 100
#define N 128

float feature[ MAXFLOWS ][ 256 ];

#include "../alberi10_mag_all.c"

// Declare the thread barriers for synchronization
pthread_barrier_t start_barrier;
pthread_barrier_t end_barrier;
// Data structure to be passed to the workers
struct instructions {
  int id;
  int start_index;
  int end_index;
};
// Mutex for the FFT planner
pthread_mutex_t mutex1;

double confidence = 1.0;
int n_retrain = 0;

void * worker1( void * t ) {

  int result0, result1, result2, result3, result4, result5, result6, result7, result8, result9, result10, result11, result12, result13, result14, result15, result16, result17, result18, result19, result20, result21, result22, result23, result24, result25, result26, result27, result28, result29, result30, result31, result32, result33, result34, result35, result36, result37, result38, result39, result40, result41, result42, result43, result44, result45, result46, result47, result48, result49, result50, result51, result52, result53, result54, result55, result56, result57, result58, result59, result60, result61, result62, result63, result64, result65, result66, result67, result68, result69, result70, result71, result72, result73, result74, result75, result76, result77, result78, result79, result80, result81, result82, result83, result84, result85, result86, result87, result88, result89, result90, result91, result92, result93, result94, result95, result96, result97, result98, result99;
  int decision_aux = 0;
  int final_decision = 0;
  int decisions[ CLASSES ];
  float magnitude[ N ];

  struct instructions * my_t = (struct instructions *) t;
  int id = my_t->id;
  int start_index = my_t->start_index;
  int end_index = my_t->end_index;
  fprintf( stderr, "Thread %d, start_index = %d, end_index: %d\n", id, start_index, end_index );

  // What does a worker do? It will get the data, run the FFT, take the
  // magnitude, run the trees, take a decision, and then restarts with new data.

  // Create the data structures to run the FFT computation
  fftwf_complex * in, * out;
  fftwf_plan p;

  in = (fftwf_complex *) fftwf_malloc( sizeof( fftwf_complex ) * 256 );
  out = (fftwf_complex *) fftwf_malloc( sizeof( fftwf_complex ) * 256 );

  // fprintf( stderr, "Thread %d, making plan\n", id );
  pthread_mutex_lock( &mutex1 );
  p = fftwf_plan_dft_1d( 256, in, out, FFTW_FORWARD, FFTW_MEASURE );
  pthread_mutex_unlock( &mutex1 );
  // fprintf( stderr, "Thread %d, plan done\n", id );

  // Wait for work to do in a loop forever
  while ( 1 ) {

    // fprintf( stderr, "Thread %d, waiting to start\n", id );
    pthread_barrier_wait( &start_barrier );
    // fprintf( stderr, "Thread %d, triggered\n", id );

    // Do all the flows
    for ( int flow_index = start_index; flow_index < end_index; flow_index++ ) {

      // clean results
      memset( decisions, 0, sizeof(decisions) );
      decision_aux = 0;

      // Initialize input to FFT
      for ( int ii = 0; ii < 256; ii++ ) {
        in[ ii ][ 0 ] = feature[ flow_index ][ ii ];
        // fprintf( stderr, "Thread %d, feature[ %d ][ %d ] = %f\n", id, flow_index, ii, feature[ flow_index ][ ii ] );
      }

      // Execute the FFT
      fftwf_execute( p );

      // Take the magnitude
      volk_32fc_magnitude_32f( magnitude, out, 128 );

      // Run the trees
      result0 = tree_0( magnitude );
      result1 = tree_1( magnitude );
      result2 = tree_2( magnitude );
      result3 = tree_3( magnitude );
      result4 = tree_4( magnitude );
      result5 = tree_5( magnitude );
      result6 = tree_6( magnitude );
      result7 = tree_7( magnitude );
      result8 = tree_8( magnitude );
      result9 = tree_9( magnitude );
      result10 = tree_10( magnitude );
      result11 = tree_11( magnitude );
      result12 = tree_12( magnitude );
      result13 = tree_13( magnitude );
      result14 = tree_14( magnitude );
      result15 = tree_15( magnitude );
      result16 = tree_16( magnitude );
      result17 = tree_17( magnitude );
      result18 = tree_18( magnitude );
      result19 = tree_19( magnitude );
      result20 = tree_20( magnitude );
      result21 = tree_21( magnitude );
      result22 = tree_22( magnitude );
      result23 = tree_23( magnitude );
      result24 = tree_24( magnitude );
      result25 = tree_25( magnitude );
      result26 = tree_26( magnitude );
      result27 = tree_27( magnitude );
      result28 = tree_28( magnitude );
      result29 = tree_29( magnitude );
      result30 = tree_30( magnitude );
      result31 = tree_31( magnitude );
      result32 = tree_32( magnitude );
      result33 = tree_33( magnitude );
      result34 = tree_34( magnitude );
      result35 = tree_35( magnitude );
      result36 = tree_36( magnitude );
      result37 = tree_37( magnitude );
      result38 = tree_38( magnitude );
      result39 = tree_39( magnitude );
      result40 = tree_40( magnitude );
      result41 = tree_41( magnitude );
      result42 = tree_42( magnitude );
      result43 = tree_43( magnitude );
      result44 = tree_44( magnitude );
      result45 = tree_45( magnitude );
      result46 = tree_46( magnitude );
      result47 = tree_47( magnitude );
      result48 = tree_48( magnitude );
      result49 = tree_49( magnitude );
      result50 = tree_50( magnitude );
      result51 = tree_51( magnitude );
      result52 = tree_52( magnitude );
      result53 = tree_53( magnitude );
      result54 = tree_54( magnitude );
      result55 = tree_55( magnitude );
      result56 = tree_56( magnitude );
      result57 = tree_57( magnitude );
      result58 = tree_58( magnitude );
      result59 = tree_59( magnitude );
      result60 = tree_60( magnitude );
      result61 = tree_61( magnitude );
      result62 = tree_62( magnitude );
      result63 = tree_63( magnitude );
      result64 = tree_64( magnitude );
      result65 = tree_65( magnitude );
      result66 = tree_66( magnitude );
      result67 = tree_67( magnitude );
      result68 = tree_68( magnitude );
      result69 = tree_69( magnitude );
      result70 = tree_70( magnitude );
      result71 = tree_71( magnitude );
      result72 = tree_72( magnitude );
      result73 = tree_73( magnitude );
      result74 = tree_74( magnitude );
      result75 = tree_75( magnitude );
      result76 = tree_76( magnitude );
      result77 = tree_77( magnitude );
      result78 = tree_78( magnitude );
      result79 = tree_79( magnitude );
      result80 = tree_80( magnitude );
      result81 = tree_81( magnitude );
      result82 = tree_82( magnitude );
      result83 = tree_83( magnitude );
      result84 = tree_84( magnitude );
      result85 = tree_85( magnitude );
      result86 = tree_86( magnitude );
      result87 = tree_87( magnitude );
      result88 = tree_88( magnitude );
      result89 = tree_89( magnitude );
      result90 = tree_90( magnitude );
      result91 = tree_91( magnitude );
      result92 = tree_92( magnitude );
      result93 = tree_93( magnitude );
      result94 = tree_94( magnitude );
      result95 = tree_95( magnitude );
      result96 = tree_96( magnitude );
      result97 = tree_97( magnitude );
      result98 = tree_98( magnitude );
      result99 = tree_99( magnitude );

      // Determine the class
      decisions[ result0 ] += 1;
      decisions[ result1 ] += 1;
      decisions[ result2 ] += 1;
      decisions[ result3 ] += 1;
      decisions[ result4 ] += 1;
      decisions[ result5 ] += 1;
      decisions[ result6 ] += 1;
      decisions[ result7 ] += 1;
      decisions[ result9 ] += 1;
      decisions[ result9 ] += 1;
      decisions[ result10 ] += 1;
      decisions[ result11 ] += 1;
      decisions[ result12 ] += 1;
      decisions[ result13 ] += 1;
      decisions[ result14 ] += 1;
      decisions[ result15 ] += 1;
      decisions[ result16 ] += 1;
      decisions[ result17 ] += 1;
      decisions[ result19 ] += 1;
      decisions[ result19 ] += 1;
      decisions[ result20 ] += 1;
      decisions[ result21 ] += 1;
      decisions[ result22 ] += 1;
      decisions[ result23 ] += 1;
      decisions[ result24 ] += 1;
      decisions[ result25 ] += 1;
      decisions[ result26 ] += 1;
      decisions[ result27 ] += 1;
      decisions[ result29 ] += 1;
      decisions[ result29 ] += 1;
      decisions[ result30 ] += 1;
      decisions[ result31 ] += 1;
      decisions[ result32 ] += 1;
      decisions[ result33 ] += 1;
      decisions[ result34 ] += 1;
      decisions[ result35 ] += 1;
      decisions[ result36 ] += 1;
      decisions[ result37 ] += 1;
      decisions[ result39 ] += 1;
      decisions[ result39 ] += 1;
      decisions[ result40 ] += 1;
      decisions[ result41 ] += 1;
      decisions[ result42 ] += 1;
      decisions[ result43 ] += 1;
      decisions[ result44 ] += 1;
      decisions[ result45 ] += 1;
      decisions[ result46 ] += 1;
      decisions[ result47 ] += 1;
      decisions[ result49 ] += 1;
      decisions[ result49 ] += 1;
      decisions[ result50 ] += 1;
      decisions[ result51 ] += 1;
      decisions[ result52 ] += 1;
      decisions[ result53 ] += 1;
      decisions[ result54 ] += 1;
      decisions[ result55 ] += 1;
      decisions[ result56 ] += 1;
      decisions[ result57 ] += 1;
      decisions[ result59 ] += 1;
      decisions[ result59 ] += 1;
      decisions[ result60 ] += 1;
      decisions[ result61 ] += 1;
      decisions[ result62 ] += 1;
      decisions[ result63 ] += 1;
      decisions[ result64 ] += 1;
      decisions[ result65 ] += 1;
      decisions[ result66 ] += 1;
      decisions[ result67 ] += 1;
      decisions[ result69 ] += 1;
      decisions[ result69 ] += 1;
      decisions[ result70 ] += 1;
      decisions[ result71 ] += 1;
      decisions[ result72 ] += 1;
      decisions[ result73 ] += 1;
      decisions[ result74 ] += 1;
      decisions[ result75 ] += 1;
      decisions[ result76 ] += 1;
      decisions[ result77 ] += 1;
      decisions[ result79 ] += 1;
      decisions[ result79 ] += 1;
      decisions[ result80 ] += 1;
      decisions[ result81 ] += 1;
      decisions[ result82 ] += 1;
      decisions[ result83 ] += 1;
      decisions[ result84 ] += 1;
      decisions[ result85 ] += 1;
      decisions[ result86 ] += 1;
      decisions[ result87 ] += 1;
      decisions[ result89 ] += 1;
      decisions[ result89 ] += 1;
      decisions[ result90 ] += 1;
      decisions[ result91 ] += 1;
      decisions[ result92 ] += 1;
      decisions[ result93 ] += 1;
      decisions[ result94 ] += 1;
      decisions[ result95 ] += 1;
      decisions[ result96 ] += 1;
      decisions[ result97 ] += 1;
      decisions[ result99 ] += 1;
      decisions[ result99 ] += 1;
      for ( int y = 0; y < CLASSES; y++ ) {
        if ( decisions[ y ] > decision_aux ) {
          final_decision = y;
          decision_aux = decisions[ y ];
        }
      }
      double probability = ( (double) decision_aux ) / ( (double) TREES );
      // TODO: confidence should be a shared variable
      // fprintf( stderr, "Thread %d, decision_aux: %d, probability %f, confidence: %f\n", id, decision_aux, probability, confidence );
      pthread_mutex_lock( &mutex1 );
      confidence = 0.999 * confidence + 0.001 * probability;
      // if ( k >= 0 ) printf( "%f\n", confidence );
      if ( confidence < 0.9 ) {
        n_retrain++;
      }
      pthread_mutex_unlock( &mutex1 );
      // Go on to the next flow
    }

    pthread_barrier_wait( &end_barrier );

  }
  pthread_exit( NULL );
}

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

int main( int argc, char * * argv ) {

  // Read the command line arguments
  int run_for;
  if ( argc > 3 ) {
    run_for = RUNS;
  } else {
    run_for = 1;
  }

  struct timespec start, done_fft, done_mag, done_tre, done_dec;

  // Set the locale to display numbers better
  setlocale( LC_ALL, "" );

  char filename[ 200 ];
  strcpy( filename,"../flussi_puliti_test_set.csv" );
  if ( argc > 2 ) {
    sscanf( argv[ 2 ], "%s", filename );
  }

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

  int num_threads = 2;
  if ( argc > 1 ) {
    sscanf( argv[ 1 ], "%d", &num_threads );
    fprintf( stderr, "setting num_threads: %d\n", num_threads );
  }
  // Handle the threads
  // Create the barriers
  pthread_barrier_init( &start_barrier, NULL, num_threads + 1 );
  pthread_barrier_init( &end_barrier, NULL, num_threads + 1 );
  // Initialize mutexes
  pthread_mutex_init( &mutex1, NULL );
  // For portability, explicitly create threads in a joinable state
  pthread_attr_t attr;
  pthread_attr_init( &attr );
  pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
  // Create the threads
  pthread_t threads[ 128 ];
  struct instructions tn[ 128 ];
  fprintf( stderr, "Creating threads\n" );
  int portion = TESTFLOWS / num_threads;
  for ( int nn = 0; nn < num_threads; nn++ ) {
    tn[ nn ].id = nn + 1;
    tn[ nn ].start_index = portion * nn;
    tn[ nn ].end_index = portion * ( nn + 1 );
    pthread_create( &threads[ nn ], NULL, worker1, (void *) &tn[ nn ] );
    // pthread_create( &threads[ 0 ], &attr, worker1, (void *) t1 );
  }

  // Prepare array for run-time statistics
  long long unsigned stats_all[ RUNS ];

  fprintf( stderr, "Starting runs\n" );
  for ( int k = -1; k < run_for; k++ ) {
    // The first run iteration is a warm up run, we do not store information for
    // statistics
    fprintf( stderr, "doing run iteration %d\n", k );

    confidence = 1.0;
    n_retrain = 0;

    // Take the time
    clock_gettime( CLOCK_MONOTONIC, &start );

    // Compute the tree results. Trigger the workers
    // fprintf( stderr, "Main: triggering\n" );
    pthread_barrier_wait( &start_barrier );

    // Wait for all workers to be done
    // fprintf( stderr, "Main: waiting for end\n" );
    pthread_barrier_wait( &end_barrier );

    clock_gettime( CLOCK_MONOTONIC, &done_tre );

    // Compute the delays
    unsigned long long time_all = (( done_tre.tv_sec * 1000000000) + done_tre.tv_nsec) - ((start.tv_sec * 1000000000) + start.tv_nsec);
    // Output the delays
    // printf( "TOTAL: %'lld ns, average: %'lld ns per flow\n", time_all, time_all / TESTFLOWS );
    // Output the confidence
    // printf( "confidence: %f, n_retrain: %d\n", confidence, n_retrain );
    if ( k >= 0 ) {
      stats_all[ k ] = time_all;
    }
  }
  // Compute stats
  long long unsigned min_all, max_all, mean_all, std_all;
  max_all = stats_all[ 0 ];
  min_all = stats_all[ 0 ];
  mean_all = 0;
  std_all = 0;
  for ( int k = 0; k < run_for; k++ ) {
    printf( "stats_all[ %d ] = %'lld\n", k, stats_all[ k ] );
    if ( max_all < stats_all[ k ] ) { max_all = stats_all[ k ]; }
    if ( min_all > stats_all[ k ] ) { min_all = stats_all[ k ]; }
    mean_all += stats_all[k];
  }
  mean_all = mean_all / run_for;
  for ( int k = 0; k < run_for; k++ ) {
    std_all += ( stats_all[ k ] - mean_all ) * ( stats_all[ k ] - mean_all );
  }
  double std_all_tot = sqrt( std_all / (run_for));
  printf( "num_threads: %d\n", num_threads );
  printf( "max all: %'12lld ns, min all: %'12lld ns, ave all: %'12lld ns, std all: %'12.6f\n", max_all, min_all, mean_all, std_all_tot );
  // Print per flow data
  printf( "num_flows: %d\n", TESTFLOWS );
  printf( "max all: %'12lld ns, min all: %'12lld ns, ave all: %'12lld ns, std all: %'12.6f\n", max_all / TESTFLOWS, min_all / TESTFLOWS, mean_all / TESTFLOWS, std_all_tot / TESTFLOWS );

  // Clean up and exit
  // Just exit
  exit( -1 );

}
