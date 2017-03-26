#!/usr/bin/octave

function y = func(x)
	y = tan(x);
endfunction

function x = build_x(N)
	x = -1:2/(N-1):1;
	x = x';
endfunction

function phi = base_func(lambda, t, x)
	phi = exp(lambda*abs(x-t));
endfunction

function G = estimate_G(lambda, x, m1)
	G = [];
	for j = -1 : 2/(m1 - 1) : 1
		G = [G, base_func(lambda, j, x)];
	endfor
endfunction

function w = learn(N, m1, lambda)
	x = build_x(N);
	G = estimate_G(lambda, x, m1);
	w = pinv(G) * func(x);
endfunction

function E = approx_accuracy(w, m1, lambda)
	x = build_x(201);
	y = func(x);
	G = estimate_G(lambda, x, m1);
	z = G * w;
	E = 1/2 * sum((z .- y) .^ 2);
endfunction

function E = estim_accuracy(w, m1, lambda)
	x = [1:0.01:1.2]';
	y = func(x);
	G = estimate_G(lambda, x, m1);
	z = G * w;
	E = 1/2 * sum((z .- y) .^ 2);
endfunction


pairs = [[5, 5]; [9, 5]; [9,9]; [21, 5]; [21, 9]; [21, 21]];
lambdas = [0, 0.5, 1, 2, 5];

approx = [[]];
estim = [[]];

for i = 1:1:length(pairs)
	for j = 1:1:length(lambdas)
		N = pairs(i, 1);
		m1 = pairs(i, 2);
		lambda = lambdas(j);
		if lambda == 0
			lambda = -m1/4;
		endif
		w = learn(N, m1, lambda);
		approx(j, i) = approx_accuracy(w, m1, lambda);
		estim(j, i) = estim_accuracy(w, m1, lambda);
	endfor
endfor

approx
[row,col] = find(approx==min(min(approx)));
best = [pairs(col, 1), pairs(col, 2), lambdas(row)]

estim
[row,col] = find(approx==min(min(approx)));
best = [pairs(col, 1), pairs(col, 2), lambdas(row)]

