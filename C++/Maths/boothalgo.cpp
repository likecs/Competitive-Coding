#include <bits/stdc++.h>

using namspace std;

void add(int ac[], int x[], int qrn) {
	int i, c = 0;
	for (i = 0; i < qrn; i++) {
		ac[i] = ac[i] + x[i] + c;
		if (ac[i] > 1) {
			ac[i] = ac[i] % 2;
			c = 1;
		}
		else c = 0;
	}
}

void complement(int a[], int n) {
	int i;
	int x[8] = {};
	x[0] = 1;
	for (i = 0; i < n; i++) a[i] = (a[i]+1)%2;
	add(a, x, n);
}

void ashr(int ac[], int qr[], int &qn, int qrn) {
	int temp, i;
	temp = ac[0];
	qn = qr[0];
	cout << "\t\tashr\t\t";
	for (i = 0; i < qrn - 1; i++) {
		ac[i] = ac[i+1];
		qr[i] = qr[i+1];
	}
	qr[qrn-1] = temp;
}

void display(int ac[], int qr[], int qrn) {
	int i;
	for (i = qrn - 1; i >= 0; i--) cout << ac[i];
	cout << " ";
	for (i = qrn - 1; i >= 0; i--) cout << qr[i];
}

int main() {
	int mt[10], br[10], qr[10], sc, ac[10] = { 0 };
	int brn, qrn, i, qn, temp;
	cout << "\n--Enter the multiplicand and multipier in signed 2's complement form if negative--";
	cout << "\n Number of multiplicand bit=";
	cin >> brn;
	cout << "\nmultiplicand=";
	for (i = brn - 1; i >= 0; i--)
		cin >> br[i]; //multiplicand
	for (i = brn - 1; i >= 0; i--)
		mt[i] = br[i]; // copy multipier to temp array mt[]
	complement(mt, brn);
	cout << "\nNo. of multiplier bit=";
	cin >> qrn;
	sc = qrn; //sequence counter
	cout << "Multiplier=";
	for (i = qrn - 1; i >= 0; i--)
		cin >> qr[i]; //multiplier
	qn = 0;
	temp = 0;
	cout << "qn\tq[n+1]\t\tBR\t\tAC\tQR\t\tsc\n";
	cout << "\t\t\tinitial\t\t";
	display(ac, qr, qrn);
	cout << "\t\t" << sc << "\n";
	while (sc != 0) {
		cout << qr[0] << "\t" << qn;
		if ((qn + qr[0]) == 1) {
			if (temp == 0) {
				add(ac, mt, qrn);
				cout << "\t\tsubtracting BR\t";
				for (i = qrn - 1; i >= 0; i--) cout << ac[i];
				temp = 1;
			}
			else if (temp == 1) {
				add(ac, br, qrn);
				cout << "\t\tadding BR\t";
				for (i = qrn - 1; i >= 0; i--) cout << ac[i];
				temp = 0;
			}
			cout << "\n\t";
			ashr(ac, qr, qn, qrn);
		}
		else if (qn - qr[0] == 0) ashr(ac, qr, qn, qrn);
		display(ac, qr, qrn);
		cout << "\t";
		sc--;
		cout << "\t" << sc << "\n";
	}
	cout << "Result=";
	display(ac, qr, qrn);
}