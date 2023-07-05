#include <vector>
#include <string>
#include <list>
#include <tuple>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

class Attr
{ // Base class for attributes
public:
    virtual bool operator==(const Attr &right) = 0;
    virtual bool operator!=(const Attr &right) = 0;
    virtual bool operator<(const Attr &right) = 0;
    virtual bool operator<=(const Attr &right) = 0;
    virtual bool operator>(const Attr &right) = 0;
    virtual bool operator>=(const Attr &right) = 0;
};

class integerAttribute : public Attr
{
private:
    int value;

public:
    // constructor
    integerAttribute(int val) : value(val) {}

    // getter and setter
    int getValue() const { return value; }
    void setValue(int val) { value = val; }

    // overloaded operators
    bool operator==(const Attr &) override;

    bool operator!=(const Attr &) override;

    bool operator<(const Attr &) override;

    bool operator<=(const Attr &) override;

    bool operator>(const Attr &) override;

    bool operator>=(const Attr &) override;
};

class floatAttribute : public Attr
{
private:
    float value;

public:
    // constructor
    floatAttribute(float val) : value(val) {}

    // getter and setter
    float getValue() const { return value; }
    void setValue(float val) { value = val; }

    // overloaded operators
    bool operator==(const Attr &) override;

    bool operator!=(const Attr &) override;

    bool operator<(const Attr &) override;

    bool operator<=(const Attr &) override;

    bool operator>(const Attr &) override;

    bool operator>=(const Attr &) override;
};

class stringAttribute : public Attr
{
private:
    string value;

public:
    // constructor
    stringAttribute(string s) : value(s) {}
    // destructor
    ~stringAttribute() {}
    // getter and setter
    string getValue() const { return value; }
    void setValue(string s) { value = s; }

    // overloaded operators
    bool operator==(const Attr &) override;

    bool operator!=(const Attr &) override;

    bool operator<(const Attr &) override;

    bool operator<=(const Attr &) override;

    bool operator>(const Attr &) override;

    bool operator>=(const Attr &) override;
};

class Record
{
private:
    vector<Attr *> attributes;

public:
    // Constructor
    Record(vector<Attr *> attrs) : attributes(attrs) {}
    // Copy Constructor
    Record(const Record &other)
    {
        for (long unsigned int i = 0; i < other.attributes.size(); i++)
        {
            if (dynamic_cast<integerAttribute *>(other.attributes[i]) != nullptr)
            {
                this->attributes.push_back(new integerAttribute(dynamic_cast<integerAttribute *>(other.attributes[i])->getValue()));
            }
            else if (dynamic_cast<floatAttribute *>(other.attributes[i]) != nullptr)
            {
                this->attributes.push_back(new floatAttribute(dynamic_cast<floatAttribute *>(other.attributes[i])->getValue()));
            }
            else if (dynamic_cast<stringAttribute *>(other.attributes[i]) != nullptr)
            {
                this->attributes.push_back(new stringAttribute(dynamic_cast<stringAttribute *>(other.attributes[i])->getValue()));
            }
        }
    }
    // Destructor
    ~Record()
    {
        for (long unsigned int i = 0; i < attributes.size(); i++)
        {
            delete attributes[i];
        }
    };
    // Methods
    void addAttribute(Attr *attr) { attributes.push_back(attr); }

    Attr *getAttribute(int index) const { return attributes[index]; }

    int getNumAttributes() const { return attributes.size(); }

    void setAttribute(int index, Attr *attr)
    {
        delete attributes[index];
        attributes[index] = attr;
    }
    bool operator==(const Record &right) const
    {
        if (this->getNumAttributes() != right.getNumAttributes())
        {
            return false;
        }
        for (int i = 0; i < this->getNumAttributes(); i++)
        {
            if (*(this->getAttribute(i)) != *(right.getAttribute(i)))
            {
                return false;
            }
        }
        return true;
    }
};

class Relation
{                             // storing a relation
    int nattr, nrecs;         // number of attributes and records
    vector<string> attrnames; // schema
    vector<int> attrinds;     // mapping schema to indices
    list<Record *> recs;      // list of records
public:
    Relation(int nattr, vector<string> attrnames)
    {
        this->nattr = nattr;
        this->nrecs = 0;
        this->attrnames = attrnames;
        this->attrinds.resize(nattr);
        for (int i = 0; i < nattr; i++)
        {
            this->attrinds[i] = i;
        }
    }

    // Destructor
    ~Relation()
    {
        for (auto r : this->recs)
        {
            delete r;
        }
        this->recs.clear();
    }

    // Copy constructor (deep copy)
    Relation(const Relation &other)
    {
        this->nattr = other.nattr;
        this->nrecs = other.nrecs;
        this->attrnames = other.attrnames;
        this->attrinds = other.attrinds;
        for (auto r : other.recs)
        {
            Record *newRec = new Record(*r); // DOUBT
            this->recs.push_back(newRec);
        }
    }

    // Assignment operator (deep copy)
    Relation &operator=(const Relation &other)
    {
        if (this != &other)
        {
            this->nattr = other.nattr;
            this->nrecs = other.nrecs;
            this->attrnames = other.attrnames;
            this->attrinds = other.attrinds;
            for (auto r : this->recs)
            {
                delete r;
            }
            this->recs.clear();
            for (auto r : other.recs)
            {
                Record *newRec = new Record(*r);
                this->recs.push_back(newRec);
            }
        }
        return *this;
    }

    // Getters
    int getNumAttrs() const
    {
        return this->nattr;
    }

    int getNumRecs() const
    {
        return this->nrecs;
    }
    int getAttrInd(string attrname) const
    {
        for (int i = 0; i < this->nattr; i++)
        {
            if (this->attrnames[i] == attrname)
            {
                return this->attrinds[i];
            }
        }
        return -1;
    }
    vector<string> getAttrNames() const
    {
        return this->attrnames;
    }

    // Setters
    void setAttrNames(vector<string> attrnames)
    {
        this->attrnames = attrnames;
    }

    // Methods
    void addRecord(Record *rec)
    {
        this->recs.push_back(rec);
        this->nrecs++;
    }

    void removeRecord(Record *rec)
    {
        this->recs.remove(rec);
        this->nrecs--;
    }

    void clearRecords()
    {
        for (auto r : this->recs)
        {
            delete r;
        }
        this->recs.clear();
        this->nrecs = 0;
    }

    list<Record *> getRecords() const
    {
        return this->recs;
    }

    void print() const
    {

        if (this == nullptr)
        {
            cout << endl;
        }
        else
        {
            for (int i = 0; i < this->nattr; i++)
            {
                cout << this->attrnames[i] << "\t\t";
            }
            cout << endl;
            for (auto r : this->recs)
            {
                for (int i = 0; i < this->nattr; i++)
                {
                    Attr *attr = r->getAttribute(i);
                    if (dynamic_cast<integerAttribute *>(attr) != nullptr)
                    {
                        cout << dynamic_cast<integerAttribute *>(attr)->getValue() << "\t\t";
                    }
                    else if (dynamic_cast<floatAttribute *>(attr) != nullptr)
                    {
                        cout << dynamic_cast<floatAttribute *>(attr)->getValue() << "\t\t";
                    }
                    else if (dynamic_cast<stringAttribute *>(attr) != nullptr)
                    {
                        cout << dynamic_cast<stringAttribute *>(attr)->getValue() << "\t\t";
                    }
                }
                cout << endl;
            }
        }
    }
};

typedef struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
} DNFformula;

Relation *Runion(const Relation *, const Relation *);
Relation *Rdifference(const Relation *, const Relation *);
Relation *RcartesianProduct(const Relation *, const Relation *);
Relation *Rprojection(const Relation *, vector<string>);
Relation *Rselection(const Relation *, DNFformula *);
Relation *Rrename(Relation *, string, string);
Relation *NaturalJoin(const Relation *, const Relation *);
bool eval(tuple<string, char, Attr *>, const Record *, const Relation *);
bool DNFCheck(DNFformula *, const Relation *, const Record *);
