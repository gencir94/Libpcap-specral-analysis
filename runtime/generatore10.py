from __future__ import print_function
import pandas as pd
import numpy as np
import random
import sys
import csv
import time
import statistics
import forestci as fci
import math
import numpy as geek
import sklearn
from sklearn.tree import export_graphviz
from sklearn.tree import _tree
#from sklearn.tree import export_text

#from sympy import ifft
#from sympy import fft
from scipy import *
from matplotlib import pyplot as plt

from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle

np.set_printoptions(threshold=sys.maxsize)
csvData = pd.read_csv("out_trasformato.csv",sep=',').values
csvData = shuffle(csvData)
X = csvData[:, :-1]
y = csvData[:, -1]


spam_X_train, spam_X_test, spam_y_train, spam_y_test = train_test_split(
                                                       X, y,
                                                       test_size=0.3)



#prendo il 20% del test
per1 = (len(spam_X_test)*2)//3
newtest_X_test = spam_X_test[:per1,:]
spam_X_test_0 = spam_X_test[per1:,:]



# creo il modello
n_trees = 100
spam_RFC = RandomForestClassifier( max_depth=10, max_features=5, n_estimators=n_trees, random_state=42 );

# addestro il modello
spam_RFC.fit( spam_X_train, spam_y_train );

out_file = open( "alberi10_mag_all.c", "w" );
out_file_global = open( "alberi10_all.c", "w" );


def tree_to_code( tree, feature_names, num_tree ):
    tree_ = tree.tree_
    feature_name = [
        feature_names[i] if i != _tree.TREE_UNDEFINED else "undefined!"
        for i in tree_.feature
    ]
    print( "int tree_" + str( k ) + "( float * magnitude ) {", file = out_file )
    print( "int tree_" + str( k ) + "( ) {", file = out_file_global )

    #num_nodes = len( tree_.feature );
    #print( "number of nodes: " + str( num_nodes ) );
    #for ii in range( len( tree_.num_nodes ) ):
    #    # Check if it is a leaf node
    #    if ( tree_.feature[ ii ] < 0 ):
    #        # leaf node
    #        print( str( ii ) + ": " + "-1, " );
    #    else:
    #        # tree node
    #        print( str( ii ) + ": " + str( tree_.feature[ ii ] ) );

    #num_nodes = len( tree_.threshold );
    #print( "number of nodes: " + str( num_nodes ) );
    #print( "feature, threshold, left, right" );
    #for i in range( len( tree_.threshold ) ):
    #    # Check if it is a leaf node
    #    if ( tree_.feature[ i ] < 0 ):
    #        # leaf node
    #        max_index_row = np.argmax( tree_.value[ i ], axis = 1 )
    #        max_index_row = max_index_row.item( 0 )
    #        print( str( i ) + ": " + "-1, " + str( max_index_row ) + ", 0, 0" );
    #    else:
    #        # tree node
    #        print( str( i ) + ": " + str( tree_.feature[ i ] ) + ", " + str( tree_.threshold[ i ] ) + ", " + str( tree_.children_left[ i ] ) + ", " + str( tree_.children_right[ i ] ) );

    def recurse(node, depth):
        indent = "  " * depth
        if tree_.feature[node] != _tree.TREE_UNDEFINED:
            name = feature_name[node]
            threshold = tree_.threshold[node]
            print ("{}if ( {} <= {} ) {{".format(indent, name, threshold),file=out_file)
            print ("{}if ( {} <= {} ) {{".format(indent, name, threshold),file=out_file_global)
            recurse(tree_.children_left[node], depth + 1)
            print ("{} }} else {{ ".format(indent),file=out_file)
            print ("{} }} else {{ ".format(indent),file=out_file_global)
            recurse(tree_.children_right[node], depth + 1)
            print ("{} }}".format(indent),file=out_file)
            print ("{} }}".format(indent),file=out_file_global)
        else:
            max_index_row = np.argmax(tree_.value[node], axis=1)
            max_index_row = max_index_row.item(0)
            #print(max_index_row)
            print ("{}return {}; ".format(indent, max_index_row),file=out_file)
            print ("{}return {}; ".format(indent, max_index_row),file=out_file_global)

    recurse(0, 1)

    print("}",file = out_file)
    print("}",file = out_file_global)


feature = []
for i in range(128):
        feature.append("magnitude["+str(i)+"]")

k = 0
for i in range(100):
        estimator = spam_RFC.estimators_[ i ]
        tree_to_code( estimator, feature, i )
        k = k + 1

#
# Output the tree in the form of a data structure
#
struct_file = open( "structure10_all.c", "w" );

def count_nodes( tree ):
    tree_ = tree.tree_
    num_nodes = len( tree_.feature );
    return num_nodes;

# struct tree_node { int feature; float threshold; int left; int right; };
def output_combined_array( tree, starting_node ):
    tree_ = tree.tree_
    num_nodes = len( tree_.feature );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    for ii in range( num_nodes ):
        # Check if it is a leaf node
        if ( tree_.feature[ ii ] < 0 ):
            # leaf node
            max_index_row = np.argmax( tree_.value[ ii ], axis = 1 );
            max_index_row = max_index_row.item( 0 );
            print( "{ -1, 0.0, 0, " + str( max_index_row ) + " }, // class", file=struct_file );
        else:
            # tree node
            print( "{ " + str( tree_.feature[ ii ] ) + ", " + str( tree_.threshold[ ii ] ) + ", " + str( tree_.children_left[ ii ] + starting_node ) + ", " + str( tree_.children_right[ ii ] + starting_node ) + " },", file=struct_file );
    return num_nodes;

def output_feature_array( tree, starting_node ):
    tree_ = tree.tree_
    num_nodes = len( tree_.feature );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    for ii in range( num_nodes ):
        # Check if it is a leaf node
        if ( tree_.feature[ ii ] < 0 ):
            # leaf node
            print( "-1,", file=struct_file );
        else:
            # tree node
            print( str( tree_.feature[ ii ] ) + ",", file=struct_file );
    return num_nodes;

def output_threshold_array( tree, starting_node ):
    tree_ = tree.tree_
    num_nodes = len( tree_.threshold );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    for ii in range( num_nodes ):
        # Check if it is a leaf node
        if ( tree_.feature[ ii ] < 0 ):
            # leaf node
            print( "0.0,", file=struct_file );
        else:
            # tree node
            print( str( tree_.threshold[ ii ] ) + ",", file=struct_file );
    return num_nodes;

def output_left_array( tree, starting_node ):
    tree_ = tree.tree_
    num_nodes = len( tree_.children_left );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    for ii in range( num_nodes ):
        # Check if it is a leaf node
        if ( tree_.feature[ ii ] < 0 ):
            # leaf node
            print( "0,", file=struct_file  );
        else:
            print( str( tree_.children_left[ ii ] + starting_node ) + ",", file=struct_file );
    return num_nodes;

def output_right_array( tree, starting_node ):
    tree_ = tree.tree_;
    num_nodes = len( tree_.children_right );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    for ii in range( num_nodes ):
        # Check if it is a leaf node
        if ( tree_.feature[ ii ] < 0 ):
            # leaf node
            max_index_row = np.argmax( tree_.value[ ii ], axis = 1 );
            max_index_row = max_index_row.item( 0 );
            print( str( max_index_row ) + ", // class", file=struct_file  );
        else:
            print( str( tree_.children_right[ ii ] + starting_node ) + ",", file=struct_file );
    return num_nodes;

def output_start_nodes( tree, starting_node ):
    tree_ = tree.tree_;
    num_nodes = len( tree_.features );
    print( "// number of nodes: " + str( num_nodes ), file=struct_file );
    print( str( starting_node ) + ",", file=struct_file );
    return num_nodes;

print( "int start_node[ 100 ] = {", file=struct_file );
total_nodes = 0;
for i in range( 100 ):
        print( str( total_nodes ) + ",", file=struct_file );
        estimator = spam_RFC.estimators_[ i ];
        total_nodes = total_nodes + count_nodes( estimator );
print( "};", file=struct_file );

# print( "int features[ " + str( total_nodes ) + " ] = {", file=struct_file );
# k = 0;
# for i in range( 100 ):
#         estimator = spam_RFC.estimators_[ i ];
#         k = k + output_feature_array( estimator, k );
# print( "};", file=struct_file );
# 
# print( "double thresholds[ " + str( total_nodes ) + " ] = {", file=struct_file );
# k = 0;
# for i in range( 100 ):
#         estimator = spam_RFC.estimators_[ i ];
#         k = k + output_threshold_array( estimator, k );
# print( "};", file=struct_file );
# 
# print( "int left[ " + str( total_nodes ) + " ] = {", file=struct_file );
# k = 0;
# for i in range( 100 ):
#         estimator = spam_RFC.estimators_[ i ];
#         k = k + output_left_array( estimator, k );
# print( "};", file=struct_file );
# 
# print( "int right[ " + str( total_nodes ) + " ] = {", file=struct_file );
# k = 0;
# for i in range( 100 ):
#         estimator = spam_RFC.estimators_[ i ];
#         k = k + output_right_array( estimator, k );
# print( "};", file=struct_file );

print( "struct TreeNode {", file=struct_file );
print( "  int feature;", file=struct_file );
print( "  float threshold;", file=struct_file );
print( "  int left;", file=struct_file );
print( "  int right;", file=struct_file );
print( "};", file=struct_file );
print( "struct TreeNode combined_array[ " + str( total_nodes ) + " ] = {", file=struct_file );
k = 0;
for i in range( 100 ):
        estimator = spam_RFC.estimators_[ i ];
        k = k + output_combined_array( estimator, k );
print( "};", file=struct_file );

# Analyze the tree depth
media = 0;
max_depth = 0;
min_depth = 1000; # need a large number here
for estimator in spam_RFC.estimators_:
        print( "Tree depth:" + str( estimator.tree_.max_depth ) );
        media = media + estimator.tree_.max_depth;
        if ( estimator.tree_.max_depth > max_depth ):
            max_depth = estimator.tree_.max_depth;
        if ( estimator.tree_.max_depth < min_depth ):
            min_depth = estimator.tree_.max_depth;

media = media / 100;

print( "Tree depth:" );
print( "Max depth:" + str( max_depth ) );
print( "Min depth:" + str( min_depth ) );
print( "Average depth: ", str( media ) );

# Export as dot file
#export_graphviz(estimator, out_file='tree.dot');


#tempo_totale = 0
#print("la lunghezza ",len(newtest_X_test))
#testo il modello
#per ogni flusso nel testset
"""
for ll in newtest_X_test :

    ll = ll.reshape(1, -1)
    start_time = time.time()
    op = spam_RFC.predict_proba(ll)
    print("PROVA DEL 9--- %s seconds ---" % (time.time() - start_time))
    a = []
    #antitrasformata
    transform = ifft(ll)
    #init timer
    start_time = time.time()
    #faccio la trasformata e calcolo l'ampiezza
    transform_i = fft(transform)
    print("FFT--- %s seconds ---" % (time.time() - start_time))
    start_time = time.time()
    transform_i = transform_i.real
    print("TRASFORMATZIONE REAL--- %s seconds ---" % (time.time() - start_time))
    #for x in range(len(transform_i)):
        #a.append(math.sqrt(transform_i[x]**2))

    start_time = time.time()
    transform_i = transform_i.reshape(1, -1)
    print("FFT RESHAPE--- %s seconds ---" % (time.time() - start_time))
    #test del modello
    start_time = time.time()
    op = spam_RFC.predict_proba(transform_i)
    print("Tempo singolo per flusso FFT inclusa --- %s seconds ---" % (time.time() - start_time))
    tempo_totale = tempo_totale + ( time.time() - start_time )

print("Il tempo totale con FFT --- %s seconds ---" % tempo_totale)

#Test senza FFT
start_time = time.time()
op = spam_RFC.predict_proba(newtest_X_test)
print("Il tempo senza FFT --- %s seconds ---" % (time.time() - start_time))

"""



