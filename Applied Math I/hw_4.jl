using PyPlot

function Runge_kutta_step(F,x,y,h,a,b,c,s)
	k = Array{Float64}(undef,s,3)
	for i in 1:s 
		k[i,1] = x + c[i]*h
		k[i,2] = y
		for j in 1:(i-1)
			k[i,2] += a[i,j]*h*k[j,3]
		end
		k[i,3] = F(k[i,1],k[i,2])
	end 
	sum = 0 
	for i in 1:s
		sum += b[i]*k[i,3]
	end
	return sum
end

function Runge_kutta(F,x0,xf,y0,N,a,b,c,s)
	h = (xf - x0)/N 
	Y = zeros(N+1)
	X = zeros(N+1)
	X[1] = x0
	for i in 2:(N+1) 
		X[i] = X[i-1] + h
	end
	Y[1] = y0
	for i in 2:(N+1)
		Y[i] = Y[i-1] + h*Runge_kutta_step(F,X[i-1],Y[i-1],h,a,b,c,s)
	end
	return [X,Y]
end

F(x,y) = sin(x)*y
a = [0 0 0 0; 1/3 0 0 0; -1/3 1 0 0; 1 -1 1 0]
b = [1/8 3/8 3/8 1/8]
c = [0 1/3 2/3 1]

z=Runge_kutta(F,1,6,2,25,a,b,c,4)


t = 1:.01:6
#plot(t,2 .* exp.(cos(1) .- cos.(t)))
#scatter(z[1],z[2])
#savefig("4_Q2")

#print(abs(2exp(cos(1)-cos(6))-z[2][25]))

N = zeros(9)
E = zeros(9)
for i in 2:9
	N[i]= Int(5^i)
	E[i] = abs(2exp(cos(1)-cos(6)) - Runge_kutta(F,1,6,2,Int(N[i]),a,b,c,4)[2][Int(N[i]+1)])
end
scatter(log.(5 ./ N), log.(E))
savefig("4_Q3")

##Only first 4 make sense

print((log(E[2])-log(E[5]))/(log(N[2])-log(N[5])))