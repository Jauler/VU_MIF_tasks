#!/usr/bin/octave

L1 = load("A9.dat")';
L2 = load("B9.dat")';
T1 = load("C9.dat")';
T2 = load("D9.dat")';

L1(3, :) = ones(1, length(L1(1, :)));
L2(3, :) = ones(1, length(L2(1, :)));
T1(3, :) = ones(1, length(T1(1, :)));
T2(3, :) = ones(1, length(T2(1, :)));

function V = activation_func(x)
	V = 1 / (1 + e^(-x));
endfunction

function E = estimate_accuracy(w, L1, L2)
	E = 0;
	N = length(L1) + length(L2);
	N1 = length(L1(1, :));
	N2 = length(L2(1, :));
	for i=1:1:N1
		x = L1(:, i);
		if w' * x <= 0
			E = E + 1;
		endif
	endfor
	for i=1:1:N2
		x = L2(:, i);
		if w' * x > 0
			E = E + 1;
		endif
	endfor
	E = E * 100 / N;
endfunction

function E = estimate_error(w, L1, L2)
	E = 0;
	N = length(L1) + length(L2);
	N1 = length(L1(1, :));
	N2 = length(L2(1, :));
	for i=1:1:N1
		o = activation_func(w' * L1(:, i));
		E = E + (1 - o) ** 2;
	endfor
	for i=1:1:N2
		o = activation_func(w' * L2(:, i));
		E = E + (0 - o) ** 2;
	endfor
	E = E / (4 * N);
endfunction

function w_new = perceptron_iterate(w, L1, L2, step)
	N1 = length(L1(1, :));
	N2 = length(L2(1, :));
	N = N1 + N2;

	temp = 0;
	for i=1:1:N1
		x = L1(:, i);
		o = activation_func(w' * x);
		temp = temp + (1 - o) * o * (1 - o) * x;
	endfor
	for i=1:1:N2
		x = L2(:, i);
		o = activation_func(w' * x);
		temp = temp + (0 - o) * o * (1 - o) * x;
	endfor

	w_new = w + step / (2 * N1) * temp;
endfunction

function [w, E, epoch_count] = learn(w_init, L1, L2, T1, T2, step)
	w = w_init;
	epoch_count = 0;
	do
		w = perceptron_iterate(w, L1, L2, step);
		epoch_count = epoch_count + 1;
	until (estimate_accuracy(w, L1, L2) <= 0)

	E = estimate_accuracy(w, T1, T2);
endfunction

w_init = [1, 1, 1]'
disp("==========")
niu = 0.1
[w, E, epoch_count] = learn(w_init, L1, L2, T1, T2, niu)
disp("==========")
niu = 1
[w, E, epoch_count] = learn(w_init, L1, L2, T1, T2, niu)
disp("==========")
niu = 10
[w, E, epoch_count] = learn(w_init, L1, L2, T1, T2, niu)







