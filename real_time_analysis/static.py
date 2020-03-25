import pandas as pd
import numpy as np
import random
import sys
import time
import statistics 
import forestci as fci
from matplotlib import pyplot as plt

from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle

np.set_printoptions(threshold=sys.maxsize)
csvData = pd.read_csv("live/primo_set.csv",sep=',').values
#random.shuffle(csvData)
csvData = shuffle(csvData)
X = csvData[:, :-1]
y = csvData[:, -1]
csvData2 = pd.read_csv("live/secondo_set.csv",sep =',').values
csvData2= shuffle(csvData2)
X2 = csvData2[:, :-1]
y2 = csvData2[:, -1]
csvData3 = pd.read_csv("live/terzo.csv",sep =',').values
csvData3 = shuffle(csvData3)
X3 = csvData3[:, :-1]
y3 = csvData3[:, -1]
csvData4 = pd.read_csv("live/quarto.csv",sep =',').values
csvData4 = shuffle(csvData4)
X4 = csvData4[:, :-1]
y4 = csvData4[:, -1]
csvData5 = pd.read_csv("live/quinto.csv",sep =',').values
csvData5 = shuffle(csvData5)
X5 = csvData5[:, :-1]
y5 = csvData5[:, -1]
csvData6 = pd.read_csv("live/sesto.csv",sep =',').values
csvData6 = shuffle(csvData6)
X6 = csvData6[:, :-1]
y6 = csvData6[:, -1]
csvData7 = pd.read_csv("live/settimo.csv",sep =',').values
csvData7 = shuffle(csvData7)
X7 = csvData7[:, :-1]
y7 = csvData7[:, -1]

spam_X_train, spam_X_test, spam_y_train, spam_y_test = train_test_split(
                                                       X, y,
                                                       test_size=0.3)
spam_X_train2, spam_X_test2, spam_y_train2, spam_y_test2 = train_test_split(
                                                       X2, y2,
                                                       test_size=0.3)
spam_X_train3, spam_X_test3, spam_y_train3, spam_y_test3 = train_test_split(
                                                       X3, y3,
                                                       test_size=0.3)
spam_X_train4, spam_X_test4, spam_y_train4, spam_y_test4 = train_test_split(
                                                       X4, y4,
                                                       test_size=0.3)
spam_X_train5, spam_X_test5, spam_y_train5, spam_y_test5 = train_test_split(
                                                       X5, y5,
                                                       test_size=0.3)
spam_X_train6, spam_X_test6, spam_y_train6, spam_y_test6 = train_test_split(
                                                       X6, y6,
                                                       test_size=0.3)
spam_X_train7, spam_X_test7, spam_y_train7, spam_y_test7 = train_test_split(
                                                       X7, y7,
                                                       test_size=0.3)

combo_X_train = np.concatenate((spam_X_train,spam_X_train2))
combo_y_train = np.concatenate((spam_y_train,spam_y_train2))
combo_X_test = np.concatenate((spam_X_test,spam_X_test2))
combo_y_test = np.concatenate((spam_y_test,spam_y_test2))

#combo_X_train = shuffle(combo_X_train)  
#combo_y_train = shuffle(combo_y_train) 
combo_X_test =  shuffle(combo_X_test)
combo_y_test =  shuffle(combo_y_test)

combo_X_train2 = np.concatenate((combo_X_train,spam_X_train3))
combo_y_train2 = np.concatenate((combo_y_train,spam_y_train3)) 
combo_X_test2 = np.concatenate((combo_X_test,spam_X_test3))
combo_y_test2 = np.concatenate((combo_y_test,spam_y_test3))

#combo_X_train2 = shuffle(combo_X_train2)  
#combo_y_train2 = shuffle(combo_y_train2) 
combo_X_test2=  shuffle(combo_X_test2)
combo_y_test2=  shuffle(combo_y_test2)

combo_X_train3 = np.concatenate((combo_X_train2,spam_X_train4))
combo_y_train3 = np.concatenate((combo_y_train2,spam_y_train4)) 
combo_X_test3 = np.concatenate((combo_X_test2,spam_X_test4)) 
combo_y_test3 = np.concatenate((combo_y_test2,spam_y_test4))

#combo_X_train3 = shuffle(combo_X_train3)  
#combo_y_train3 = shuffle(combo_y_train3) 
combo_X_test3 =  shuffle(combo_X_test3)
combo_y_test3 =  shuffle(combo_y_test3)

combo_X_train4 = np.concatenate((combo_X_train3,spam_X_train5)) 
combo_y_train4 = np.concatenate((combo_y_train3,spam_y_train5)) 
combo_X_test4 = np.concatenate((combo_X_test3,spam_X_test5)) 
combo_y_test4 = np.concatenate((combo_y_test3,spam_y_test5))

#combo_X_train4 = shuffle(combo_X_train4)  
#combo_y_train4 = shuffle(combo_y_train4) 
combo_X_test4 =  shuffle(combo_X_test4)
combo_y_test4 =  shuffle(combo_y_test4)

combo_X_train5 = np.concatenate((combo_X_train4,spam_X_train6)) 
combo_y_train5 = np.concatenate((combo_y_train4,spam_y_train6)) 
combo_X_test5 = np.concatenate((combo_X_test4,spam_X_test6)) 
combo_y_test5 = np.concatenate((combo_y_test4,spam_y_test6)) 

#combo_X_train5 = shuffle(combo_X_train5)  
#combo_y_train5 = shuffle(combo_y_train5) 
combo_X_test5 =  shuffle(combo_X_test5)
combo_y_test5 =  shuffle(combo_y_test5)

combo_X_train6 = np.concatenate((combo_X_train5,spam_X_train7))
combo_y_train6 = np.concatenate((combo_y_train5,spam_y_train7))
combo_X_test6 = np.concatenate((combo_X_test5,spam_X_test7))
combo_y_test6 = np.concatenate((combo_y_test5,spam_y_test7))

#combo_X_train6 = shuffle(combo_X_train6)  
#combo_y_train6 = shuffle(combo_y_train6) 
combo_X_test6 =  shuffle(combo_X_test6)
combo_y_test6 =  shuffle(combo_y_test6)

beta = 0.99
n_trees = 100
spam_RFC = RandomForestClassifier(max_features=5,n_estimators=n_trees,random_state=42)
spam_RFC.fit(spam_X_train,spam_y_train)
somma = len(spam_X_test) + len(spam_X_test2) + len(combo_X_test) + len(spam_X_test3) + len(combo_X_test2) + len(spam_X_test4) + len(combo_X_test3) + len(spam_X_test5) + len(combo_X_test4) + len(spam_X_test6) + len(combo_X_test5) + len(spam_X_test7) + len(combo_X_test6)
print(somma)


#aa = spam_RFC.score(spam_X_test, spam_y_test)
#n_nodes = []
#max_depths = []

#print(aa)
# Stats about the trees in random forest

#for ind_tree in spam_RFC.estimators_:
#    n_nodes.append(ind_tree.tree_.node_count)
#    max_depths.append(ind_tree.tree_.max_depth)

#print({int(np.mean(n_nodes))})
#print({int(np.mean(max_depths))})

#trainpredictions = spam_RFC.predict(X)
op = spam_RFC.predict_proba(spam_X_test)
#print(op2)
#for ind_tree in spam_RFC.estimators_:
# 	print(ind_tree.predict_proba(spam_X_test))
# 	print('ciaoaicoao')

#print(op)
#print('das')

mostrato = max(op[0])
prob=[]
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova
    prob.append(mostrato) 
    print(mostrato)  

plt.axvline(x=len(prob),color = 'r')

op = spam_RFC.predict_proba(spam_X_test2)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break
    print(mostrato)  


plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train,combo_y_train)
op  = spam_RFC.predict_proba(combo_X_test)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova
    prob.append(mostrato)
    print(mostrato)  


plt.axvline(x=len(prob),color = 'r')
op = spam_RFC.predict_proba(spam_X_test3)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break

plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train2,combo_y_train2)
op  = spam_RFC.predict_proba(combo_X_test2)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    print(mostrato)  


plt.axvline(x=len(prob),color = 'r')
op  = spam_RFC.predict_proba(spam_X_test4)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break
    print(mostrato)  


plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train3,combo_y_train3)
op  = spam_RFC.predict_proba(combo_X_test3)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    print(mostrato)  


plt.axvline(x=len(prob),color = 'r')
op  = spam_RFC.predict_proba(spam_X_test5)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break
    print(mostrato)  


plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train4,combo_y_train4)
op  = spam_RFC.predict_proba(combo_X_test4)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    print(mostrato)  


plt.axvline(x=len(prob),color = 'r')
op  = spam_RFC.predict_proba(spam_X_test6)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break
    print(mostrato)  


plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train5,combo_y_train5)
op  = spam_RFC.predict_proba(combo_X_test5)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    print(mostrato)  


plt.axvline(x=len(prob),color = 'r')
op  = spam_RFC.predict_proba(spam_X_test7)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.8):
       break
    print(mostrato)  

plt.axvline(x=len(prob),color='g')
spam_RFC.fit(combo_X_train6,combo_y_train6)
op  = spam_RFC.predict_proba(combo_X_test6)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    print(mostrato)  


out_file = open("test_ogni100_fisso.txt","w")

for element in prob:
    print >>out_file, element

out_file.write("Ho finito\n")

for element in range(0,len(prob)):
    print >>out_file,element

out_file.close()


plt.axvline(x=len(prob),color = 'r')
asse_x = range(0,len(prob)) 
plt.plot(asse_x,prob)
plt.show()
