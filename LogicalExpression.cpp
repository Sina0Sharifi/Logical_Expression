#include <iostream>
#include <String>
using namespace std;
template <class T , int MAX> class MyStack {
	int top = -1;
public:
	T s[MAX]{};
	void push(T num) {
		if (top != MAX)
			s[++top] = num;
		else
			exit(0);
	}

	bool empty() {
		return top == -1;
	}

	T pop() {
		if (!this->empty())
			return s[top--];
		else
			return 0;
	}
	T peek() {
		if (!this->empty())
			return s[top];
		else
			return 0;
	}
};
bool operatorr(int&, char, char);
bool result(bool, char, bool);
int main() {
	while (1) {
		int parantez = 0;
		MyStack<bool,100> stack1, stack2;
		MyStack<char,100> stack3;
		string LogicalExpression;
		int i = 0;
		bool boolean;
		cin >> LogicalExpression;
		int str = LogicalExpression.length() - 1;
		bool* arr;
		arr = new bool[str + 1];
		for (short int j = 0; j <= str; j++) {
			bool b = 0;
			if (isalpha(LogicalExpression[j])) {
				for (short int k = 0; k < j; k++) {
					if (LogicalExpression[j] == LogicalExpression[k]) {
						arr[j] = arr[k];
						b = 1;
						break;
					}
				}
				if (b == 1)
					continue;
				cout << "enter " << LogicalExpression[j] << endl;
				cin >> boolean;
				arr[j] = boolean;
			}
		}
		while (i <= str) {
			if (isalpha(LogicalExpression[i])) {
				stack1.push(arr[i]);
			}
			else {
				if (LogicalExpression[i] == ')') {
					while (stack3.peek() != '(')
					{
						if (stack3.peek() == '!')
							stack1.push(result(stack1.pop(), stack3.pop(), 0));
						else
							stack1.push(result(stack1.pop(), stack3.pop(), stack1.pop()));
					}
					char a = stack3.pop();
					parantez = parantez - 5;
				}
				else if (stack3.empty()) {
					if (LogicalExpression[i] == '(')
						parantez = 5 + parantez;
					stack3.push(LogicalExpression[i]);
				}
				else if (!stack3.empty() && operatorr(parantez, stack3.peek(), LogicalExpression[i])) {
					if (LogicalExpression[i] == '(')
						parantez = 5 + parantez;
					stack3.push(LogicalExpression[i]);
				}
				else
				{
					while (!operatorr(parantez, stack3.peek(), LogicalExpression[i]) && !stack3.empty()) {
						if (stack3.peek() == '!')
							stack1.push(result(stack1.pop(), stack3.pop(), 0));
						else
							stack1.push(result(stack1.pop(), stack3.pop(), stack1.pop()));
					}
					stack3.push(LogicalExpression[i]);
				}
			}
			i++;
		}
	delete[] arr;
	arr = NULL;
		while (!stack3.empty()) {
			if (stack3.peek() == '!')
				stack1.push(result(stack1.pop(), stack3.pop(),0));
			else
				stack1.push(result(stack1.pop(), stack3.pop(), stack1.pop()));
		}
		cout << "finish =" << stack1.pop()<<endl;
	}
}
bool operatorr(int& parantez, char p, char in) {
	char op[] = { '#','~','|','^','!','(' };
	short int a = -1, b = -1;
	if (p == '(')
		return true;
	if (in == '!')
		return true;
	for (short int i = 0; a == -1 || b == -1; i++) {
		if (p == op[i])
			a = i + parantez;
		if (in == op[i])
			b = i + parantez;
	}
	if (a < b)
		return true;
	else
		return false;
}
bool result(bool b, char c, bool a) {
	switch (c) {
	case '^':
		return(a && b);
		break;
	case '|':
		return(a || b);
		break;
	case '~':
		if (a && (!b))
			return(0);
		else
			return(1);
		break;
	case '#':
		if (a == b)
			return(1);
		else
			return(0);
		break;
	case'!':
		bool d = !b;
		return(d);
		break;
	}
}