#include <cstdio>
#include <memory>
#include <string>
#include <vector>

// Forward declarations (cyclic Visitor <-> Element dependency)
class SavingsAccount;
class CheckingAccount;
class Loan;

// 1. Visitor interface
// 2b. Second dispatch target (dynamic on Visitor,
//     static overload picked by caller)
class Visitor {
  public:
    virtual void visit(const SavingsAccount *) = 0;
    virtual void visit(const CheckingAccount *) = 0;
    virtual void visit(const Loan *) = 0;
    virtual ~Visitor() = default;
};

// 2. Visitable / Element interface
class BankAsset {
  public:
    virtual void accept(Visitor &) = 0;
    virtual ~BankAsset() = default;
};

// 3. ConcreteElements (stable types)
class SavingsAccount : public BankAsset {
  public:
    std::string owner;
    double balance, rate;
    SavingsAccount(std::string o, double b, double r) : owner(std::move(o)), balance(b), rate(r) {}
    // STATIC: overload picked at compile-time (this is SavingsAccount*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }

    // Rest of the element logic...
};

class CheckingAccount : public BankAsset {
  public:
    std::string owner;
    double balance;
    CheckingAccount(std::string o, double b) : owner(std::move(o)), balance(b) {}
    // STATIC: overload picked at compile-time (this is CheckingAccount*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }

    // Rest of the element logic...
};

class Loan : public BankAsset {
  public:
    std::string owner;
    double principal, rate;
    Loan(std::string o, double p, double r) : owner(std::move(o)), principal(p), rate(r) {}
    // STATIC: overload picked at compile-time (this is Loan*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }

    // Rest of the element logic...
};

// 4. ConcreteVisitors (stable types)
class InterestCalculator : public Visitor {
  public:
    double total_interest = 0.0;
    void visit(const SavingsAccount *s) override {
        total_interest += s->balance * s->rate; // Behaviour for SavingsAccount element
    }
    void visit(const CheckingAccount *) override {} // NO Behaviour for CheckingAccounts element
    void visit(const Loan *l) override {
        total_interest += l->principal * l->rate; // Behaviour for Loan element
    }
};

class MonthlyFeeCalculator : public Visitor {
  public:
    double total_fees = 0.0;
    void visit(const SavingsAccount *) override {} // NO Behaviour for SavingsAccounts element
    void visit(const CheckingAccount *c) override {
        if (c->balance < 1000.0) {
            total_fees += 5.0; // Behaviour for CheckingAccounts element
        }
    }
    void visit(const Loan *) override { total_fees += 10.0; } // Behaviour for Loan element
};

class TaxReportExporter : public Visitor {
  public:
    void visit(const SavingsAccount *s) override {
        std::printf("TAX savings %s interest %g\n", s->owner.c_str(), s->balance * s->rate);
    }
    void visit(const CheckingAccount *c) override {
        std::printf("TAX checking %s interest 0\n", c->owner.c_str());
    }
    void visit(const Loan *l) override {
        std::printf("TAX loan %s deductible %g\n", l->owner.c_str(), l->principal * l->rate);
    }
};

class StatementExporter : public Visitor {
  public:
    void visit(const SavingsAccount *s) override {
        std::printf("STMT savings %s balance %g\n", s->owner.c_str(), s->balance);
    }
    void visit(const CheckingAccount *c) override {
        std::printf("STMT checking %s balance %g\n", c->owner.c_str(), c->balance);
    }
    void visit(const Loan *l) override {
        std::printf("STMT loan %s owed %g\n", l->owner.c_str(), l->principal);
    }
};

// 5. ObjectStructure + 6. Client
class Portfolio {
    std::vector<std::unique_ptr<BankAsset>> assets;

  public:
    void add(std::unique_ptr<BankAsset> a) { assets.push_back(std::move(a)); }
    void accept(Visitor &v) {
        // Dispatch 1 (dynamic): virtual picks
        // Savings/Checking/Loan::accept at runtime
        for (auto &a : assets)
            a->accept(v);
    }
};

int main() {
    Portfolio portfolio;
    portfolio.add(std::make_unique<SavingsAccount>("alice", 5000.0, 0.03));
    portfolio.add(std::make_unique<CheckingAccount>("bob", 800.0));
    portfolio.add(std::make_unique<Loan>("carol", 10000.0, 0.07));

    InterestCalculator interest;
    // Client: same call, concrete visitor (InterestCalculator) at runtime
    portfolio.accept(interest);
    std::printf("Net interest: %.2f\n", interest.total_interest);

    MonthlyFeeCalculator fees;
    // Client: same call, concrete visitor (MonthlyFeeCalculator) at runtime
    portfolio.accept(fees);
    std::printf("Total fees: %.2f\n", fees.total_fees);

    TaxReportExporter tax;
    // Client: same call, concrete visitor (TaxReportExporter) at runtime
    portfolio.accept(tax);

    StatementExporter stmt;
    // Client: same call, concrete visitor (StatementExporter) at runtime
    portfolio.accept(stmt);
};
