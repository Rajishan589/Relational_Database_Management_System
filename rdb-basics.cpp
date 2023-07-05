#include "rdb.h"

Relation *Runion(const Relation *R1, const Relation *R2)
{
    if (R1->getNumAttrs() != R2->getNumAttrs())
    {
        cout << "Not compatible!" << endl;
        return nullptr;
    }
    if (R1->getAttrNames() != R2->getAttrNames())
    {
        cout << "Attribute names are not same." << endl;
        cout << "Can't take union!";
        return nullptr;
    }
    Relation *R = new Relation(R1->getNumAttrs(), R1->getAttrNames());
    for (auto r : R1->getRecords())
    {
        R->addRecord(new Record(*r));
    }
    int flag;
    for (auto r : R2->getRecords())
    {
        flag = 0;
        for (auto r1 : R->getRecords())
        {
            if (*r1 == *r)
            {
                flag = 1;
                break;
            }
            if (flag == 0)
            {
                R->addRecord(new Record(*r));
            }
        }
    }
    return R;
}

Relation *Rdifference(const Relation *R1, const Relation *R2)
{
    if (R1->getNumAttrs() != R2->getNumAttrs())
    {
        return nullptr;
    }
    Relation *R = new Relation(R1->getNumAttrs(), R1->getAttrNames());
    int flag;
    for (auto r : R1->getRecords())
    {
        flag = 0;
        for (auto r1 : R2->getRecords())
        {
            if (*r1 == *r)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            R->addRecord(new Record(*r));
        }
    }

    return R;
}

Relation *RcartesianProduct(const Relation *R1, const Relation *R2)
{
    vector<string> attrname;

    for (auto s : R1->getAttrNames())
    {
        attrname.push_back(s);
    }
    for (auto s : R2->getAttrNames())
    {
        attrname.push_back(s);
    }
    Relation *R = new Relation(R1->getNumAttrs() + R2->getNumAttrs(), attrname);
    for (auto r1 : R1->getRecords())
    {
        for (auto r2 : R2->getRecords())
        {
            vector<Attr *> attrs;
            for (int i = 0; i < R1->getNumAttrs(); i++)
            {
                attrs.push_back(r1->getAttribute(i));
            }
            for (int i = 0; i < R2->getNumAttrs(); i++)
            {
                attrs.push_back(r2->getAttribute(i));
            }
            R->addRecord(new Record(attrs));
        }
    }
    return R;
}

Relation *Rprojection(const Relation *R, vector<string> attrnames)
{
    vector<int> attrinds;
    for (auto s : attrnames)
    {
        // attrinds.push_back(R->getAttrInd(s));
        for (int i = 0; i < R->getNumAttrs(); i++)
        {
            if (R->getAttrNames()[i] == s)
            {
                attrinds.push_back(i);
                break;
            }
        }
    }
    Relation *R_ = new Relation(attrinds.size(), attrnames);
    for (auto r : R->getRecords())
    {
        vector<Attr *> attrs;
        for (auto i : attrinds)
        {
            attrs.push_back(r->getAttribute(i));
        }
        R_->addRecord(new Record(attrs));
    }
    return R_;
}

bool eval(tuple<string, char, Attr *> formula, const Record *r, const Relation *R)
{

    for (auto str : R->getAttrNames())
    {

        if (get<0>(formula) == str)
        {
            if (get<1>(formula) == '=')
            {
                if (*(r->getAttribute(R->getAttrInd(str))) == *(get<2>(formula)))
                {
                    return true;
                }
            }
            else if (get<1>(formula) == '<')
            {
                if (*r->getAttribute(R->getAttrInd(str)) < *get<2>(formula))
                {
                    return true;
                }
            }
            else if (get<1>(formula) == '>')
            {
                if (*r->getAttribute(R->getAttrInd(str)) > *get<2>(formula))
                {
                    return true;
                }
            }
            // 1 is used for >=
            else if (get<1>(formula) == '1')
            {
                if (*r->getAttribute(R->getAttrInd(str)) >= *get<2>(formula))
                {
                    return true;
                }
            }
            // 2 is used for <=
            else if (get<1>(formula) == '0')
            {
                if (*r->getAttribute(R->getAttrInd(str)) <= *get<2>(formula))
                {
                    return true;
                }
            }
            // ! is used for !=
            else if (get<1>(formula) == '!')
            {
                if (*r->getAttribute(R->getAttrInd(str)) != *get<2>(formula))
                {
                    return true;
                }
            }
            else
                return false;
        }
    }
    return false;
}

bool DNFCheck(DNFformula *f, const Relation *R, const Record *rec)
{
    bool ans_f = false;

    for (auto r : f->ops)
    {
        bool ans = true;
        for (auto s : r)
        {
            if (eval(s, rec, R) == false)
            {
                ans = false;
                break;
            }
        }
        if (ans == true)
        {
            ans_f = true;
            break;
        }
    }
    return ans_f;
}

Relation *Rselection(const Relation *R1, DNFformula *f)
{
    Relation *R = new Relation(R1->getNumAttrs(), R1->getAttrNames());
    for (auto r : R1->getRecords())
    {
        if (DNFCheck(f, R1, r))
        {
            R->addRecord(new Record(*r));
        }
    }
    return R;
}
Relation *Rrename(Relation *R, string s1, string s2)
{ // replace attr s1 by s2
    vector<string> attrnames;
    for (auto s : R->getAttrNames())
    {
        if (s == s1)
        {
            attrnames.push_back(s2);
        }
        else
        {
            attrnames.push_back(s);
        }
    }
    R->setAttrNames(attrnames);
    return R;
}