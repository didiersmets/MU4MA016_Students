using LinearAlgebra

function lu_naive(A)
	n = size(A)[1]
	L = Matrix{Float64}(I,n,n)
	for p = 1:n-1
		for j = p+1:n
			for k = p+1:n
				L[j,p] = A[j,p]/A[p,p]
				A[j,p] = A[j,p] - A[j,p]
				A[j,k] = A[j,k] - L[j,p]*A[p,j]'
			end
		end
	end
	return L,A
end

function lu_decompose(A)
	n = size(A)[1]
	for p = 1:n-1
		for j = p+1:n
			for k = p+1:n
				A[j,p] = A[j,p]/A[p,p]
				A[j,k] = A[j,k] - A[j,p]*A[p,j]'
			end
		end
	end
	return A
end

function lu_solve(A,b)
	n = size(A)[1]
	v = zeros(n)
	u = zeros(n)
	T = lu_decompose(A)
	for j = 1:n
		v[j] = b[j]
		for k = 1:j-1
			v[j] = v[j] - T[j,k]*v[k]
		end
	end
	for p = 1:n
		j = n-p+1
		u[j] = v[j]
		for k = j+1:n
			u[j] = u[j] - T[j,k]*u[k]
		end
		u[j] = u[j]/T[j,j]
	end
	return u 
end

function lu_solve!(A,b)
	T = lu_decompose(A)
	n = size(b)[1]
	for j = 1:n
		for k = 1:j-1
			b[j] = b[j] - T[j,k]*b[k]
		end
	end
	for p = 1:n
		j = n-p+1
		for k = j+1:n
			b[j] = b[j] - T[j,k]*b[k]
		end
		b[j] = b[j]/T[j,j]
	end
	return b
end







