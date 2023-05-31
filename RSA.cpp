//Created by Jake Blackwell and Brendan Cheng

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric> 

using namespace std;

int RSA(const int &e, const int &mod, const int &m, const vector<int> &messageList);

//vector<int> getPrimes(const int &mod);
vector<int> getPrimeFactors(const int &mod);
//vector<int> getPrimeFactors(const int &mod, const vector<int> &primes);
int getD(const int &e, const int &phi);
void decryptMessage(const vector<int> &message, const int &d, const int &mod);
bool isPublicKeyValid(const int &e, const int &phi, const vector<int> &primeFactors);
int exponentiation(int M, const int &d, const int &mod);

int main() {
	int e = 0;
	int mod = 0;
	int m = 0;
	int message = 0;
	vector<int> messageList;

	cout << "What is the Public Key?" << endl;
	cout << "e: ";
	cin >> e;
	cout << "n: ";
	cin >> mod;
	
	cout << "\nWhat is the length of the message?" << endl;
	cout << "m: ";
	cin >> m;

	cout << "\nPlease enter the message" << endl;
	cout << "ciphertext: ";


	for (int i = 0; i < m; i++) {
		cin >> message;
		messageList.push_back(message);
	}

	return RSA(e, mod, m, messageList);
}


int RSA(const int &e, const int &mod, const int &m, const vector<int> &messageList) {


	//for (int i = 0; i < m; i += 3) {
	//	messageList.push_back(stoi(message.substr(i, 3)));
	//}
	//for (int i = 0; i < messageList.size(); i++) {
	//	cout << messageList.at(i) << endl;
	//}

	vector<int> primeFactors = getPrimeFactors(mod);
	int primeFactor1 = primeFactors.at(0);
	int primeFactor2 = primeFactors.at(1);
	
	int phi = (primeFactor1 - 1) * (primeFactor2 - 1);
	cout << "Phi = " << phi << endl;

	if (!isPublicKeyValid(e, phi, primeFactors)) {
		cout << "Public key is not valid!";
		return 0;
	}

	int d = getD(e, phi);
	cout << "d = " << d << endl;
	

	//cout << primeFactor1 << " " << primeFactor2 << " " << phi << " " << d << endl;

	decryptMessage(messageList, d, mod);
/*	vector<int> message = {030, 673, 332, 785, 171, 589, 782, 171, 828, 589, 785, 568
,782 ,785 ,713 ,782 ,813 ,785 ,123, 589, 828 ,673 ,589 ,487
,589 ,785 ,813 ,890 ,243 ,813 ,785 ,733, 243, 813 ,890 ,589
,733 ,243 ,813 ,673 ,422 ,769 ,785 ,673 ,769 ,785 ,769 ,673
,733 ,171 ,828 ,589 ,291 ,785 ,673 ,813, 785 ,673 ,769 ,785
,782 ,713 ,828 ,482 ,785 ,123, 589 ,422, 243 ,500 ,769 ,589
,785 ,813 ,890 ,589 ,482 ,785 ,568 ,782, 785 ,713 ,782 ,813
,785 ,549 ,589 ,243 ,828 ,673 ,367 ,589, 785 ,890 ,782 ,587
,785 ,422 ,782 ,733 ,171 ,828, 673 ,422, 243 ,813 ,589 ,568
,785 ,828 ,673 ,332 ,589 ,785, 673 ,769 ,777 ,030
	};*/
	//size = 118
	return 0;

}

/*vector<int> getPrimes(const int& mod) {
	vector<int> primes;
	for (int i = 2; i <= sqrt(mod); i++) {
		int isComposite = 0;
		for (int prod = 2; prod < i; prod++) {
			if (i % prod == 0) {
				//cout << i << " is divisible by " << prod << endl;
				isComposite++;
			}
		}
		if (!isComposite) {
			primes.push_back(i);
		}
	}


	//cout << "Possible Primes for 1st Factor: ";
	//for (int i = 0; i < primes.size(); i++) {
	//	cout << primes.at(i) << " ";
	//}
	//cout << endl;

	return primes;
}*/

vector<int> getPrimeFactors(const int& mod) {
	vector<int> primeFactors;
	for (int i = 2; i <= sqrt(mod); i++) {
		int isComposite = 0;
		for (int prod = 2; prod < i; prod++) {
			if (i % prod == 0) {
				//cout << i << " is divisible by " << prod << endl;
				isComposite++;
			}
		}
		if (!isComposite) {
			if (mod % i == 0) {
				primeFactors.push_back(i);
				primeFactors.push_back(mod / i);
				//cout << mod << " is divisble by " << primeFactors.at(0) << " and " << primeFactors.at(1) << endl;
				break;
			}
		}
	}
	return primeFactors;
}

/*vector<int> getPrimeFactors(const int& mod, const vector<int>& primes) {
	vector<int> primeFactors;
	for (int i = 0; i < primes.size(); i++) {
		if (mod % primes.at(i) == 0) {
			primeFactors.push_back(primes.at(i));
			primeFactors.push_back(mod / primes.at(i));
			//cout << mod << " is divisble by " << primeFactors.at(0) << " and " << primeFactors.at(1) << endl;
			break;
		}
	}
	return primeFactors;
}*/

int getD(const int &e, const int &phi) {
	int i = 0;
	for (i; (((phi * i) + 1) % e) != 0; i++) {}
	//finds i when 832*i + 1 is divisible to 5 

	return ((phi * i) + 1) / e;
}

void decryptMessage(const vector<int> &message, const int &d, const int &mod) {
	vector<int> decryptedInts;
	vector<char>decryptedChars;
	//Calculate M^d % mod
	for (int i = 0; i < message.size(); i++) {
		/*int messageInt = message.at(i);
		for (int j = 1; j <= d; j++) {
			num *= messageInt;

			if (num > mod) {
				num = num % mod;
			}
		}*/
		decryptedInts.push_back(exponentiation(message.at(i), d, mod));
	}

	for (int i = 0; i < decryptedInts.size(); i++) {
		switch (decryptedInts.at(i)) {
		case 3:
			decryptedChars.push_back('A');
			break;
		case 4:
			decryptedChars.push_back('B');
			break;
		case 5:
			decryptedChars.push_back('C');
			break;
		case 6:
			decryptedChars.push_back('D');
			break;
		case 7:
			decryptedChars.push_back('E');
			break;
		case 8:
			decryptedChars.push_back('F');
			break;
		case 9:
			decryptedChars.push_back('G');
			break;
		case 10:
			decryptedChars.push_back('H');
			break;
		case 11:
			decryptedChars.push_back('I');
			break;
		case 12:
			decryptedChars.push_back('J');
			break;
		case 13:
			decryptedChars.push_back('K');
			break;
		case 14:
			decryptedChars.push_back('L');
			break;
		case 15:
			decryptedChars.push_back('M');
			break;
		case 16:
			decryptedChars.push_back('N');
			break;
		case 17:
			decryptedChars.push_back('O');
			break;
		case 18:
			decryptedChars.push_back('P');
			break;
		case 19:
			decryptedChars.push_back('Q');
			break;
		case 20:
			decryptedChars.push_back('R');
			break;
		case 21:
			decryptedChars.push_back('S');
			break;
		case 22:
			decryptedChars.push_back('T');
			break;
		case 23:
			decryptedChars.push_back('U');
			break;
		case 24:
			decryptedChars.push_back('V');
			break;
		case 25:
			decryptedChars.push_back('W');
			break;
		case 26:
			decryptedChars.push_back('X');
			break;
		case 27:
			decryptedChars.push_back('Y');
			break;
		case 28:
			decryptedChars.push_back('Z');
			break;
		case 29:
			decryptedChars.push_back(' ');
			break;
		case 30:
			decryptedChars.push_back('"');
			break;
		case 31:
			decryptedChars.push_back('.');
			break;
		case 32:
			decryptedChars.push_back(',');
			break;
		case 33:
			decryptedChars.push_back('\'');
			break;
		}
	}

	cout << "Decrypted Integers:\n";
	for (int i = 0; i < decryptedInts.size(); i++) {
		cout << decryptedInts.at(i) << " ";
	}
	cout << endl;

	cout << "Decrypted Chars:\n";
	for (int i = 0; i < decryptedChars.size(); i++) {
		cout << decryptedChars.at(i);
	}
	cout << endl;
}

bool isPublicKeyValid(const int &e, const int &phi, const vector<int> &primeFactors) {
	vector<int> primeFactorsOf2nd = getPrimeFactors(primeFactors.at(1));

	if ((gcd(e,phi) != 1) || (primeFactors.at(0) == primeFactors.at(1)) || primeFactorsOf2nd.size() > 1) {
		return false;
	}
	else {
		return true;
	}
}

int exponentiation(int M, const int& d, const int& mod) {
	int power = d;
	vector<int> coeff;

	while (power > 0) {
		if (power % 2 == 1) { //odd powers
			coeff.push_back(M);
			power--;
		}
		power = power / 2;
		M = (int)pow(M, 2) % mod;
	}

	int prod = 1;
	for (int i = 0; i < coeff.size(); i++) {
		prod *= coeff.at(i);
		prod = prod % mod;
	}

	return prod;
}