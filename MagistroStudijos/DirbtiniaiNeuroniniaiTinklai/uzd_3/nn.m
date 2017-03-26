#!/usr/bin/octave

L1 = load("data/Balls2A.dat")';
L2 = load("data/Balls2B.dat")';
T1 = load("data/Balls2TA.dat")';
T2 = load("data/Balls2TB.dat")';

function V = activation_func(x)
	V = 1 ./ (1 .+ e .^(-x));
endfunction

function V = activation_func_d(y)
	V = y .* (1 .- y);
endfunction

function [y_out, err] = forward_pass(w, in, desired)
	Lbefore = in;

	y_out = cell();

	y_out{1} = in;
	for i = 2:1:length(w)
		Lbefore(length(Lbefore) + 1) = 1; #Add offset

		v = w{i} * Lbefore;
		Lbefore = activation_func(v);
		y_out{i} = Lbefore;
	endfor

	err = (desired .- y_out{length(y_out)}) .^ 2;
endfunction

function dw = backward_pass(y, w, desired)
	dw = cell();
	d = cell();
	out_idx = length(y);

	# output layer delta without step
	e = desired .- y{out_idx};
	d{out_idx} = [e .* activation_func_d(y{out_idx})];
	dw{out_idx} = [d{out_idx} .* y{out_idx - 1}', d{out_idx} * 1];

	for i = length(y)-1:-1:2
		d{i} = (w{i+1}' * d{i+1})(1:length(w{i}), :);
		d{i} = d{i} .* activation_func_d(y{i});
		dw{i} = d{i} * [y{i - 1}; 1]';
	endfor

	dw{1} = zeros(length(w{1}), 1);
endfunction

function [err] = estimate_error(w, desired1, desired2, TS1, TS2)
	err = 0;
	for i = 1:1:length(TS1)
		y_out = forward_pass(w, TS1(:, i), desired1);
		if ( y_out{length(y_out)} < (desired2 - desired1) / 2 + desired1 )
			err = err +  1;
		endif
	endfor
	for i = 1:1:length(TS2)
		y_out = forward_pass(w, TS2(:, i), desired2);
		if ( y_out{length(y_out)} > (desired2 - desired1) / 2 + desired1 )
			err = err + 1;
		endif
	endfor

	err = err / (length(TS1) + length(TS2));
endfunction

# return randomly initialized weight matrices. In matrices each row corresponds for single neuron weights
function w = build_random_w(topology, B)
	w = cell();
	w{1} = ones(topology(1), 1);
	for i = 2:1:length(topology)
		w{i} = rand(topology(i), topology(i-1) + 1) * 2 * B - B;
	endfor
endfunction

w = build_random_w([2, 4, 1], 1);
e = [];
e_diff = [];
setSize = 100;

# centravimas
L1 = L1';
L2 = L2';
[ma k] = size(L1);
[mb k] = size(L2);
u = mean([L1; L2]);
L1 = L1 - ones(ma, 1) * u;
L2 = L2 - ones(mb, 1) * u;
L1 = L1';
L2 = L2';

for i=1:1:1000

	err_sum = 0;
	dw_sum = cell();
	dw_sum{1} = [0;0];
	dw_sum{2} = [0,0,0; 0,0,0; 0,0,0; 0,0,0;];
	dw_sum{3} = [0,0,0,0,0];
	setStart = 1;
	setEnd = setSize;

	for j=setStart:1:setEnd
		[y, err] = forward_pass(w, L1(:, j), 0.9);
		dw = backward_pass(y, w, 0.9);
		for k = 1:1:length(w)
			dw_sum{k} = dw_sum{k} .+ dw{k};
		endfor
		err_sum = err_sum + err;
	endfor
	for j=setStart:1:setEnd
		[y, err] = forward_pass(w, L2(:, j), 0.1);
		dw = backward_pass(y, w, 0.1);
		for k = 1:1:length(w)
			dw_sum{k} = dw_sum{k} .+ dw{k};
		endfor
		err_sum = err_sum + err;
	endfor
	err = err / (4*setSize);

	w{2} = w{2} .+ 1 .* dw_sum{2} ./ (2*setSize);
	w{3} = w{3} .+ 5 .* dw_sum{3} ./ (2*setSize);

	e = [e, err_sum];

	if i > 1
		e_diff = [e_diff, abs(e(end) - e(end - 1))];
	endif
endfor

diff = e_diff(end)
plot(e)
err = estimate_error(w, 0.9, 0.1, L1(:, 1:10), L2(:, 1:10))
err = estimate_error(w, 0.9, 0.1, T1, T2)


