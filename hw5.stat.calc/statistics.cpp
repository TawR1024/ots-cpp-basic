#include <iostream>
#include <limits>
#include <vector>

class IStatistics
{
   public:
    virtual ~IStatistics () {}

    virtual void        update (double next) = 0;
    virtual double      eval () const        = 0;
    virtual const char* name () const        = 0;
};

class Min : public IStatistics
{
   public:
    Min () : m_min{std::numeric_limits<double>::max ()} {}

    void update (double next) override
    {
        if (next < m_min)
        {
            m_min = next;
        }
    }
    double eval () const override { return m_min; }

    const char* name () const override { return "min"; }

   private:
    double m_min;
};

class Max : public IStatistics
{
   public:
    Max ()
        : _max{std::numeric_limits<double>::min ()} {
          };  // init with as minimal as pissible value; so any value will be more then it.

    void update (double next) override
    {
        if (next > _max)
        {
            _max = next;
        }
    }

    double eval () const override { return _max; }

    const char* name () const override { return "max"; }

   private:
    double _max;
};

class Mean : public IStatistics
{
   public:
    Mean () : _mean{0.0}, _count{0} {}

    double eval () const override { return _mean; }

    const char* name () const override { return "mean"; }

    void update (double next) override
    {
        _count++;
        _mean = _mean + (next - _mean) / _count;
    }

   private:
    double   _mean;
    uint64_t _count;
};

class Std : public IStatistics
{
   public:
    Std () : _sum{0.0}, _sum_squares{0.0}, _count{0} {};

    void update (double next) override
    {
        _count++;
        _sum += next;
        _sum_squares += next * next;
    }

    double eval () const override
    {
        if (_count <= 1)
            return 0.0;  // std for 1 element is always 0;
        double mean     = _sum / _count;
        double variance = (_sum_squares / _count) - (mean * mean);
        return std::sqrt (variance);
    }

    const char* name () const override { return "std"; }

   private:
    double   _sum;
    double   _sum_squares;
    uint64_t _count;
};

int main ()
{
    std::vector<IStatistics*> metrics = {
        new Min (),
        new Max (),
        new Mean (),
        new Std (),
    };

    double val = 0;
    while (std::cin >> val)
    {
        for (auto metric : metrics)
        {
            metric->update (val);
        }
    }

    // Handle invalid input data
    if (!std::cin.eof () && !std::cin.good ())
    {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (auto metric : metrics)
    {
        std::cout << metric->name () << " = " << metric->eval () << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (auto metric : metrics)
    {
        delete metric;
    }

    return 0;
}