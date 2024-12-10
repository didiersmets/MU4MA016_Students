using LinearAlgebra 

function Jacobi(A,b, x0, epsilon)
	M = Diagonal(A)
	N = M - A
	inv_M = inv(M)
	x = zeros(length(x0))
	while norm(A*x0 - b) > epsilon
		x = inv_M*N*x0 + inv_M*b
		x0 = x
	end
	return x
end

function Gauss_Seidel(A, b, x0, epsilon)
	M = LowerTriangular(A)
	N = M - A
	inv_M = inv(M)
	x = zeros(length(x0))
	while norm(A*x0 - b) > epsilon
		x = inv_M*N*x0 + inv_M*b
		x0 = x
	end
	return x
end

function Lap_full(size)
	T = zeros(size,size)
	for i = 1:size
		T[i,i] = 2
	for i = 1:size-1
		T[i,i+1] = T[i+1,i] = -1
	end
	end
	return T
end

function Lap_sparse(size)
	D = 2*ones(size)
	Du = -1*ones(size)
	T = SymTridiagonal(D,Du)
	return(T)
end

#function error(A, b, x0, epsilon)






