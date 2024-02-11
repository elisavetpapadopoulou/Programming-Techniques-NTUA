/*
 * Polynomial.cpp
 *
 *  Created on: 17 Apr 2021
 *      Author: elisa
 */

#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
protected:
	class Term {
	public:
		int exponent;
		int coefficient;
		Term *next;
		Term(int exp, int coeff, Term *n) {
			exponent = exp;
			coefficient = coeff;
			next = n;
		}
		friend class Polynomial;
	};
	Term *head, *assistant;

public:
	Polynomial();
	Polynomial(const Polynomial &p);
	~Polynomial();

	Polynomial & operator = (const Polynomial &p) {
		Term *helper;
		this->~Polynomial();
		helper = p.head;
		while (helper != nullptr) {
			this->addTerm(helper->exponent, helper->coefficient);
			helper = helper->next;
		}
		return *this;
	}

	void addTerm(int expon, int coeff);
	double evaluate(double x);

	friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) ;

	friend Polynomial operator* (const Polynomial &p, const Polynomial &q);

	friend ostream & operator << (ostream &out, const Polynomial &p);

};


Polynomial::Polynomial() {
	head = nullptr;
	assistant = nullptr;
}

Polynomial::Polynomial(const Polynomial &p) {
	head = assistant = nullptr;
	Term *passistant;
	passistant = p.head;

	while (passistant != nullptr) {
		Term *term = new Term(passistant->exponent, passistant->coefficient, nullptr);
		if (head == nullptr) {
			head = term;
			assistant = term;
		}
		else {
			assistant->next = term;
			assistant = term;
		}
		passistant = passistant->next;
	}
	assistant = head;
}

Polynomial::~Polynomial() {
	while (assistant != nullptr){
		Term *p = assistant;
		assistant = assistant->next;
		delete p;
	}
	assistant = head = nullptr;
}

void Polynomial::addTerm(int expon, int coeff) {
	if (coeff != 0) {
		Term *term = new Term(expon, coeff, nullptr);
		if (head == nullptr) {
			head = term;
			assistant = term;
		}
		else {
			if (expon > assistant->exponent) {
				term->next = head;
				assistant = term;
				head = term;
			}
			else if (expon == assistant->exponent) {
				if (assistant->coefficient + coeff != 0)
					assistant->coefficient += coeff;
				else {
					Term *p;
					p = assistant;
					if (p == head)
						head = assistant->next;
					assistant = assistant->next;
					delete p;
				}
				delete term;
			}
			else  {
				while (assistant->next != nullptr) {
					if (assistant->next->exponent > expon) {
						assistant = assistant->next;
					}
					else break;
				}
				if (assistant->next == nullptr or (assistant->next)->exponent < expon){
					term->next = assistant->next;
					assistant->next = term;
				}
				else if (assistant->next->exponent == expon) {
					if (assistant->next->coefficient + coeff != 0)
						assistant->next->coefficient += coeff;
					else {
						Term *n;
						n = assistant->next;
						assistant->next = assistant->next->next;
						delete n;
					}
					delete term;
				}
			}
			assistant = head;
	}
}
}

double Polynomial::evaluate(double x) {
	double sum = 0;
	while(assistant != nullptr) {
		sum += (assistant->coefficient)*pow(x, assistant->exponent);
		assistant = assistant->next;
	}
	assistant = head;
	return sum;
}

Polynomial operator+ (const Polynomial &p, const Polynomial &q) {
	Polynomial result;
	Polynomial::Term *passistant, *qassistant;
	int pexp, qexp, pcoeff, qcoeff, exp, coeff;

	passistant = p.head;
	qassistant = q.head;

	if (q.head != nullptr) {
		if (p.head == nullptr) {
			result = q;
			return result;
		}
		else {
			qexp = qassistant->exponent;
			qcoeff = qassistant->coefficient;
		}
	}

	if (p.head != nullptr) {
		if (q.head == nullptr) {
			result = p;
			return result;
		}
		else {
			pexp = passistant->exponent;
			pcoeff = passistant->coefficient;
		}
	}

	while (passistant != nullptr and qassistant != nullptr) {
		if (pexp == qexp) {
			exp = pexp;
			coeff = qcoeff + pcoeff;
			passistant = passistant->next;
			qassistant = qassistant->next;
			if (passistant != nullptr) {
				pexp = passistant->exponent;
			    pcoeff = passistant->coefficient;
			}
			if (qassistant != nullptr) {
			   qexp = qassistant->exponent;
			   qcoeff = qassistant->coefficient;
			}
			result.addTerm(exp, coeff);
			continue;
		}

		else if (pexp > qexp) {
			exp = pexp;
			coeff = pcoeff;
			passistant = passistant->next;
			if (passistant != nullptr) {
				pexp = passistant->exponent;
				pcoeff = passistant->coefficient;
			}
			result.addTerm(exp, coeff);
			continue;
		}

		else if (pexp < qexp) {
			exp = qexp;
			coeff = qcoeff;
			qassistant = qassistant->next;
			if (qassistant != nullptr) {
				qexp = qassistant->exponent;
				qcoeff = qassistant->coefficient;
			}
			result.addTerm(exp, coeff);
			continue;
		}
	}

	while (passistant != nullptr) {
		exp = passistant->exponent;
		coeff = passistant->coefficient;
		passistant = passistant->next;
		result.addTerm(exp, coeff);
	}
	while (qassistant != nullptr) {
		exp = qassistant->exponent;
		coeff = qassistant->coefficient;
		qassistant = qassistant->next;
		result.addTerm(exp, coeff);
	}
	return result;
}

Polynomial operator* (const Polynomial &p, const Polynomial &q) {
	int exp, coeff, pexp, pcoeff, qexp, qcoeff;
	Polynomial result;
	Polynomial::Term *passistant, *qassistant;
	passistant = p.assistant;
	qassistant = q.assistant;

	while(passistant != nullptr) {

		pexp = passistant->exponent;
		pcoeff = passistant->coefficient;
		while (qassistant != nullptr) {
			qexp = qassistant->exponent;
			qcoeff = qassistant->coefficient;

			exp = pexp + qexp;
			coeff = pcoeff*qcoeff;
			result.addTerm(exp, coeff);
			qassistant = qassistant->next;

		}

		qassistant = q.head;
		passistant = passistant->next;
	}
		result.assistant = result.head;
		return result;
}

ostream & operator<< (ostream &out, const Polynomial &p) {
	Polynomial::Term *passistant;
	passistant = p.assistant;
	if (passistant == nullptr)
		cout << 0;
	while (passistant != nullptr) {
		if (passistant->coefficient > 0 and passistant != p.head)
			cout << "+ ";
		else if (passistant->coefficient < 0) {
			cout << "- ";
			if (passistant->coefficient < -1 or (passistant->coefficient <= -1 and passistant->exponent == 0))
			cout << abs(passistant->coefficient);
		}
		if (passistant->coefficient > 1 or (passistant->coefficient >= 1 and passistant->exponent == 0))
			cout << passistant->coefficient;
		if (passistant->exponent != 0) {
			cout << "x";
			if (passistant->exponent > 1) {
				cout << "^";
				cout << passistant->exponent;
			}
	}
		if (passistant->next != nullptr)
			cout << " ";
		passistant = passistant->next;
}
	return out;
}

/*int main() {
	 Polynomial p; // 0
	 p.addTerm(1, 3); // 3x

	 p.addTerm(2, 1); // x^2
	 p.addTerm(0, -1); // -1

	 Polynomial q(p); // x^2 + 3x - 1
	 q.addTerm(1, -3); // -3x

	 Polynomial s, h, fuck;
	 s.addTerm(1, 1);
	 s.addTerm(0, 1);
	 h.addTerm(1, 1);
	 h.addTerm(0, -1);

	 cout << "P(x) = " << p << endl;
	 cout << "P(1) = " << p.evaluate(1) << endl;
	 cout << "Q(x) = " << q << endl;
	 cout << "Q(1) = " << q.evaluate(1) << endl;
	 cout << "(P+Q)(x) = " << p+q << endl;
	 cout << "(P*Q)(x) = " << p*q << endl;
	 cout << "(S+H)(x) = " << s+h << endl;
	 fuck.addTerm(2, 1);
	 fuck.addTerm(1, -1);
	 fuck.addTerm(2, -1);
	 fuck.addTerm(1, 1);
	 cout << "FUCK(x) = " << fuck << endl;
}
*/

