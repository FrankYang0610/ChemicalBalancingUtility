// Chemical Balancing Utility by Frank Yang
// Jul 8 2023

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

int elementsCountReactant[120];
int elementsCountProduct[120];
int coefficientList[100]; // 1~chemicalList[0].size() is for reactant; chemicalList[0].size()+1~chemicalList[0].size()+chemicalList[1].size() is for product.

bool programStart=1;

struct chemical
{
    int elements[120]={}; // numbers of elements. for example, elements[1]=2 means H2
};
vector <chemical> chemicalList[2]; // fixing. [0][]=reactant, [1][]=product

int recognizingNumbers(string reaction, int startingPos, int endingPos)
{
    int number=0;
    for (int i=startingPos; i<=endingPos; i++)
        number+=(reaction[i]-0x30)*pow(10,endingPos-i);
    return number;
}

void recognizingChemical(string reaction, int startingPos, int endingPos, bool isProduct)
{
    chemical temporary;
    vector <int> processingElementsList;
    int timesList[120]={}; // times added on each element

    bool inBracket=false;

    for (int i=startingPos; i<=endingPos; i++)
    {
        if (reaction[i]=='(')
        {
            inBracket=true;
            if (reaction[i-1]>=0x3A)
            {
                for (int j=0; j<=processingElementsList.size()-1; j++)
                {
                    if (!timesList[processingElementsList[j]]) temporary.elements[processingElementsList[j]]++;
                    else temporary.elements[processingElementsList[j]]+=timesList[processingElementsList[j]];
                }
                for (int j=0; j<=119; j++) timesList[j]=0; // Clear
                processingElementsList.clear(); // Clear
            }
        } // elements inside '()' starting scan

        else if (reaction[i]==')')
        {
            inBracket=false;
            if (reaction[i+1]>=0x3A)
                for (int j=0; j<=processingElementsList.size()-1; j++)
                    temporary.elements[processingElementsList[j]]++;
        } // elements inside '()' ending scan

        else if (reaction[i]>=0x41 && reaction[i]<=0x5a) // Capital Letters
        {
            // Remove the last saved element
            if (!inBracket && !processingElementsList.empty())
            {
                for (int j=0; j<=processingElementsList.size()-1; j++)
                    temporary.elements[processingElementsList[j]]++;
                processingElementsList.clear();
            }

            // A
            if (reaction[i]=='A' && reaction[i+1]=='c') processingElementsList.push_back(89);
            else if (reaction[i]=='A' && reaction[i+1]=='g') processingElementsList.push_back(47);
            else if (reaction[i]=='A' && reaction[i+1]=='l') processingElementsList.push_back(13);
            else if (reaction[i]=='A' && reaction[i+1]=='m') processingElementsList.push_back(95);
            else if (reaction[i]=='A' && reaction[i+1]=='r') processingElementsList.push_back(18);
            else if (reaction[i]=='A' && reaction[i+1]=='s') processingElementsList.push_back(33);
            else if (reaction[i]=='A' && reaction[i+1]=='t') processingElementsList.push_back(85);
            else if (reaction[i]=='A' && reaction[i+1]=='u') processingElementsList.push_back(79);

            // B
            else if (reaction[i]=='B' && reaction[i+1]=='a') processingElementsList.push_back(56);
            else if (reaction[i]=='B' && reaction[i+1]=='e') processingElementsList.push_back(4);
            else if (reaction[i]=='B' && reaction[i+1]=='h') processingElementsList.push_back(107);
            else if (reaction[i]=='B' && reaction[i+1]=='i') processingElementsList.push_back(83);
            else if (reaction[i]=='B' && reaction[i+1]=='k') processingElementsList.push_back(97);
            else if (reaction[i]=='B' && reaction[i+1]=='r') processingElementsList.push_back(35);
            else if (reaction[i]=='B') processingElementsList.push_back(5);

            // C
            else if (reaction[i]=='C' && reaction[i+1]=='a') processingElementsList.push_back(20);
            else if (reaction[i]=='C' && reaction[i+1]=='d') processingElementsList.push_back(48);
            else if (reaction[i]=='C' && reaction[i+1]=='e') processingElementsList.push_back(58);
            else if (reaction[i]=='C' && reaction[i+1]=='f') processingElementsList.push_back(98);
            else if (reaction[i]=='C' && reaction[i+1]=='l') processingElementsList.push_back(17);
            else if (reaction[i]=='C' && reaction[i+1]=='m') processingElementsList.push_back(96);
            else if (reaction[i]=='C' && reaction[i+1]=='n') processingElementsList.push_back(112);
            else if (reaction[i]=='C' && reaction[i+1]=='o') processingElementsList.push_back(27);
            else if (reaction[i]=='C' && reaction[i+1]=='r') processingElementsList.push_back(24);
            else if (reaction[i]=='C' && reaction[i+1]=='s') processingElementsList.push_back(55);
            else if (reaction[i]=='C' && reaction[i+1]=='u') processingElementsList.push_back(29);
            else if (reaction[i]=='C') processingElementsList.push_back(6);

            // D
            else if (reaction[i]=='D' && reaction[i+1]=='b') processingElementsList.push_back(105);
            else if (reaction[i]=='D' && reaction[i+1]=='s') processingElementsList.push_back(110);
            else if (reaction[i]=='D' && reaction[i+1]=='y') processingElementsList.push_back(66);

            // E
            else if (reaction[i]=='E' && reaction[i+1]=='r') processingElementsList.push_back(68);
            else if (reaction[i]=='E' && reaction[i+1]=='s') processingElementsList.push_back(99);
            else if (reaction[i]=='E' && reaction[i+1]=='u') processingElementsList.push_back(63);

            // F
            else if (reaction[i]=='F' && reaction[i+1]=='e') processingElementsList.push_back(26);
            else if (reaction[i]=='F' && reaction[i+1]=='l') processingElementsList.push_back(114);
            else if (reaction[i]=='F' && reaction[i+1]=='m') processingElementsList.push_back(100);
            else if (reaction[i]=='F' && reaction[i+1]=='r') processingElementsList.push_back(87);
            else if (reaction[i]=='F') processingElementsList.push_back(9);

            // G
            else if (reaction[i]=='G' && reaction[i+1]=='a') processingElementsList.push_back(31);
            else if (reaction[i]=='G' && reaction[i+1]=='d') processingElementsList.push_back(64);
            else if (reaction[i]=='G' && reaction[i+1]=='e') processingElementsList.push_back(32);

            // H
            else if (reaction[i]=='H' && reaction[i+1]=='e') processingElementsList.push_back(2);
            else if (reaction[i]=='H' && reaction[i+1]=='f') processingElementsList.push_back(72);
            else if (reaction[i]=='H' && reaction[i+1]=='g') processingElementsList.push_back(80);
            else if (reaction[i]=='H' && reaction[i+1]=='o') processingElementsList.push_back(67);
            else if (reaction[i]=='H' && reaction[i+1]=='s') processingElementsList.push_back(108);
            else if (reaction[i]=='H') processingElementsList.push_back(1);

            // I
            else if (reaction[i]=='I' && reaction[i+1]=='n') processingElementsList.push_back(49);
            else if (reaction[i]=='I' && reaction[i+1]=='r') processingElementsList.push_back(77);
            else if (reaction[i]=='I') processingElementsList.push_back(53);

            // J

            // K
            else if (reaction[i]=='K' && reaction[i+1]=='r') processingElementsList.push_back(36);
            else if (reaction[i]=='K') processingElementsList.push_back(19);

            // L
            else if (reaction[i]=='L' && reaction[i+1]=='a') processingElementsList.push_back(57);
            else if (reaction[i]=='L' && reaction[i+1]=='r') processingElementsList.push_back(103);
            else if (reaction[i]=='L' && reaction[i+1]=='u') processingElementsList.push_back(71);
            else if (reaction[i]=='L' && reaction[i+1]=='v') processingElementsList.push_back(116);

            // M
            else if (reaction[i]=='M' && reaction[i+1]=='c') processingElementsList.push_back(115);
            else if (reaction[i]=='M' && reaction[i+1]=='d') processingElementsList.push_back(101);
            else if (reaction[i]=='M' && reaction[i+1]=='g') processingElementsList.push_back(12);
            else if (reaction[i]=='M' && reaction[i+1]=='n') processingElementsList.push_back(25);
            else if (reaction[i]=='M' && reaction[i+1]=='o') processingElementsList.push_back(42);
            else if (reaction[i]=='M' && reaction[i+1]=='t') processingElementsList.push_back(109);

            // N
            else if (reaction[i]=='N' && reaction[i+1]=='a') processingElementsList.push_back(11);
            else if (reaction[i]=='N' && reaction[i+1]=='b') processingElementsList.push_back(41);
            else if (reaction[i]=='N' && reaction[i+1]=='e') processingElementsList.push_back(10);
            else if (reaction[i]=='N' && reaction[i+1]=='h') processingElementsList.push_back(113);
            else if (reaction[i]=='N' && reaction[i+1]=='i') processingElementsList.push_back(28);
            else if (reaction[i]=='N' && reaction[i+1]=='o') processingElementsList.push_back(102);
            else if (reaction[i]=='N' && reaction[i+1]=='p') processingElementsList.push_back(93);
            else if (reaction[i]=='N') processingElementsList.push_back(7);

            // O
            else if (reaction[i]=='O' && reaction[i+1]=='g') processingElementsList.push_back(118);
            else if (reaction[i]=='O' && reaction[i+1]=='s') processingElementsList.push_back(76);
            else if (reaction[i]=='O') processingElementsList.push_back(8);

            // P
            else if (reaction[i]=='P' && reaction[i+1]=='a') processingElementsList.push_back(91);
            else if (reaction[i]=='P' && reaction[i+1]=='b') processingElementsList.push_back(82);
            else if (reaction[i]=='P' && reaction[i+1]=='d') processingElementsList.push_back(46);
            else if (reaction[i]=='P' && reaction[i+1]=='m') processingElementsList.push_back(61);
            else if (reaction[i]=='P' && reaction[i+1]=='o') processingElementsList.push_back(84);
            else if (reaction[i]=='P' && reaction[i+1]=='t') processingElementsList.push_back(78);
            else if (reaction[i]=='P') processingElementsList.push_back(15);

            // Q

            // R
            else if (reaction[i]=='R' && reaction[i+1]=='a') processingElementsList.push_back(88);
            else if (reaction[i]=='R' && reaction[i+1]=='e') processingElementsList.push_back(75);
            else if (reaction[i]=='R' && reaction[i+1]=='g') processingElementsList.push_back(111);
            else if (reaction[i]=='R' && reaction[i+1]=='h') processingElementsList.push_back(45);
            else if (reaction[i]=='R' && reaction[i+1]=='n') processingElementsList.push_back(86);
            else if (reaction[i]=='R' && reaction[i+1]=='u') processingElementsList.push_back(44);

            // S
            else if (reaction[i]=='S' && reaction[i+1]=='b') processingElementsList.push_back(51);
            else if (reaction[i]=='S' && reaction[i+1]=='c') processingElementsList.push_back(21);
            else if (reaction[i]=='S' && reaction[i+1]=='e') processingElementsList.push_back(34);
            else if (reaction[i]=='S' && reaction[i+1]=='g') processingElementsList.push_back(106);
            else if (reaction[i]=='S' && reaction[i+1]=='i') processingElementsList.push_back(14);
            else if (reaction[i]=='S' && reaction[i+1]=='m') processingElementsList.push_back(62);
            else if (reaction[i]=='S' && reaction[i+1]=='n') processingElementsList.push_back(50);
            else if (reaction[i]=='S' && reaction[i+1]=='r') processingElementsList.push_back(38);
            else if (reaction[i]=='S') processingElementsList.push_back(16);

            // T
            else if (reaction[i]=='T' && reaction[i+1]=='a') processingElementsList.push_back(73);
            else if (reaction[i]=='T' && reaction[i+1]=='c') processingElementsList.push_back(43);
            else if (reaction[i]=='T' && reaction[i+1]=='e') processingElementsList.push_back(52);
            else if (reaction[i]=='T' && reaction[i+1]=='h') processingElementsList.push_back(90);
            else if (reaction[i]=='T' && reaction[i+1]=='i') processingElementsList.push_back(22);
            else if (reaction[i]=='T' && reaction[i+1]=='l') processingElementsList.push_back(81);
            else if (reaction[i]=='T' && reaction[i+1]=='m') processingElementsList.push_back(69);
            else if (reaction[i]=='T' && reaction[i+1]=='s') processingElementsList.push_back(117);

            // U
            else if (reaction[i]=='U') processingElementsList.push_back(92);

            // V
            else if (reaction[i]=='V') processingElementsList.push_back(23);

            // W
            else if (reaction[i]=='W') processingElementsList.push_back(74);

            // X
            else if (reaction[i]=='X' && reaction[i+1]=='e') processingElementsList.push_back(54);

            // Y
            else if (reaction[i]=='Y' && reaction[i+1]=='b') processingElementsList.push_back(70);
            else if (reaction[i]=='Y') processingElementsList.push_back(39);

            // Z
            else if (reaction[i]=='Z' && reaction[i+1]=='n') processingElementsList.push_back(30);
            else if (reaction[i]=='Z' && reaction[i+1]=='r') processingElementsList.push_back(40);
        }

        if (reaction[i]>=0x30 && reaction[i]<=0x39) // Number recognized
        {
            int digits=0;
            for (int j=i;j<=endingPos && reaction[j]>=0x30 && reaction[j]<=0x39; j++) digits++;
            int coefficient=recognizingNumbers(reaction,i,i+digits-1);

            if (!inBracket)
            {
                for (int j=0; j<=processingElementsList.size()-1; j++)
                {
                    if (!timesList[processingElementsList[j]]) temporary.elements[processingElementsList[j]]+=coefficient;
                    else temporary.elements[processingElementsList[j]]+=coefficient*timesList[processingElementsList[j]];
                }
                for (int j=0; j<=119; j++) timesList[j]=0; // Clear
                processingElementsList.clear(); // Clear
            }
            else // inBracket
                timesList[processingElementsList[processingElementsList.size()-1]]+=coefficient;

            i+=digits-1;
        }
    }

    if (!processingElementsList.empty()) // Only one element not processed, its coefficient is 1
        temporary.elements[processingElementsList[0]]++;

    chemicalList[isProduct].push_back(temporary);
}

bool completed=false;
void balance(int depth) // numberOfChemicals=maxdepth
{
    if (depth==chemicalList[0].size()+chemicalList[1].size()+1) // Check, all coefficients loaded
    {
        for (int i=0; i<=chemicalList[0].size()-1; i++) // reactants
            for (int j=0; j<=119; j++)
                elementsCountReactant[j]+=chemicalList[0][i].elements[j]*coefficientList[i+1];

        for (int i=0; i<=chemicalList[1].size()-1; i++) // products
            for (int j=0; j<=119; j++)
                elementsCountProduct[j]+=chemicalList[1][i].elements[j]*coefficientList[chemicalList[0].size()+i+1];

        int cursor=0;
        for (cursor=0; cursor<=119; cursor++)
            if (elementsCountReactant[cursor]!=elementsCountProduct[cursor]) cursor=10000;

        if (cursor==120) completed=true;

        // Clear
        for (int i=1; i<=119; i++)
        {
            elementsCountReactant[i]=0;
            elementsCountProduct[i]=0;
        }
    }
    else
        for (int i=1; i<=20 && !completed; i++)
        {
            coefficientList[depth]=i;
            balance(depth+1);
        }
}

int main()
{
    cout<<"Welcome to Chemical Balancing Utility by Frank Yang."<<endl;
    cout<<"BF version 1.0.0"<<endl;

    cout<<"Type a chemical reaction, using A+B+...->C+D+... form. Using quit() for quitting."<<endl;

    while(programStart)
    {
        string reaction;
        cin>>reaction;
        if (reaction=="quit()")
            programStart = 0;
        else // processing
        {
            int cur=0;
            bool isProduct=0;
            for (int i=0; i<=reaction.size()-1; i++) // starting recognizing and push into vector
            {
                if (reaction[i]=='+' || reaction[i]=='-')
                {
                    recognizingChemical(reaction,cur,i-1,isProduct);
                    cur=i+1;
                }
                else if (i==reaction.size()-1)
                    recognizingChemical(reaction,cur,i,isProduct);
                else if (reaction[i]=='>')
                {
                    cur=i+1;
                    isProduct=1;
                }
            }

            // Start balancing
            balance(1); // coefficientList array returned.

            // Output
            cur=0;
            int coefficientListCursor=1;

            bool isRightCompleted=true;
            if (coefficientList[1]==20 && coefficientList[2]==20)
            {
                isRightCompleted=false;
                cout<<"ERROR! THE REACTION CAN'T BE BALANCED!";
            }

            for (int i=0; isRightCompleted && i<=reaction.size()-1; i++) // starting recognizing and push into vector
            {
                if (reaction[i]=='+' || reaction[i]=='-' || i==reaction.size()-1)
                {
                    if(coefficientList[coefficientListCursor]>1) cout<<coefficientList[coefficientListCursor];
                    coefficientListCursor++;
                    for (int j=cur; j<=i; j++) cout<<reaction[j];
                    cur=i+1;
                }
                else if (reaction[i]=='>')
                {
                    cout<<reaction[i];
                    cur=i+1;
                }
            }
        }

        // reset
        cout<<endl;
        chemicalList[0].clear();
        chemicalList[1].clear();
        for (int i=1; i<=99; i++) coefficientList[i]=0;
        completed=false;
    }

    return 0;
}
