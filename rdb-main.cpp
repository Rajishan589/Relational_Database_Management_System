#include "rdb.h"

class Relational_Algebra
{
private:
    int ntables;
    vector<Relation *> tables;

public:
    Relational_Algebra() { ntables = 0; }
    ~Relational_Algebra() {}
    void view()
    {
        cout << "Table no.\tNo. of records\tNo. of attributes" << endl;
        for (int i = 0; i < ntables; i++)
        {
            cout << "\t" << i + 1 << "\t\t\t" << tables[i]->getNumRecs() << "\t\t" << tables[i]->getNumAttrs() << endl;
        }
    }
    void home()
    {
        cout << endl
             << endl;
        cout << "****  Home Menu  ****" << endl
             << endl;

        cout << "1. Add, Remove, Create Tables" << endl;
        cout << "2. Table Operation " << endl;
        cout << "3. Quit" << endl
             << endl;
        cout << "Select an option: ";
        int opt;
        cin >> opt;
        switch (opt)
        {
        case 1:
            Operation_menu();
            break;

        case 2:
            operate();
            break;

        case 3:
            exit(0);
            break;

        default:
            home();
            break;
        }
    }

    void Operation_menu()
    {
        cout << endl
             << endl;
        cout << "$$$$$$$$  MENU  $$$$$$$$" << endl
             << endl;
        cout << "1. Display tables (Relation) summary: " << endl;
        cout << "2. New table " << endl;
        cout << "3. Remove table" << endl;
        cout << "4. Add record " << endl;
        cout << "5. Print table " << endl;
        cout << "6. Home Menu" << endl;
        cout << endl;
        cout << "Select an option: ";
        int opt;
        int no;
        vector<string> attrnames;
        vector<Attr *> attr;
        int nattr;
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            view();
            home();
            break;
        }

        case 2:

        {
            cout << "Enter the number of attributes" << endl;
            cin >> nattr;

            for (int i = 0; i < nattr; i++)
            {
                string temp;
                cout << "Enter the name of attribute no. " << i + 1 << endl;
                cin >> temp;
                attrnames.push_back(temp);
            }
            Relation temp(nattr, attrnames);
            tables.push_back(&temp);
            cout << "Instantiated an empty table.\n Table no.: " << ntables + 1 << endl;
            ++ntables;
            home();
            break;
        }

        case 3:
        {
            cout << "Enter the table no. to be deleted" << endl;
            cin >> no;
            tables.erase(tables.begin() + no - 1);
            --ntables;
            home();
            break;
        }

        case 4:
        {
            cout << "Enter the table no. to be operated" << endl;
            // int no;
            cin >> no;
            cout << "Enter the record to be added" << endl;
            vector<Attr *> temp_attr;
            for (int i = 0; i < tables[no - 1]->getNumAttrs(); i++)
            {
                cout << "Attribute Name: " << tables[no - 1]->getAttrNames()[i] << "\n";
                cout << "Enter the type of attribute(int/float/string): ";
                string type;
                cin >> type;
                cout << "Enter the value of attribute: ";
                if (type == "int")
                {
                    int tempInt;
                    cin >> tempInt;
                    temp_attr.push_back(new integerAttribute(tempInt));
                }
                else if (type == "float")
                {
                    float tempFloat;
                    cin >> tempFloat;
                    temp_attr.push_back(new floatAttribute(tempFloat));
                }
                else if (type == "string")
                {
                    string tempStr;
                    cin >> tempStr;
                    temp_attr.push_back(new stringAttribute(tempStr));
                }
                else
                {
                    cout << "Invalid type. Try again.\n";
                    --i;
                }
                
            }
            Record *rec = new Record(temp_attr);
            // Put record input here
            tables[no - 1]->addRecord(rec);
            home();
            break;
        }

        case 5:
        {
            cout << "Enter the table no. to be printed" << endl;
            // int no;
            cin >> no;
            if (no > ntables)
            {
                cout << "Does not exist!" << endl;
                home();
                break;
            }
            else
            {
                tables[no - 1]->print();
                home();
                break;
            }
        }

        case 6:
            home();

        default:
            home();
        }
    }

    void operate()
    {
        cout << "$$$$   OPERATIONS    $$$$" << endl;
        cout << "1. Union" << endl;
        cout << "2. Difference" << endl;
        cout << "3. Cartesian Product" << endl;
        cout << "4. Projection" << endl;
        cout << "5. Selection" << endl;
        cout << "6. Rename" << endl;
        cout << "7. Natural Join" << endl;
        cout << "8. Back" << endl;

        int opt;
        int a, b;
        cin >> opt;
        vector<string> pro;
        switch (opt)
        {
        case 1:
        {
            cout << "Enter the table nos. of whose union is to be generated" << endl;
            view();
            cin >> a >> b;
            Relation *R = Runion(tables[a - 1], tables[b - 1]);
            R->print();
            tables.push_back(R);
            ntables++;
            home();
            break;
        }
        case 2:
        {
            cout << "Enter the table nos. of whose difference is to be generated" << endl;
            view();
            cin >> a >> b;
            Relation *R1 = Rdifference(tables[a - 1], tables[b - 1]);
            R1->print();
            tables.push_back(R1);
            ntables++;
            home();
            break;
        }

        case 3:
        {
            cout << "Enter the table nos. of whose cartesian product is to be generated" << endl;
            view();
            cin >> a >> b;
            Relation *R2 = RcartesianProduct(tables[a - 1], tables[b - 1]);
            R2->print();
            tables.push_back(R2);
            ntables++;
            home();
            break;
        }

        case 4:
        {
            cout << "Enter the input table no. whose projection is to be taken: " << endl;
            view();
            int a;
            cin >> a;
            cout << "Enter the attributes to be projected: ";

            for (int i = 0; i < tables[a - 1]->getNumAttrs(); i++)
            {
                string temp;
                cin >> temp;
                pro.push_back(temp);
            }
            Relation *R3 = Rprojection(tables[a - 1], pro);
            R3->print();
            tables.push_back(R3);
            ntables++;
            home();
            break;
        }

        case 5:
        {
            cout << "Enter the input table no. whose selection is to be taken: " << endl;
            view();
            int a1;
            cin >> a1;
            cout << "Enter the number of Disjunctive conditions in the DNF formula: ";
            int n2;
            DNFformula f;
            cin >> n2;
            // list<list<tuple<string,char,Attr*>>> disj;
            for (int j = 0; j < n2; j++)
            {
                cout << "Enter the number of conjunctive clauses (AND) in the " << j + 1 << "th disjunctive clause (OR):";
                int n1;
                cin >> n1;
                list<tuple<string, char, Attr *>> conj;
                for (int i = 0; i < n1; i++)
                {
                    cout << "Enter the " << i + 1 << "th conjunctive clause: " << endl;
                    tuple<string, char, Attr *> temp;
                    cout << "Enter the attribute name: ";
                    string s;
                    cin >> s;
                    get<0>(temp) = s;
                    cout << "Enter the operator: ";
                    char c;
                    cin >> c;
                    get<1>(temp) = c;
                    cout << "Enter the object type(string/float/int): ";
                    string s1;
                    cin >> s1;
                    if (s1 == "string")
                    {
                        cout << "Enter the string value: ";
                        string s2;
                        cin >> s2;
                        get<2>(temp) = new stringAttribute(s2);
                    }
                    else if (s1 == "float")
                    {
                        cout << "Enter the float value: ";
                        float f;
                        cin >> f;
                        get<2>(temp) = new floatAttribute(f);
                    }
                    else if (s1 == "int")
                    {
                        cout << "Enter the int value: ";
                        int i_val;
                        cin >> i_val;
                        get<2>(temp) = new integerAttribute(i_val);
                    }
                    conj.push_back(temp);
                }
                // disj.push_back(conj);
                f.ops.push_back(conj);
            }
            // f.ops=disj;
            for (auto i : f.ops)
            {
                for (auto j : i)
                {

                    cout << get<0>(j) << " " << get<1>(j) << " " << dynamic_cast<integerAttribute *>(get<2>(j))->getValue() << endl;
                }
            }
            Relation *R4 = Rselection(tables[a1 - 1], &f);
            R4->print();
            tables.push_back(R4);
            ntables++;
            home();
            break;
        }

        case 6:
        {
            cout << "Enter the input table no. whose string is to be renamed: " << endl;
            view();
            int a;
            cin >> a;
            cout << "Enter the existing attribute name: ";
            string s1, s2;
            cin >> s1;
            cout << "Enter the new attribute name: ";
            cin >> s2;
            tables[a - 1] = Rrename(tables[a - 1], s1, s2);
            tables[a - 1]->print();
            home();
            break;
        }
        case 7:
        {
            cout << "Enter the table nos. of whose natural join is to be generated" << endl;
            cin >> a >> b;
            Relation *R5 = NaturalJoin(tables[a - 1], tables[b - 1]);
            R5->print();
            tables.push_back(R5);
            ntables++;
            home();
            break;
        }

        case 8:
            home();
        default:
            home();
        }
    }
};

int main()
{
    cout << endl
         << endl
         << "Welcome to the Relational Algebra Interpreter" << endl;
    cout << "______________________________________________" << endl;
    Relational_Algebra a;
    a.home();
    return 0;
}
