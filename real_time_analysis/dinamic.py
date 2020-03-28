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

combo_X_test =  shuffle(combo_X_test)
combo_y_test =  shuffle(combo_y_test)

combo_X_train2 = np.concatenate((combo_X_train,spam_X_train3))
combo_y_train2 = np.concatenate((combo_y_train,spam_y_train3)) 
combo_X_test2 = np.concatenate((combo_X_test,spam_X_test3))
combo_y_test2 = np.concatenate((combo_y_test,spam_y_test3))

combo_X_test2 =  shuffle(combo_X_test2)
combo_y_test2 =  shuffle(combo_y_test2)

combo_X_train3 = np.concatenate((combo_X_train2,spam_X_train4))
combo_y_train3 = np.concatenate((combo_y_train2,spam_y_train4)) 
combo_X_test3 = np.concatenate((combo_X_test2,spam_X_test4)) 
combo_y_test3 = np.concatenate((combo_y_test2,spam_y_test4))

combo_X_test3 =  shuffle(combo_X_test3)
combo_y_test3 =  shuffle(combo_y_test3)

combo_X_train4 = np.concatenate((combo_X_train3,spam_X_train5)) 
combo_y_train4 = np.concatenate((combo_y_train3,spam_y_train5)) 
combo_X_test4 = np.concatenate((combo_X_test3,spam_X_test5)) 
combo_y_test4 = np.concatenate((combo_y_test3,spam_y_test5))

combo_X_test4 =  shuffle(combo_X_test4)
combo_y_test4 =  shuffle(combo_y_test4)

combo_X_train5 = np.concatenate((combo_X_train4,spam_X_train6)) 
combo_y_train5 = np.concatenate((combo_y_train4,spam_y_train6)) 
combo_X_test5 = np.concatenate((combo_X_test4,spam_X_test6)) 
combo_y_test5 = np.concatenate((combo_y_test4,spam_y_test6)) 

combo_X_test5 =  shuffle(combo_X_test5)
combo_y_test5 =  shuffle(combo_y_test5)

combo_X_train6 = np.concatenate((combo_X_train5,spam_X_train7))
combo_y_train6 = np.concatenate((combo_y_train5,spam_y_train7))
combo_X_test6 = np.concatenate((combo_X_test5,spam_X_test7))
combo_y_test6 = np.concatenate((combo_y_test5,spam_y_test7))

combo_X_test6 =  shuffle(combo_X_test6)
combo_y_test6 =  shuffle(combo_y_test6)


per1 = (len(spam_X_test)*2)/3
newtest_X_test = spam_X_test[:per1,:]
spam_X_test_0 = spam_X_test[per1:,:]
newtest_X_test = shuffle(newtest_X_test)
print(len(newtest_X_test))

newtest_X_test2 = np.concatenate((spam_X_test_0[:len(spam_X_test2),:],spam_X_test2)) 
per1 = (len(newtest_X_test2)*2)/3
newtest_X_test2 = shuffle(newtest_X_test2)
newtest_X_test2 = newtest_X_test2[:per1,:]
print(len(newtest_X_test2))

per1 = (len(combo_X_test)*2)/3 
combo_X_test_0 = combo_X_test[:per1,:]
combo_X_test_0_0 = combo_X_test[per1:,:]
print("lung ",len(combo_X_test_0))

newtest_X_test3 = np.concatenate((combo_X_test_0_0[:len(spam_X_test3),:],spam_X_test3))
per1 = (len(newtest_X_test3)*2)/3
newtest_X_test3 = shuffle(newtest_X_test3)
newtest_X_test3 = newtest_X_test3[:per1,:]
print(len(newtest_X_test3))

per1 = (len(combo_X_test2)*2)/3 
combo_X_test_1 = combo_X_test2[:per1,:]
combo_X_test_1_1 = combo_X_test2[per1:,:]
print("lung ",len(combo_X_test_1))

newtest_X_test4 = np.concatenate((combo_X_test_1_1[:len(spam_X_test4),:],spam_X_test4))
per1 = (len(newtest_X_test4)*2)/3
newtest_X_test4 = shuffle(newtest_X_test4)
newtest_X_test4 = newtest_X_test4[:per1,:]
print(len(newtest_X_test4))

per1 = (len(combo_X_test3)*2)/3 
combo_X_test_2 = combo_X_test3[:per1,:]
combo_X_test_2_2 = combo_X_test3[per1:,:]
print("lung ",len(combo_X_test_2))

newtest_X_test5 = np.concatenate((combo_X_test_2_2[:len(spam_X_test5),:],spam_X_test5))
per1 = (len(newtest_X_test5)*2)/3
newtest_X_test5 = shuffle(newtest_X_test5)
newtest_X_test5 = newtest_X_test5[:per1,:]
print(len(newtest_X_test5))

per1 = (len(combo_X_test4)*2)/3 
combo_X_test_3 = combo_X_test4[:per1,:]
combo_X_test_3_3 = combo_X_test4[per1:,:]
print("lung ",len(combo_X_test_3))

newtest_X_test6 = np.concatenate((combo_X_test_3_3[:len(spam_X_test6),:],spam_X_test6))
per1 = (len(newtest_X_test6)*2)/3
newtest_X_test6 = shuffle(newtest_X_test6)
newtest_X_test6 = newtest_X_test6[:per1,:]
print(len(newtest_X_test6))

per1 = (len(combo_X_test5)*2)/3 
combo_X_test_4 = combo_X_test5[:per1,:]
combo_X_test_4_4 = combo_X_test5[per1:,:]
print("lung ",len(combo_X_test_4))

newtest_X_test7 = np.concatenate((combo_X_test_4_4[:len(spam_X_test7),:],spam_X_test7))
per1 = (len(newtest_X_test7)*2)/3
newtest_X_test7 = shuffle(newtest_X_test7)
newtest_X_test7 = newtest_X_test7[:per1,:]
print(len(newtest_X_test7))

per1 = (len(combo_X_test6)*2)/3 
combo_X_test_5 = combo_X_test6[:per1,:]
combo_X_test_5_5 = combo_X_test6[per1:,:]
print("lung ",len(combo_X_test_5))

beta = 0.99
n_trees = 100
spam_RFC = RandomForestClassifier(max_features=5,n_estimators=n_trees,random_state=42)
spam_RFC.fit(spam_X_train,spam_y_train)
somma = len(spam_X_test) + len(spam_X_test2) + len(combo_X_test) + len(spam_X_test3) + len(combo_X_test2) + len(spam_X_test4) + len(combo_X_test3) + len(spam_X_test5) + len(combo_X_test4) + len(spam_X_test6) + len(combo_X_test5) + len(spam_X_test7) + len(combo_X_test6)
print(somma)


out_file = open("test_ogni100_variabile.txt","w")

op = spam_RFC.predict_proba(newtest_X_test)

mostrato = max(op[0])
prob=[]
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova
    prob.append(mostrato) 
    print(mostrato)  

out_file.write("Punto rosso ")
out_file.write(str(len(prob)))
out_file.write("\n")
plt.axvline(x=len(prob),color = 'r')

op = spam_RFC.predict_proba(newtest_X_test2)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break
    print(mostrato)  


if(mostrato < 0.9):
    spam_RFC.fit(combo_X_train,combo_y_train)
    out_file.write("Punto blu ")
    out_file.write(str(len(prob)))
    out_file.write("\n")
    plt.axvline(x=len(prob),color = 'b')

op  = spam_RFC.predict_proba(combo_X_test_0)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova
    prob.append(mostrato)
    print(mostrato)  


out_file.write("Punto rosso ")
out_file.write(str(len(prob)))
out_file.write("\n")
plt.axvline(x=len(prob),color = 'r')

op = spam_RFC.predict_proba(newtest_X_test3)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break


op  = spam_RFC.predict_proba(newtest_X_test4)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break
    print(mostrato)  


if(mostrato < 0.9):
    spam_RFC.fit(combo_X_train3,combo_y_train3)
    plt.axvline(x=len(prob),color = 'b')
    out_file.write("Punto blu ")
    out_file.write(str(len(prob)))
    out_file.write("\n")

op  = spam_RFC.predict_proba(combo_X_test_2)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
#    if(mostrato < 0.9):
#       break
    print(mostrato)  


out_file.write("Punto rosso ")
out_file.write(str(len(prob)))
out_file.write("\n")
plt.axvline(x=len(prob),color = 'r')

op  = spam_RFC.predict_proba(newtest_X_test5)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break
    print(mostrato)  


out_file.write("Punto verde ")
out_file.write(str(len(prob)))
out_file.write("\n")
plt.axvline(x=len(prob),color='g')


#spam_RFC.fit(combo_X_train4,combo_y_train4)
#plt.axvline(x=len(prob),color = 'b')

op  = spam_RFC.predict_proba(combo_X_test_3)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
#    if(mostrato < 0.9):
#       break
    print(mostrato)  


out_file.write("Punto rosso ")
out_file.write(str(len(prob)))
out_file.write("\n")
plt.axvline(x=len(prob),color = 'r')

op  = spam_RFC.predict_proba(newtest_X_test6)
mostrato = beta*mostrato+(1-beta)*max(op[0])
#plt.axvline(x=len(prob),color = 'b')
    

prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break
    print(mostrato)  

op  = spam_RFC.predict_proba(newtest_X_test7)

mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)

for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
    if(mostrato < 0.9):
       break
    print(mostrato)  

if(mostrato < 0.9):
    spam_RFC.fit(combo_X_train6,combo_y_train6)
    plt.axvline(x=len(prob),color = 'b')
    out_file.write("Punto blu ")
    out_file.write(str(len(prob)))
    out_file.write("\n")

op  = spam_RFC.predict_proba(combo_X_test_5)
mostrato = beta*mostrato+(1-beta)*max(op[0])
prob.append(mostrato)



for xx in op[1:]:
    probabilita_nuova = max(xx)
    mostrato = beta*mostrato+(1-beta)*probabilita_nuova 
    prob.append(mostrato)
#    if(mostrato < 0.9):
#       break
    print(mostrato)  

out_file.write("Punto rosso ")
out_file.write(str(len(prob)))
out_file.write("\n")

x = 0
for element in prob:
    print >>out_file,x," ",element
    x = x+1

out_file.write("Ho finito\n")

out_file.close()


plt.axvline(x=len(prob),color = 'r')

asse_x = range(0,len(prob)) 
plt.plot(asse_x,prob)
plt.show()
