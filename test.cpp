#include <vector>
#include <numeric>
#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Strategy
{
public:
    virtual int execute(vector<int> data) = 0;
};

class Context
{
    std::map<std::string, Strategy *> strategies;
    string operation;

public:
    Context() {}

    void add_strategy(string name, Strategy *strategy)
    {
        strategies[name] = strategy;
    }
    ~Context()
    {
        delete strategy;
    }

    int execute(vector<int> &data)
    {
        return strategies[operation]->execute(data);
    }

    bool set_strategy(string operation)
    {
        // test if strategy exists
        this->operation = operation;
        return false;
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
    Context context;

    context.add_strategy("add", new ConcreteAdd);
    context.add_strategy("multiply", new ConcreteSub);

    vector<int> v = {1, 2, 3, 4, 5, 6, 7};

    if (context.set_strategy("add"))
        std::cerr << "Error: no valid strategy";

    cout << context.execute(v) << endl;
}