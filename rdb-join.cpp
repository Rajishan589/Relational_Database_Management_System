#include "rdb.h"

Relation *NaturalJoin(const Relation *R1, const Relation *R2)
{
    vector<string> attrnames;
    vector<tuple<int, int>> common_attr; // common attr indices in R1 and R2
    int flag = 0;
    for (auto s : R1->getAttrNames())
    {
        for (auto s1 : R2->getAttrNames())
        {
            if (s == s1)
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0)
    {
        return nullptr;
    }
    else
    {
        for (auto s : R1->getAttrNames())
        {
            attrnames.push_back(s);
        }
        int i, j;
        i = j = 0;
        for (auto s : R2->getAttrNames())
        {
            flag = 1;
            i = 0;
            for (auto s1 : R1->getAttrNames())
            {
                if (s == s1)
                {
                    flag = 0;

                    tuple<int, int> temp;
                    temp = {i, j};
                    common_attr.push_back(temp);
                }

                i++;
            }
            if (flag == 1)
            {
                attrnames.push_back(s);
            }
            j++;
        }
        Relation *R = new Relation(attrnames.size(), attrnames);
        for (auto r1 : R1->getRecords())
        {
            for (auto r2 : R2->getRecords())
            {
                flag = 1;
                for (auto t : common_attr)
                {
                    if (*(r1->getAttribute(get<0>(t))) != *(r2->getAttribute(get<1>(t))))
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    vector<Attr *> attrs;
                    for (int i = 0; i < R1->getNumAttrs(); i++)
                    {
                        attrs.push_back(r1->getAttribute(i));
                    }
                    for (int i = 0; i < R2->getNumAttrs(); i++)
                    {
                        for (auto j : common_attr)
                        {
                            if (i != get<1>(j))
                                attrs.push_back(r2->getAttribute(i));
                        }
                    }
                    R->addRecord(new Record(attrs));
                }
            }
        }
        return R;
    }
}
