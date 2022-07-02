// algo_proj_q3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int minimum(int val1, int val2) {
    if (val1 > val2) {
        return val2;
    }
    else {
        return val1;
    }
}
int prefix(char p[], int psize, int k, char q) {         //
    //cout << "IN"<< endl;  
    int nextk = 0;
    int i = 0;

    if (k < psize&& q == p[k])      //if incoming and next are same then state incremented
    {
        //cout << "here: " << k << endl;
        return k + 1;

    }
    //finding the suffix size of x that is a prefix of pattern
    for (nextk = k; nextk > 0; nextk--)     //starts from alrgest value
    {
        if (p[nextk - 1] == q)  //decrementing nextk
        {
            for (i = 0; i < nextk - 1; i++)             //comparing characters
            {
                if (p[i] != p[k - nextk + 1 + i])
                    break;
            }
            if (i == nextk - 1)
            {
                // cout << "nextk: " << nextk << endl;
                return nextk;
            }

        }
    }

    return 0;
}
int patternsearch(char p[], int psize, char text[], int transition[][4]) {
    int M = psize;
    int N = strlen(text);

    // Process txt over FA.

    int i, state = 0; int val = 0;

    for (i = 0; i < N; i++)

    {
        if (text[i] == 'A')
        {
            val = 0;
        }
        else if (text[i] == 'B') {
            val = 1;
        }
        else if (text[i] == 'C') {
            val = 2;
        }
        else if (text[i] == 'D') {
            val = 3;
        }       //will change according to our alphabet set
        state = transition[state][val];     //getting the state from transition table

        if (state == M) {
            return i - M + 1;           //if state and length of matrix matched returns the starting shift / index which is 0 in our case
        }

    }
    return -1;
}
int main()
{
    const int m = 2;
    const int n1 = 4;       //rows
    const int n2 = 4;       //cols

    char pattern[m][m] = { {'B','A'},{'C','A'} };
    char text[n1][n2] = { {'B', 'A' , 'B' , 'B' },
                          {'C', 'A' , 'A' , 'A' },
                          {'A', 'B' , 'A' , 'D' },
                          {'B', 'C' , 'A' , 'C' }
                           };

    char alphabet[4] = { 'A','B','C','D' };     //WILL CHANGE ACCORDING TO OUR TEXT

    char patternarr[m * m + 1];
    int o = 0;

    //-----time complexity m^2-------------
    for (int i = 0; i < m; i++) {       //combining matrix into single array
        for (int j = 0; j < m; j++) {
            patternarr[o] = pattern[j][i];
            o++;
        }
    }
    patternarr[o] = '\0';

    int transition[(m * m) + 1][4];         //transition table 

    //creating transition table
    //--------------time complexity  m^2(k) ------
    for (int i = 0; i <= m * m; ++i)
    {
        for (int k = 0; k < 4; ++k) {            //will change as alphabet changes
            transition[i][k] = (prefix(patternarr, m * m, i, alphabet[k]));
        }
    }

    //creating submatrix into an array
    char temp_arr[m * m + 1];

    o = 0;
    int count = 0;      //to add cols
    int count2 = 0;     //to add the rows
    //arrays to store pattern index at
    int rowarr[n1 + 1];
    int colarr[n2 + 1];
    //------Time complexity n1*n2(m^2)
    int l = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < m * m; k++) {
                temp_arr[o] = text[i + count2][j + count];
                o++;
                count2++;
                if ((k + 1) % m == 0 && k != 0) {           //count2 ko 0 kr rhy takey ab wo top row pei jaye and count + takey next column pei jaye
                    count2 = 0;
                    count++;
                }

            }
            temp_arr[o] = '\0';
            int index = patternsearch(patternarr, m * m, temp_arr, transition);     //searching time complexity m*m
            if (index != -1) {
                rowarr[l] = i;
                colarr[l] = j;
                l++;
                cout << "Pattern at index: " << i * j << " at row:" << i << " col:" << j << endl;
            }

            o = 0;
            count = 0;
            count2 = 0;

            if (j == n2 - m) {          //breaks at the last col
                break;
            }


        }

        if (i == n1 - m) {      //break at the last row
            break;
        }
    }
    rowarr[l] = -1;
    colarr[l] = -1;

    cout << endl;

    for (int i = 0; i < n1; i++) {//n^2
        for (int j = 0; j < n2; j++) {
            cout << text[i][j] << " ";
        }
        cout << endl;
    }

    //checking for diagnols
    //----------time complexity---
    int columns = m;
    int num = 0;
    int flag = 0;
    count = 0;
    count2 = 0;
    for (int r = 0; r < l; r++) {//(n^2)(m)
        if (colarr[r] != -1) {
            num = colarr[r];

        }
        for (int c = 0; c < l; c++) {
            if (colarr[c] > num && colarr[c] <= (num + m * m)) {
                if (rowarr[c] == (rowarr[r] + columns)) {
                    if (flag == 0) {
                        for (int k = 0; k < m * m; k++) {
                            text[rowarr[r] + count2][colarr[r] + count] = 'X';
                            count2++;
                            if ((k + 1) % m == 0 && k != 0) {           //count2 ko 0 kr rhy takey ab wo top row pei jaye and count + takey next column pei jaye
                                count2 = 0;
                                count++;
                            }

                        }
                        count = 0;
                        count2 = 0;

                        for (int k = 0; k < m * m; k++) {
                            text[rowarr[c] + count2][colarr[c] + count] = 'X';
                            count2++;
                            if ((k + 1) % m == 0 && k != 0) {           //count2 ko 0 kr rhy takey ab wo top row pei jaye and count + takey next column pei jaye
                                count2 = 0;
                                count++;
                            }

                        }
                        count = 0;
                        count2 = 0;
                    }
                    else {
                        for (int k = 0; k < m * m; k++) {
                            text[rowarr[c] + count2][colarr[c] + count] = 'X';
                            count2++;
                            if ((k + 1) % m == 0 && k != 0) {           //count2 ko 0 kr rhy takey ab wo top row pei jaye and count + takey next column pei jaye
                                count2 = 0;
                                count++;
                            }

                        }
                        count = 0;
                        count2 = 0;
                    }
                    flag++;

                    //cout << "first diagonal at row: " << rowarr[c] << " col: " << colarr[c] << endl;
                    columns = columns + m;
                    num = colarr[c];
                    rowarr[c] = -1;
                    colarr[c] = -1;
                }
            }
        }
        flag = 0;
        rowarr[r] = -1;
        colarr[r] = -1;
        columns = m;

    }

    cout << endl;


    for (int i = 0; i < n1; i++) {//n^2
        for (int j = 0; j < n2; j++) {
            cout << text[i][j] << " ";
        }
        cout << endl;
    }

    return 0;

}
//int pmod = 0;
//int tmod = 0;
//int d = 10; int q = 17;
//for (int i = 0; i < m; i++)// m^2
//{
//    for (int j = 0; j < m; j++)
//    {
//        pmod = (d * pmod + pattern[j][i]) ;
//        tmod = (d * tmod + text[j][i]) ;
//    }
//}
//cout << pmod << endl;
//cout << tmod << endl;
//int h = pow(d, m ^ (2) + m);
////cout << h << endl;
//for (int i = 0; i < (n1 - (m - 1)); i++)// (n-m+1)^2
//{
//    for (int j = 0; j < (n2 - (m - 1)); j++)
//    {
//        cout << pmod << "  " << tmod << endl;
//        if (tmod == pmod)
//        {
//            cout << i + j + 2 << endl;
//        }
//        else
//        {
//            tmod = tmod % h;
//            for (int k = 0; k < m; k++)
//            {
//                tmod = ;
//                
//            }
//        }
//    }
//    cout << endl;
//}
////preprocessing
//for (int i = 0; i < r2 ; i++) {
//    for (int j = 0; j < c2; j++) {
//        tmod = (d * tmod + (matrix[j][i])) % q;
//        pmod = (d * pmod + (pattern[j][i])) % q;
//    }
//}
//cout << "pmod: " << pmod << " and tmod:" << tmod << endl;
//int a = 0;
//for (int x = 0; x < r1 * c2; x++) {
//    if (x == 3 || x == 7 || x == 11 || x == 15) {   //find a generic way to skip last column
//        //do nothing
//    }
//    else {
//        if (tmod == pmod) { //??????????!!!
//            bool flag = true;
//            for (int m = 0; m < r2; m++) {
//                int row1 = m / r2;
//                int col1 = m % r2;
//                int col2 = m % r2;
//                col2 = col2 + a;
//                if (matrix[row1][col2] == pattern[row1][col1] && flag==true) {
//                    flag = true;
//                    cout << "Shift occured at row: " << row1 << " and col: "<<col2 << endl;
//                }
//                else {
//                    break;
//                }
//            }
//            cout << "pmod: " << pmod << " and tmod:" << tmod << endl;
//        }
//        if (x < (r2 * c2) - (r1 * c1)) {
//            if ((a + 1) == r2) {
//                a = 0;
//            }
//            else {
//                a++;
//            }
//            for (int k = 0; k < r2 * c2; k++) {
//                int row = k / r2;
//                int col = k % r2;
//                col = col + a;
//                tmod = (d * tmod + matrix[row][col]) % q;
//            }
//        }
//    }
//}
//for (int i = 0; i < 2 * 2; i++) {
//    int r = i / 2;
//    int c = i % 2;
//    cout << patern[r][c] << " ";
//    if (c == 1) {
//        cout << endl;
//    }
//}*/

//for (int c = 0; c < n2 ; c++)            //n1*n2  n1 is rows
 //{
 //    for (int r = 0; r < n1 ; r++)         //n2 cols
 //    {
 //        k++;
 //        if (o == m*m)
 //        {
 //            
 //            temp_arr[o] = '\0';         //done for the starting matrix, generalise it
 //            cout << temp_arr << endl;                     
 //            patternsearch(patternarr, m * m, temp_arr, transition);     //searching
 //            
 //            o = 0;
 //            c--;
 //            cout << "--------" << endl;
 //        }
 //        temp_arr[o]= text[r][c];            //reading col wise hence j/i reversed
 //        //cout << text[j][i] << endl;
 //        
 //        if (r == m) 
 //        {
 //                
 //            break;
 //        }
 //        
 //        //cout << "r:" << c << " c:" << r << endl;
 //        o++;
 //        
 //        
 //    }
 //    cout << "r: " << c << endl;
 //}


