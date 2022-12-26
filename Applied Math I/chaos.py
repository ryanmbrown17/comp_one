##Packages
import numpy as np 
import matplotlib.pyplot as plt
import math
from collections import Counter

### Given a linear Map X(x), n, x0, returns numpy array 
def orbit(X,n,x0):
	arr = np.zeros(n+1)
	arr[0] = x0
	for i in range(n):
		arr[i+1] = X(arr[i])
	return arr

####
def logistic(mu,x):
	return mu*x*(1-x)

def logistic_orbit(mu,n,x0):
	arr = np.zeros(n+1)
	arr[0] = x0
	for i in range(n):
		arr[i+1] = logistic(mu,arr[i])
	return arr
def Arr_const(v,n):
	arr = np.zeros(n)
	for i in range(n):
		arr[i] = v 
	return arr
def drange(start,stop,step):
	r=start
	while r<stop:
		yield r 
		r+=step
###
def biforcation_portion(start,end,x_0,n):
	X = Arr_const(start,100)
	Y = logistic_orbit(start,500,x_0)[401:]
	for i in drange(start,end,1/n):
		X = np.append(X,Arr_const(i,100))
		new = logistic_orbit(i,500,x_0)[401:]
		Y = np.append(Y,new)
	return X,Y

def Liapunov_exp(mu,x_0):
	sum = 0 
	x=x_0
	for i in range(401,501):
		x = logistic(mu,x)
		sum += np.log(abs(mu-2*mu*x))
	return sum/100

def Liaponv_exp_auto_stop(start,stop,x_0,n,epsilon):
	arr = np.zeros(0)
	I=0
	if(start==0):
		start += n
	arr=np.append(arr,[Liapunov_exp(start,x_0)])
	for i in drange(start+n,stop,n):
		arr=np.append(arr,[Liapunov_exp(i,x_0)])
		if(arr[-1]>=0 ):
			while(arr[-1]>=0):
				i+=n
				arr=np.append(arr,[Liapunov_exp(i,x_0)])
			return arr,i
		if(arr[-1]-arr[-2]>0 and arr[-1]>-epsilon):
			while(arr[-1]-arr[-2]>0 and arr[-1]>-epsilon):
				i+=n
				arr=np.append(arr,[Liapunov_exp(i,x_0)])
			return arr,i
		I=i
	return arr,I
	
#X, Y = biforcation_portion(2,3.57,.1,10000)
#plt.scatter(X,Y,s=.1,linewidth=0)
#plt.title("Biforcation Diagram")
#plt.xlabel("\u03bc")
#plt.ylabel("Periodic Points")
#plt.savefig("Biforcation",dpi=1000)

Y = np.zeros(4000000-2600000)
X = np.zeros(4000000-2600000)
for i in range(2600000,4000000):
	X[i-2600000] = i/1000000
	Y[i-2600000] = Liapunov_exp(i/1000000,.2)

plt.scatter(X[Y>-1],Y[Y>-1],s=.1,linewidth=0)
plt.scatter(X[Y>=-0.01],Y[Y>=-0.01],s=.1,linewidth=0)
plt.title("Liapunov Exponents")
plt.xlabel("\u03bc")
plt.ylabel("λ")
plt.savefig("liapunov",dpi=1000)


#R_list = np.linspace(2.0,3.6,10000)
#x0 = 0.2
#N = 1200


#non_repetitive=[] 
#mu = []
#cool_down=False
#for r in R_list:
#		new = len(Counter(logistic_orbit(r,N,.2)[201:]))
#		non_repetitive.append(new)
#		if(new == 1000 and cool_down==False):
#			mu.append(r)
#			cool_down = True
#		if(new <900 ):
#			cool_down=False

#print(mu)


#plt.scatter(R_list,non_repetitive,s=1,linewidth =0)
#plt.title("Repeated Points")
#plt.xlabel("\u03bc")
#plt.ylabel("Number of Repeated Points")
#plt.savefig("unique",dpi=1000)

#X,Y = biforcation_portion(3.5,4,.2,10000)
#plt.scatter(X,Y,s=.1,linewidth=0)
#plt.title("Chaos")
#plt.xlabel("\u03bc")
#plt.ylabel("Eventual Points")
#plt.savefig("Chaos",dpi=1000)

