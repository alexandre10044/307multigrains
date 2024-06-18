/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

float n1;
float n2;
float n3;
float n4;
float f1;
float f2;
float f3;
float f4;
float f5;

typedef std::vector<float>    Line;
typedef std::vector<Line>   Matrix;
typedef std::pair<int, int> Point;


Point getPivotIndex(Matrix M)
{
    size_t  max_y = M.size();
    if (max_y <= 0)
        return Point(-1, -1);
    size_t  max_x = M[0].size();
    if (max_x <= 5) // Taille de matrice fixe ?
        return Point(-1, -1);
    Line    line = M[max_y - 1];
    // Gets the last 5 elements of the last line
    Line    copyL;
    for (int i = 0; i < 5; i++) {
        copyL.push_back(line[i]);
    }
    float minV = 99999999999999;

    // Gets the smallest element
    for(float i : copyL) {
        minV = std::min(i, minV);
    }
    if (minV >= 0)
        return Point(-1, -1);
    int     xPivot = -1, yPivot = -1;

    xPivot = std::distance(copyL.begin(), std::find(copyL.begin(), copyL.end(), minV));
    minV = 99999999999999;
    for (int i = 0; i < max_y - 1; i++)
    {
        if (M[i][max_x - 1])
        {
            if (M[i][xPivot] > 0 &&
                (minV > M[i][max_x - 1] / M[i][xPivot] &&
                M[i][max_x - 1] / M[i][xPivot] > 0))
            {

                yPivot = i;
                minV = M[i][max_x - 1] / M[i][xPivot];
            }
        }
        else if (minV > M[i][xPivot] && M[i][xPivot] > 0)
        {
                yPivot = i;
                minV = M[i][max_x - 1] / M[i][xPivot];
        }
    }
    return (Point(yPivot, xPivot));
}

bool is_number(const std::string& s)
{
    for (int i = 0; i < s.size(); i++)
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (false);
    return (true);
}

Matrix createMatrix(Line N, Line P)
{
    Line minusP;
    for (int value : P)
        minusP.push_back(-value);
    for (int i = 0; i < 5; i++)
        minusP.push_back(0);
    Matrix M = {
        Line { 1, 0, 1, 0, 2 },
        Line { 1, 2, 0, 1, 0 },
        Line { 2, 1, 0, 1, 0 },
        Line { 0, 0, 3, 1, 2 },
        minusP
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == i)
                M[i].push_back(1);
            else
                M[i].push_back(0);
        }
        M[i].push_back(N[i]);
    }
    return (M);
}

Matrix applyPivot(Matrix M, int y_p, int x_p)
{
    float p_value = M[y_p][x_p];
    for (int i = 0; i < M[y_p].size(); i++) {
        M[y_p][i] = M[y_p][i] / p_value;
    }
    int maxy = M.size();
    int maxx = M[0].size();
    for (int i = 0; i < maxy; i++) {
        if (i == y_p)
            continue;
        float km = M[i][x_p];
        for (int j = 0; j < maxx; j++)
            M[i][j] -= km * M[y_p][j];
    }
    return (M);
}

std::pair<Line, Matrix> simplexe(Matrix M)
{
    Line products;
    for (int i = 0; i < 4; i++)
        products.push_back(-1);
    int i = 0;
    while (true)
    {
        i++;
        if (i == 6)
            break;
        Point p = getPivotIndex(M);
        int x_p = p.second;
        int y_p = p.first;
        if (y_p < 0 || x_p < 0)
            break;
        M = applyPivot(M, y_p, x_p);
        products[y_p] = x_p;
    }
    return std::pair<Line, Matrix>(products, M);
}

int main(int ac, char **av)
{
    std::string line;
    try {
        // Help
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            std::cout << "USAGE" << std::endl;
            std::cout << "\t" << av[0] << " n1 n2 n3 n4 po pw pc pb ps" << std::endl;
            std::cout << "DESCRIPTION" << std::endl;
            std::cout << "\tn1\tnumber of tons of fertilizer F1" << std::endl;
            std::cout << "\tn2\tnumber of tons of fertilizer F2" << std::endl;
            std::cout << "\tn3\tnumber of tons of fertilizer F3" << std::endl;
            std::cout << "\tn4\tnumber of tons of fertilizer F4" << std::endl;
            std::cout << "\tpo\tprice of one unit of oat" << std::endl;
            std::cout << "\tpw\tprice of one unit of wheat" << std::endl;
            std::cout << "\tpc\tprice of one unit of corn" << std::endl;
            std::cout << "\tpb\tprice of one unit of barley" << std::endl;
            std::cout << "\tps\tprice of one unit of soy" << std::endl;
            return (0);
        }
        // ErrorHandling
        if (ac != 10) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
    } catch (...) { return (84); }
    try {
        for (int i = 1; i < 10; i++)
            if (!is_number(std::string(av[i]))) {
                std::cerr << "Invalid syntax." << std::endl;
                return (84);
            }
        n1 = std::atoi(av[1]);
        n2 = std::atoi(av[2]);
        n3 = std::atoi(av[3]);
        n4 = std::atoi(av[4]);
        f1 = std::atoi(av[5]);
        f2 = std::atoi(av[6]);
        f3 = std::atoi(av[7]);
        f4 = std::atoi(av[8]);
        f5 = std::atoi(av[9]);
        if (n1 < 0 || n2 < 0 || n3 < 0 || n4 < 0 ||
            f1 < 0 || f2 < 0 || f3 < 0 || f4 < 0 || f5 < 0) {
            std::cerr << "Invalid Usage. Can't be negative number." << std::endl;
            return (84);
        }
        Line N = { n1, n2, n3, n4 };
        Line P = { f1, f2, f3, f4, f5 };
        Matrix M = createMatrix(N, P);
        std::pair<Line, Matrix> res2 = simplexe(M);
        Line res = res2.first;
        M = res2.second;
        std::vector<float> dump = { 0, 0, 0, 0, 0 };
        float tt = 0;

        for (int i = 0; i < 4; i++)
            if (res[i] != -1)

                if (M[i][M[i].size() - 1] != 0) {
                    dump[res[i]] = M[i][M[i].size() - 1];
                    tt += M[i][M[i].size() - 1] * P[res[i]];
                } else
                    dump[res[i]] = M[i][M[i].size() - 1];
        printf("Resources: %.0f F1, %.0f F2, %.0f F3, %.0f F4\n\n", n1, n2, n3, n4);
        if (dump[0] == 0)
            printf("Oat: 0 units at $%.0f/unit\n", f1);
        else
            printf("Oat: %.2f units at $%.0f/unit\n", dump[0], f1);
        if (dump[1] == 0)
            printf("Wheat: 0 units at $%.0f/unit\n", f2);
        else
            printf("Wheat: %.2f units at $%.0f/unit\n", dump[1], f2);
        if (dump[2] == 0)
            printf("Corn: 0 units at $%.0f/unit\n", f3);
        else
            printf("Corn: %.2f units at $%.0f/unit\n", dump[2], f3);
        if (dump[3] == 0)
            printf("Barley: 0 units at $%.0f/unit\n", f4);
        else
            printf("Barley: %.2f units at $%.0f/unit\n", dump[3], f4);
        if (dump[4] == 0)
            printf("Soy: 0 units at $%.0f/unit\n\n", f5);
        else
            printf("Soy: %.2f units at $%.0f/unit\n\n", dump[4], f5);
        printf("Total production value: $%.2f", tt);
    } catch (...) { return (84); }
    return (0);
}
