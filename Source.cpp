#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
 
class Perceptron
{
private:
 double result;
 vector<double> sm;
 vector<double> weights;
 double b;
 double s;
public:
 Perceptron(int n = 2)
 {
  for (int i = 0; i < n; ++i)
  {
   weights.push_back((rand() % 1000 - 500) / 1000.);
  }
  b = (rand() % 1000 - 500) / 1000.;
 }
 
 double process(vector<double>& x)
 {
  s = b;
  for (int i = 0; i < x.size(); ++i)
  {
   s += x[i] * weights[i];
  }
  result = activationFunction(s);
  sm = x;
  return result;
 }
 
 double activationFunction(double aS)
 {
  return 1. / (1. + exp(-aS));
 }
 
 double dActivationFunction(double aS)
 {
  return activationFunction(aS) * (1 - activationFunction(aS));
 }
 
 void learn(double n)
 {
  double error = n - result;
  double tetta = error * dActivationFunction(s);
  for (int i = 0; i < weights.size(); ++i)
  {
   weights[i] += tetta * sm[i] * 0.3f;
  }
  b += tetta;
 }
};
void getAnswer(int a, int b, vector<double>& answer)
{
 int result = a + b;
 answer[result] = 0.5f;
 for (int i = result - 1; i >= 0; --i)
 {
  answer[i] = answer[i + 1] - 0.5f / answer.size();
 }
 for (int i = result + 1; i < answer.size(); ++i)
 {
  answer[i] = answer[i - 1] + 0.5f / answer.size();
 }
}
int main()
{
 srand(time(0));
 vector<Perceptron> perceptrons(200, Perceptron(2));
 int agr = 0;
 int disagr = 0;
 vector<double> answer(200);
 while (true)
 {
  for (double i = 0; i < 100; i++)
  {
   for (double j = 0; j < 100; j++)
   {
    vector<double> temp_l = { i, j };
    
    getAnswer(i, j, answer);
    int winner = -1;
    float minimum = 1.;
    for (int k = 0; k < 200; k++)
    {
     double temp = perceptrons[k].process(temp_l);
     if (abs(temp - 0.5f) < minimum)
     {
      minimum = abs(temp - 0.5f);
      winner = k;
     }
     perceptrons[k].learn(answer[k]);
    }
    if (winner == i + j) agr++;
    else disagr++;
   }
  }
  cout << agr << ' ' << disagr << endl;
  agr = 0;
  disagr = 0;
 }
}
