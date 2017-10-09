//Stock span problem using stacks
/*

for every "i" finds the first index "j" such that a[j] < a[i]
left_span stores above data for left side [1..i]
right_span stores the above data for right side [i..n]
these arrays contains distance between "i" && "j"
exmaple: a = [8, 7, 5, 6, 2]
left_span = [1, 2, 3, 1, 5]
right_span = [1, 1, 2, 1, 1]
*/

const int MAX = 1e5 + 5;

int a[MAX];
int left_span[MAX];
int right_span[MAX];

void stock_span(int n) {
	stack<int> s;
	s.push(1);
	left_span[1] = 1;
	for(int i = 2; i <= n; ++i) {
		while(!s.empty() && a[s.top()] >= a[i]) {
			s.pop();
		}
		if (s.empty()) {
			left_span[i] = i;
		}
		else {
			left_span[i] = i - s.top();
		}
		s.push(i);
	}
	while(!s.empty()) {
		s.pop();
	}
	s.push(n);
	right_span[n] = 1;
	for(int i = n - 1; i >= 1; --i) {
		while(!s.empty() && a[s.top()] >= a[i]) {
			s.pop();
		}
		if (s.empty()) {
			right_span[i] = n - i + 1;
		}
		else {
			right_span[i] = s.top() - i;
		}
		s.push(i);
	}
	while(!s.empty()) {
		s.pop();
	}
}