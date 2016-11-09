#!/usr/bin/octave

C1 = load("E9.dat")';
C2 = load("F9.dat")';

C1(3, :) = ones(1, length(C1(1, :)));
C2(3, :) = ones(1, length(C2(1, :)));

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
		x = L1(:, i);
		o = activation_func(w' * x);
		E = E + (1 - o) ** 2;
	endfor
	for i=1:1:N2
		x = L2(:, i);
		o = activation_func(w' * x);
		E = E + (0 - o) ** 2;
	endfor
	E = E / (4 * N1);
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
		e_old = estimate_error(w, L1, L2);
		w = perceptron_iterate(w, L1, L2, step);
		e_new = estimate_error(w, L1, L2);
		epoch_count = epoch_count + 1;
	until (epoch_count >= 1000 || abs(e_new - e_old) < 0.001)

	E = estimate_error(w, T1, T2);
endfunction

function [L1, L2, w_init] = select_data(C1, C2, count)
	w_init = rand(3, 1) * 0.2 - 0.1;
	N = length(C1);
	rndIdx = randperm(N);
	L1 = C1(:, rndIdx(1:count));
	L2 = C2(:, rndIdx(1:count));
endfunction

function [epoch_count_avg, E_learn_avg, E_test_avg] = run_multiple_times(C1, C2, run_count, count)
	E_learn = [];
	E_test = [];
	epoch_counts = [];
	for i = 1:1:run_count
		[L1, L2, w_init] = select_data(C1, C2, count);
		[w, E, epoch_count] = learn(w_init, L1, L2, L1, L2, 1);

		E_learn = [E_learn, estimate_accuracy(w, L1, L2)];
		E_test = [E_test, estimate_accuracy(w, C1, C2)];

		epoch_counts = [epoch_counts, epoch_count];
	endfor

	epoch_counts;
	E_learn;
	E_test;

	epoch_count_avg = mean(epoch_counts);
	E_learn_avg = mean(E_learn);
	E_test_avg = mean(E_test);
endfunction

rand("seed", time())

disp("====== 5 =======")
[epoch_count_avg, E_learn_avg, E_test_avg] = run_multiple_times(C1, C2, 10, 5)

disp("====== 10 =======")
[epoch_count_avg, E_learn_avg, E_test_avg] = run_multiple_times(C1, C2, 10, 10)

disp("====== 20 =======")
[epoch_count_avg, E_learn_avg, E_test_avg] = run_multiple_times(C1, C2, 10, 20)
