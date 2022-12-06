#include <vector>
#include <numeric>
#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Strategy
{
public:
    virtual int execute() = 0;
};

class Context
{
    std::map<std::string, Strategy> strategies;

public:
    Context(Strategy *const s) : strategy(s) {}

    void add_strategy(string name, Strategy &strategy)
    {
        strategies[name] = strategy;
    }
    ~Context()
    {
        delete strategy;
    }

    int execute(string operation, vector<int> &data)
    {
        return strategies[operation].execute(data);
    }

private:
    Strategy *strategy;
};

class ConcreteAdd : public Strategy
{
public:
    int execute(vector<int> v)
    {
        cout << "Add" << endl;
        return std::accumulate(v.begin(), v.end(), 0);
    }
};

class ConcreteSub : public Strategy
{
public:
    int execute(vector<int> v)
    {
        cout << "Subb" << endl;
        return std::accumulate(v.begin(), v.end(), 0);
    }
};

int main()
{
    Context context();
    context.add_strategy("add", ConcreteAdd());
    context.add_strategy("multiply", ConcreteSub());

    vector<int> v = {1, 2, 3, 4, 5, 6, 7};

    if (context.set_strategy('add'))
        std::cout << context.execute(v) else std::cerr << "Error: no valid strategy";

    Context context(new ConcreteAdd::execute(v));
    context.contextInterface();
}