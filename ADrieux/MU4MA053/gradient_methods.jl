using LinearAlgebra

function steepest_gradient(A,b,x0,epsilon)
	x = x0
	p = b - A*x0
	alpha = 0
	while norm(p) > epsilon
		alpha = norm(p)^2/dot(p, A*p)
		x = x + alpha*p
		p = p - alpha*A*p
	end
	return x
end

function conjugate_gradient(A,b,x0,epsilon)
	p0 = r0 = b - A*x0
	r = zeros(length(r0))
	alpha = 0
	omega = 0
	while norm(r0) > epsilon 
		alpha = norm(r0)^2/dot(p0, A*p0)
		x0 = x0 + alpha*p0
		r = r0 - alpha*A*p0
		omega = norm(r)^2/norm(r0)^2
		r0 = r
		p0 = r + omega*p0
	end
	return x0
end

function steepest_gradient_k(A,b,x0,k)
	x = x0
	p = b - A*x0
	alpha = 0
	for i = 1:k
		alpha = norm(p)^2/dot(p, A*p)
		x = x + alpha*p
		p = p - alpha*A*p
	end
	return x
end

function conjugate_gradient_k(A,b,x0, k)
	p0 = r0 = b - A*x0
	r = zeros(length(r0))
	alpha = 0
	omega = 0
	for i = 1:k
		alpha = norm(r0)^2/dot(p0, A*p0)
		x0 = x0 + alpha*p0
		r = r0 - alpha*A*p0
		omega = norm(r)^2/norm(r0)^2
		r0 = r
		p0 = r + omega*p0
	end
	return x0
end

function error1(A, b, x0, k)
	error1 = zeros(length(x0))
	solution_approchee = steepest_gradient_k(A,b,x0,k)
	solution_exacte = A\b
	error1 = solution_approchee - solution_exacte
	return(sqrt(dot(error1, A*error1)))
end

function error(A, b, x0, k)
	error = zeros(length(x0))
	solution_approchee = conjugate_gradient_k(A,b,x0,k)
	solution_exacte = A\b
	error = solution_approchee - solution_exacte
	return(sqrt(dot(error, A*error)))
end

function f(A,l)
	valeurs_propres = eigvals(A)
	k2 = valeurs_propres[size(A,1) - l]/valeurs_propres[1]
	return(k2)
end

function PCG(A,b,x0,epsilon,M)
	r0 = b - A*x0
	d0 = M\r0
	alpha = 0
	omega = 0
	r = zeros(length(r0))
	while norm(r0) > epsilon 
		alpha = dot(r0, M\r0)/dot(d0,A*d0)
		x0 = x0 + alpha*d0
		r = r0 - alpha*A*d0
		omega = dot(r,M\r)/dot(r0,M\r0)
		r0 = r
		d0 = M\r + omega*d0
	end
	return x0
end

function matrice_D(N)
	D = zeros(N,N)
	for i = 1:N
		D[i,i] = i^2*pi^2
	end
	return(D)
end

function vecteur_f(N)
	f = zeros(N)
	for i = 1:N
		f[i] = (1-(-1)^i)/pi*i
	end
	return(f)
end

function matrice_P(N)
	P = zeros(N,N)
	for i = 1:N
		for j = i+1:N
			P[i,j] = ((-1)^(i-j) + 1)/(2*pi^2*(i-j)^2) + ((-1)^(i+j) + 1)/(2*pi^2*(i+j)^2)
			P[j, i] = P[i, j]
		end
	end
	for k = 1:N
		P[k,k] = 1/12
	end
	return(P)
end

function value(v,x)
	s = 0
	for k = 1:length(x)
		s = s + v[k]*sin(pi*k*x)
	end
	return(s)
end

function PCG_k(A,b,x0,epsilon,M)
	r0 = b - A*x0
	d0 = M\r0
	alpha = 0
	omega = 0
	k = 0
	r = zeros(length(r0))
	while norm(r0) > epsilon
		k = k + 1
		alpha = dot(r0, M\r0)/dot(d0,A*d0)
		x0 = x0 + alpha*d0
		r = r0 - alpha*A*d0
		omega = dot(r,M\r)/dot(r0,M\r0)
		r0 = r
		d0 = M\r + omega*d0
	end
	return k
end






