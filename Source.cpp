#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Perceptron
{
private:
	vector<double> sm;
	vector<double> weight;
	double result;
	vector<double> signals;
	double b;
public:
	Perceptron(int n = 2) {
		for (int i = 0; i < n; i++)
		{
			weight.push_back((rand() % 101 - 50) - 100);
		}
	}
	double process(vector<double>& x) {
		int sum = b;
		for (int i = 0; i < x.size(); ++i) {
			sum += x[i] * weight[i];
		}
		result = activationFunction(sum);
		sm = x;
		return result;
	}
	double activationFunction(double sum) {
		return 1. / (1. + exp(-sum));
	}
	double dactivationFunction(double sum) {
		return activationFunction(sum) * (1. - activationFunction(sum));
	}

	void learn(int n) {
		double error = n - result;
		double tetta = error * dactivationFunction(result);
		for (int i = 0; i < weight.size(); ++i)
		{
			weight[i] += tetta * sm[i] * 0.3f;
		}
		b += tetta * 0.3f;

	}
};
int main()
{

	vector<double> answ;
	vector<double> a = { 50, 28 };
	vector<Perceptron> perceptrons;
	for (int i = 0; i < 500; ++i)
	{
		answ.push_back(0);
		perceptrons.push_back(Perceptron(2));
	}
	answ[a[0] + a[1]] = 0.5f;
	for (int i = a[0] + a[1] - 1; i > 0; --i)
	{
		answ[i] = answ[i + 1] - 0.5f / 500;
		cout << answ[i] << ' ';
	}
	cout << endl;
	for (int i = a[0] + a[1] + 1; i < 500; ++i)
	{
		answ[i] = answ[i - 1] + 0.5f / 500;
		cout << answ[i] << ' ';
	}
	int right = 0;
	int neright = 0;
	while (true)
	{
		for (double i = 0; i < 250; ++i)
		{

			for (double j = 0; j < 250; ++j)
			{
				vector<double> temp = { i,j };
				for (int k = 0; k < 500; ++k)
				{
					double answ_l = perceptrons[k].process(temp);
					if (abs(0.5f - answ_l) == 0.5f) right++;
					else neright++;
					cout << right << ' ';
					cout << neright << endl;
					perceptrons[k].learn(answ[k]);
				}
			}
		}
	}
}