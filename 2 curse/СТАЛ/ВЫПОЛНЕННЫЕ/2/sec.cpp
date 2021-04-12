#include<iostream>
#include<string>
using namespace std;

void subtraction(int* mass1,int* mass2, int* mass, int size);
void reWrite(string str, int* mass, int size);
void subConverting(int* mass, int size);
void summing(int* mass1,int* mass2, int* mass, int size);
void sumConverting(int* mass, int size);
int compare(int* mass1, int* mass2, int n);
void zeroing(int* mass, int size, int l);

int main(){
	unsigned int size = 0;
	string num1, num2;
	char ans, sign1 = '\0', sign2 = '\0', sign = '\0';
	unsigned short int larger = 0, p = 0, z = 0;
	
m2:	cout << "   \nWARNING! First element must be sign! (+ or -)\n\nEnter first  number: ";
	cin >> num1;
	cout << "Enter second number: ";
	cin >> num2;
	
	if(num1.length() == 1 || num2.length() == 1){
		cout << "\n\n     You entered sign(s) only!\n\n";
		return 0;
	};
	
	if(num1.length() > num2.length()){
		size = num1.length();
	}else{
		size = num2.length();
	}
	
	int* mass1 = new int [size+1];
	int* mass2 = new int[size+1];
	int* result = new int [size+1];
	
	reWrite(num1, mass1, size);
	reWrite(num2, mass2, size);
	
	zeroing(mass1, size, num1.length());
	zeroing(mass2, size, num2.length());
	
	sign1 = num1[0];
	sign2 = num2[0];
	
	larger = compare(mass1, mass2, size);
	
	
	if(larger == 0 && sign1 == sign2){
		cout << "\n\n     Subtraction is equal: 0\n\n";
		goto m3;
		return 0;
	}
	
	if((sign1 == '+') && (sign2 == '+')){
		if(larger == 1){
			subtraction(mass1, mass2, result, size);
			sign = '+';
			goto m1;
		} else{
			subtraction(mass2, mass1, result, size);
			sign = '-';
			goto m1;
		}
	};
	if((sign1 == '-') && (sign2 == '-')){
		if(larger == 1){
			subtraction(mass1, mass2, result, size);
			sign = '-';
			goto m1;
		} else{
			subtraction(mass2, mass1, result, size);
			sign = '+';
		}
	};
    if((sign1 == '+') && (sign2 == '-')){
		if(larger == 1){
			summing(mass1, mass2, result, size);
			p = 1;
			sign = '+';
			goto m1;
		} else{
			summing(mass2, mass1, result, size);
			p = 1;
			sign = '+';
			goto m1;
		}
	};
	if((sign1 == '-') && (sign2 == '+')){
		if(larger == 1){
			summing(mass1, mass2, result, size);
			p = 1;
			sign = '-';
			goto m1;
		} else{
			summing(mass2, mass1, result, size);
			p = 1;
			sign = '-';
			goto m1;
		}
	}
	
m1:	cout << "\n\n     Subtraction is equal: " << sign;
	for(int i = 1; i < size+p; i++){
		if(result[i] == 0)
		{
			z++;
		}else{
			break;
		}
	}
	for(int i = z+1; i < size+p; i++){
		cout << result[i];
	}
	
	cout << "\n\n";
	
	num1 = "\0";
	num2 = "\0";
	sign = '\0';
	z = 0;
	delete(mass1);
	delete(mass2);
	delete(result);
	
m3:	cout << "Do you want to continue? (y or n) ";
	cin >> ans;
	cout << "\n";
	if(ans == 'y')
	{
		goto m2;
	}
	return 0;
}

void subtraction(int* mass1, int* mass2, int* mass, int size){//вычитание
	for(int i = size-1; i >= 0; i--) {
		mass[i] = mass1[i] - mass2[i];
	}
	subConverting(mass, size);
}

void zeroing(int* mass, int size, int l){ //обнуление первых элементов массива
	for(int i = size-l; i>=0; i--){
		mass[i] = 0;
	}
}

void summing(int* mass1, int* mass2, int* mass, int size){// сложение
	for(int i = size-1; i >= 0; i--){
		mass[i] = mass1[i] + mass2[i];
	}
	sumConverting(mass, size);
}

int compare(int* mass1, int* mass2, int n){ //сравнение по модулю
	int k = 0;
	for(int i = 1; i < n; i++){
		if(mass1[i] > mass2[i]){
			k = 1;
			return k;
		}else{
			if(mass1[i] < mass2[i]){
				k = 2;
				return k;
			}
		}
	}
	return k;
}

void subConverting(int* mass, int size){//преобразование после вычитания
	int l = 1;
	
	for(int i = size-1; i >= 0; i--){
		if(mass[i] == -1){
			while(1){
				if(mass[i-l] == 1){
					mass[i] = 1;
					mass[i-l] = 0;
					break;
				} else{
					mass[i-l] += 1;
					l++;
				}
			}
		}
		l = 0;
	}
}

void sumConverting(int* mass, int size){//преобразование после сложения
	for(int i = size; i >= 1; i--){
		mass[i] = mass[i-1];
	}
	mass[1] = 0;
	int l =1;
	
	for(int i = size; i >= 1; i--){
		if(mass[i] == 2){
			while(1){
				if(mass[i-l] == 0){
					mass[i] = 0;
					mass[i-l] = 1;
					break;
				} else{
					mass[i-l] -= 1;
					l++;
				}
			}
		}
		l = 0;
	}
}

void reWrite(string str, int* mass, int size){// перезапись чисел из string в целочисленный массив
	int p = str.length();
	for(int i = size; i > 0; i--){
		mass[i] = str[p] - '0';
		p--;
	    if(p == -1){
		    break;
	    }
	}
}