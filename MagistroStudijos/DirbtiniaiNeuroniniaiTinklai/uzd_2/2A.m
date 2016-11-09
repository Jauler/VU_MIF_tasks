#!/usr/bin/octave

L1 = load("A9.dat")';
L2 = load("B9.dat")';
T1 = load("C9.dat")';
T2 = load("D9.dat")';

L1(3, :) = ones(1, length(L1(1, :)));
L2(3, :) = ones(1, length(L2(1, :)));
T1(3, :) = ones(1, length(T1(1, :)));
T2(3, :) = ones(1, length(T2(1, :)));

function [w_new, changed] = perceptron_iteration(w, x, c, step)
	pred = w' * x;

	if (pred > 0 && c == 1) || (pred <= 0 && c == 2)
		w_new = w;
		changed = false;
	elseif pred < 0 && c == 1
		w_new = w + step * x;
		changed = true;
	elseif pred >= 0 && c == 2
		w_new = w - step * x;
		changed = true;
	endif
endfunction

function [w_new, change_count] = run_epoch(w, L1, L2, step)
	w_new = w;
	change_count = 0;
	for i = 1:1:length(L1)
		[w_new, changed] = perceptron_iteration(w_new, L1(:, i), 1, step);
		if changed
			change_count = change_count + 1;
		endif

		[w_new, changed] = perceptron_iteration(w_new, L2(:, i), 2, step);
		if changed
			change_count = change_count + 1;
		endif
	endfor
endfunction

function [sum_change_count, epoch_idx, err, w] = learn(w, L1, L2, T1, T2, step)
	epoch_idx = 0;
	sum_change_count = 0;
	do
		[w, changed_count] = run_epoch(w, L1, L2, step);
		epoch_idx = epoch_idx + 1;
		sum_change_count = sum_change_count + changed_count;
	until (changed_count <= 0)

	err = 0.0;
	len = length(T1(1, :));
	for i = 1:1:len
		if w' * T1(:, i) <= 0
			err = err + 1;
		endif
	endfor

	len = length(T2(1, :));
	for i = 1:1:len
		if w' * T2(:, i) > 0
			err = err + 1;
		endif
	endfor
	err = err * 100 / (length(T1) + length(T2));
endfunction

w_init = [1, 1, 1]'
disp("==========")
niu = 0.1
[sum_change_count, epoch_idx, err, w] = learn(w_init, L1, L2, T1, T2, niu)
disp("==========")
niu = 1
[sum_change_count, epoch_idx, err, w] = learn(w_init, L1, L2, T1, T2, niu)
disp("==========")
niu = 10
[sum_change_count, epoch_idx, err, w] = learn(w_init, L1, L2, T1, T2, niu)



