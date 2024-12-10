using LinearAlgebra 

function rand_schrodinger_1d(N)
	L = zeros(N,N)
	v = zeros(N,N)
	for i = 1:N
		L[i,i] = 2
		v[i,i] = rand((1/N^2, 1))
	end
	for j = 1:N-1
		L[j+1,j] = L[j,j+1] = -1
	end
	return(L + v)
end

function conjugate_gradient(A,b,x0,epsilon)
	p0 = r0 = b-A*x0
	r = zeros(length(r0))
	alpha = 0
	omega = 0
	while norm(r0) > epsilon
		alpha = norm(r0)^2/dot(p0, A*p0)
		x0 = x0 + alpha*p0
		r = r0 - alpha*A*p0
		omega = norm(r)^2/norm(r0)^2
		r0 = r
		p0 = r0 + omega*p0
	end
	return x0
end

function Inverse_power_method(A,x,epsilon)
	y0 = x/norm(x)
	x0 = conjugate_gradient(A,y0,rand(length(x)), 1e-8)
	lambda = dot(y0, x0)
	while norm(y0 - lambda*A*y0) > epsilon
		y0 = x0/norm(x0)
		x0 = conjugate_gradient(A,y0,rand(length(x)), 1e-8)
		lambda = dot(y0, x0)
	end 
	return(1/lambda, y0)
end

function Power_method(A,x,epsilon)
	y0 = x/norm(x)
	lambda = dot(y0, A*y0)
	while norm(A*y0 - lambda*y0) > epsilon
		y0 = A*y0
		y0 = y0/norm(y0)
		lambda = dot(y0, A*y0)
	end
	return(lambda, y0)
end


#function Deflation(A,x,epsilon,neig)
#	V = zeros(neig)
#	Y = zeros(neig, length(x))
#	for i = 1:neig 
#		V[i] = eigvals(A)[i]
#		Y[i,:] = eigvecs(A)[:,i]
#	end
#	for n = 1:neig
#
